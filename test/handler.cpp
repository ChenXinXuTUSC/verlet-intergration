#include <stdio.h>
#include <functional>

int myFunction(int data, int &a, int &b) {
    // 函数体
    return data + a + b;
}

template<typename F, typename... Args>
auto setHandler(F&& f, Args&&... args) {
    using ReturnType = typename std::result_of<F(int, Args...)>::type;
    auto task = std::bind(std::forward<F>(f), std::placeholders::_1, std::ref(args)...);
    return std::function<ReturnType(int)>(task);
}

int main(int argc, char** argv) {
    // 创建延迟调用
    int a = 10, b = 10;
    auto dc1 = setHandler(myFunction, a, b);

    a = 1, b = 1;
    printf("call#1: %d\n", dc1(100));


    a = 2, b = 2;
    printf("call#2: %d\n", dc1(200));


    // auto dc2 = setHandler([](){ printf("hello world\n"); });

    return 0;
}

// #include <stdio.h>
// #include <functional>
// #include <utility>

// int myFunction(int data, int &a, int &b) {
//     return data + a + b;
// }

// template<typename F, typename... Args>
// auto setHandler(F&& f, Args&&... args) 
//     -> std::function<typename std::result_of<F(int, Args...)>::type(int)> {
//     // 构造 std::bind，使用占位符 _1 作为第一个参数
//     auto task = std::bind(std::forward<F>(f), std::placeholders::_1, std::ref(args)...);

//     // 返回封装的 std::function
//     using ReturnType = typename std::result_of<F(int, Args...)>::type;
//     return std::function<ReturnType(int)>(task);
// }

// int main(int argc, char** argv) {
//     int a = 10, b = 10;

//     // 使用 setHandler 绑定 myFunction，第一个参数使用占位符
//     auto dc1 = setHandler(myFunction, a, b);

//     a = 1, b = 1;
//     printf("call#1: %d\n", dc1(100));  // 传递第一个参数为 100，结果：100 + 1 + 1

//     a = 2, b = 2;
//     printf("call#2: %d\n", dc1(200));  // 传递第一个参数为 200，结果：200 + 2 + 2

//     return 0;
// }


// #include <iostream>
// #include <functional>
// #include <thread>

// void increment(int& value) {
//     ++value;
// }

// void print_value(const int& value) {
//     std::cout << "Value: " << value << std::endl;
// }

// int main() {
//     int value = 0;

//     // 使用 std::ref 按引用绑定参数
//     auto increment_func = std::bind(increment, std::ref(value));
//     auto print_func = std::bind(print_value, std::cref(value));

//     // 调用 increment_func 来增加 value
//     increment_func();
//     print_func();  // 输出: Value: 1

//     // 再次调用 increment_func
//     increment_func();
//     print_func();  // 输出: Value: 2

//     // 改变 value 的值
//     value = 10;
//     print_func();  // 输出: Value: 10

//     return 0;
// }

// #include <iostream>
// #include <functional> // std::bind, std::ref

// void print(int x) {
//     std::cout << x << std::endl;
// }

// int main() {
//     int value = 42;

//     auto bound_fn = std::bind(print, std::ref(value)); // 使用 std::ref 创建引用绑定
//     value = 100; // 修改 value
//     bound_fn();  // 输出 100，因为绑定的是引用

//     return 0;
// }

