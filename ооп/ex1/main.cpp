#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_m.h"

int main() {
    int a, b;
    std::cin >> a >> b;

    std::cout  << Hypo::hypotenuse << std::endl;
    std::cout  << Hypom::hypotenuse << std::endl;

    return 0;
}