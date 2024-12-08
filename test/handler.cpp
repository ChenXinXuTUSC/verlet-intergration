#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

int myFunction(int &a, int &b) {
    // 函数体
    return a + b;
}

template <typename F, typename... A>
auto delayedCall(F&& func, A&&... args) {
    // using return_type = typename std::result_of<F(A...)>::type;

    auto task = [&]() {
        return func(args...);
    };

    return task;
}

int main(int argc, char** argv) {
    // 创建延迟调用
    int a, b;
    auto dc1 = delayedCall(myFunction, a, b);

    a = 1, b = 1;
    printf("call#1: %d\n", dc1());


    a = 2, b = 2;
    printf("call#2: %d\n", dc1());


    auto dc2 = delayedCall([](){ printf("hello world\n"); });

    return 0;
}
