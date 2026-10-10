#pragma once
#include <cmath>

namespace my_lib {
    namespace usual {
        template<typename T>
        double hypotenuse(T a, T b) {
            return std::sqrt(static_cast<double>(a)*a + static_cast<double>(b)*b);
        }
    }
}