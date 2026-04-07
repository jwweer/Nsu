#include <stdio.h>
#include <assert.h>
#include "primes.h"

int main() {
    // Тест isPrime
    assert(isPrime(2) == 1);
    assert(isPrime(3) == 1);
    assert(isPrime(4) == 0);
    assert(isPrime(17) == 1);
    assert(isPrime(1) == 0);
    assert(isPrime(0) == 0);
    
    // Тест findNextPrime
    assert(findNextPrime(2) == 2);
    assert(findNextPrime(4) == 5);
    assert(findNextPrime(14) == 17);
    assert(findNextPrime(23) == 23);
    
    // Тест getPrimesCount
    assert(getPrimesCount(1, 10) == 4); // 2,3,5,7
    assert(getPrimesCount(10, 20) == 4); // 11,13,17,19
    assert(getPrimesCount(20, 30) == 2); // 23,29
    
    printf("Все тесты пройдены успешно!\n");
    return 0;
}