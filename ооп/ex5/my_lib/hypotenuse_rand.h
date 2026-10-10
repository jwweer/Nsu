#pragma once
#include <cmath>
#include <random>

namespace my_lib {
    namespace randver {
        template<typename T>
        double hypotenuse_rand(T a, T b) {
            double res = std::sqrt(static_cast<double>(a)*a + static_cast<double>(b)*b);
            static std::mt19937 gen(std::random_device{}());
            std::uniform_int_distribution<int> coin(0, 1), add(0, 10);
            if (coin(gen)) res += add(gen);
            return res;
        }
    }
}