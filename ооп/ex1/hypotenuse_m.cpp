#include "hypotenuse_m.h"
#include <cmath>
#include <random>

double hypotenuse_modified(int a, int b) {
    double result = std::sqrt(static_cast<double>(a) * a + static_cast<double>(b) * b);

    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> chance(0, 1);

    if (chance(gen) == 1) {
        result += static_cast<double>(gen());
    }

    return result;
}