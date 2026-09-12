#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_m.h"

int main() {
    int a, b;
    std::cin >> a >> b;
    int h1, h2;
    h1 = Hypo::hypotenuse(a, b);
    h2 = Hypom::hypotenuse(a, b);

    std::cout  << h1 << std::endl;
    std::cout  << h2 << std::endl;

    return 0;
}