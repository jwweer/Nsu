#include "hypotenuse.h"
#include <cmath>
namespace Hypo {
    int hypotenuse(const int& a, const int& b) {
        return std::sqrt(a * a + b * b);
    }
    double hypotenuse(const double& a, const double& b) {
        return std::sqrt(a * a + b * b);
    }
}