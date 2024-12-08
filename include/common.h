#ifndef COMMON_H
#define COMMON_H

#include <cmath>
#include <random>
#include <stdio.h>
#include <type_traits>
#include <vector>

#include <memory>

template <typename T>
using ptr = std::shared_ptr<T>;


template <typename T>
static T randomNum(T min, T max) {
    // 检查类型是否是整数或浮点数
    static_assert(std::is_arithmetic<T>::value, "type must be arithmetic (int or float/double).");

    // 静态随机设备和引擎，仅初始化一次
    static std::random_device rd;
    static std::mt19937 engine(rd());

    if constexpr (std::is_integral<T>::value) {
        // 整型分布器
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine);
    } else if constexpr (std::is_floating_point<T>::value) {
        // 浮点型分布器
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine);
    }
}

#endif
