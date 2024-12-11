#ifndef __COMMON_H__
#define __COMMON_H__

#include <cmath>
#include <random>
#include <stdio.h>
#include <type_traits>
#include <vector>

#include <memory>

template <typename T>
using ptr = std::shared_ptr<T>;



// 主模板，默认不实现
template <typename T, typename Enable = void>
struct RandomNumGenerator;

// 特化：整数类型
template <typename T>
struct RandomNumGenerator<T, std::enable_if_t<std::is_integral<T>::value>> {
    static T generate(T min, T max) {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        std::uniform_int_distribution<T> dist(min, max);
        return dist(engine);
    }
};

// 特化：浮点类型
template <typename T>
struct RandomNumGenerator<T, std::enable_if_t<std::is_floating_point<T>::value>> {
    static T generate(T min, T max) {
        static std::random_device rd;
        static std::mt19937 engine(rd());
        std::uniform_real_distribution<T> dist(min, max);
        return dist(engine);
    }
};

// 对外接口
template <typename T>
T randomNum(T min, T max) {
    static_assert(std::is_arithmetic<T>::value, "type must be arithmetic (integer or float/double).");
    return RandomNumGenerator<T>::generate(min, max);
}

#endif
