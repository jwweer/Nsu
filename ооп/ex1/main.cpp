#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_m.h"

int main() {
    int a, b;
    std::cin >> a >> b;

    double h1 = hypotenuse(a, b);
    double h2 = hypotenuse_m(a, b);

    std::cout  << h1 << std::endl;
    std::cout  << h2 << std::endl;

    return 0;
}