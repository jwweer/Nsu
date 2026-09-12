#include "hypotenuse_m.h"
#include <cmath>
#include <random>

int hypotenuse_modified(int a, int b) {
    double result = std::sqrt(a * a + b * b);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> chance(0, 1);

    if (chance(gen) == 1) {
        result += static_cast<int>(gen());
    }

    return result;
}