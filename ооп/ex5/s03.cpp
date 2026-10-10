#include <iostream>
#include "hypotenuse.h"
#include "hypotenuse_rand.h"

int main() {
    int a, b;
    std::cin >> a >> b;
    std::cout << my_lib::usual::hypotenuse(a, b) << "\n";
    std::cout << my_lib::randver::hypotenuse_rand(a, b) << "\n";
    return 0;
}