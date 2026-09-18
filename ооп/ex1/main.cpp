#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_m.h"

int main() {

    int a, b;
    std::cin >> a >> b;

    int h1 = Hypo::hypotenuse(a, b);
    int h2 = Hypom::hypotenuse(a, b);

    std::cout << "Hypo  int: " << h1 << std::endl;
    std::cout << "Hypom int: " << h2 << std::endl;

    double da, db;
    std::cin >> da >> db;

    double dh1 = Hypo::hypotenuse(da, db);
    double dh2 = Hypom::hypotenuse(da, db);

    std::cout << "Hypo  double: " << dh1 << std::endl;
    std::cout << "Hypom double: " << dh2 << std::endl;

    int x = 3, y = 4;
    std::cout << "Before modify: x = " << x << ", y = " << y << std::endl;
    Hypo::hypotenuse_modify(x, y);
    std::cout << "After  modify: x = " << x << ", y = " << y << std::endl;

    return 0;
}