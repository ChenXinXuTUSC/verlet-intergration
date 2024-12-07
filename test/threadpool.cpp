#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

// 任务优先级结构体
struct PriorityTask {
    int priority;
    std::function<void()> func;

    // 优先级比较，优先级数值越小，优先级越高
    bool operator<(const PriorityTask& other) const {
        return priority > other.priority;
    }
};

// 线程池类
class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for (size_t i = 0; i < threads; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    PriorityTask task;

                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        this->condition.wait(lock, [this] { return this->stop || !this->tasks.empty(); });
                        if (this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.top());
                        this->tasks.pop();
                    }

                    task.func();
                }
            });
        }
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();
        for (std::thread& worker : workers) {
            worker.join();
        }
    }

    template <class F, class... Args>
    auto enqueue(int priority, F&& f, Args&&... args)
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;

        auto task = std::make_shared< std::packaged_task<return_type()> >(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );

        std::future<return_type> res = task->get_future();
        {
            std::unique_lock<std::mutex> lock(queueMutex);

            // Don't allow enqueueing after stopping the pool
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");

            tasks.emplace(PriorityTask{priority, [task]() { (*task)(); }});
        }
        condition.notify_one();
        return res;
    }

private:
    // Need to keep track of threads so we can join them
    std::vector<std::thread> workers;
    // The task queue
    std::priority_queue<PriorityTask> tasks;

    // Synchronization
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

// 使用示例
int main() {
    ThreadPool pool(4);

    auto result1 = pool.enqueue(1, []() -> int {
        std::cout << "Executing task 1" << std::endl;
        return 1;
    });

    auto result2 = pool.enqueue(0, []() -> int {
        std::cout << "Executing task 2" << std::endl;
        return 2;
    });

    std::cout << "Task 1 result: " << result1.get() << std::endl;
    std::cout << "Task 2 result: " << result2.get() << std::endl;

    return 0;
}
