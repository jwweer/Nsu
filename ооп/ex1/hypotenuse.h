#ifndef HYPOTENUSE_H
#define HYPOTENUSE_H

#include <cmath>

namespace Hypo {

    template <typename T>
    T hypotenuse(const T& a, const T& b) {
        return std::sqrt(a * a + b * b);
    }

    template <typename T>
    void hypotenuse_modify(T& a, T& b) {
        T h = std::sqrt(a * a + b * b);
        a = static_cast<T>(h);
        b = static_cast<T>(h);
    }

}

#endif