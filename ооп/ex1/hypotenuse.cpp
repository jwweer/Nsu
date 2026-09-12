#include "hypotenuse.h"
#include <cmath>

double hypotenuse(int a, int b) {
    return std::sqrt(static_cast<double>(a) * a + static_cast<double>(b) * b);
}