#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_m.h"

int main() {

    int a, b;
    std::cin >> a >> b;

    std::cout <<  Hypo::hypotenuse(a, b) << std::endl;
    std::cout << Hypom::hypotenuse(a, b) << std::endl;

    double da, db;
    std::cin >> da >> db;

    std::cout << Hypo::hypotenuse(da, db) << std::endl;
    std::cout << Hypom::hypotenuse(da, db) << std::endl;

    int x = 3, y = 4;
    std::cout << "Before: x = " << x << ", y = " << y << std::endl;
    Hypo::hypotenuse_modify(x, y);
    std::cout << "After: x = " << x << ", y = " << y << std::endl;

    return 0;
}