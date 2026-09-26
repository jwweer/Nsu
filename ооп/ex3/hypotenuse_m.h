#pragma once
#include <cmath>
#include <random>

inline std::mt19937 rng(std::random_device{}());

namespace Hypo {
    template <typename T2, typename T1>
    T2 hypotenuse(const T1& a, const T1& b, const T1& noise) {
        double result = std::sqrt(
            static_cast<double>(a) * static_cast<double>(a) +
            static_cast<double>(b) * static_cast<double>(b)
        );

        static std::uniform_int_distribution<int> chance(0, 1);
        if (chance(rng) == 1) {
            result += static_cast<double>(noise);
        }

        return static_cast<T2>(result);
    }
}