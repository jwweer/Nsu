#include "modular.h"
#include <assert.h>
#include <stdio.h>

int main() {
    MOD = 13;
    
    int a = 45;
    a = pnorm(a);
    assert(a == 6);
    
    int x = pmul(padd(7, psub(2, 3)), 5);
    assert(x == 4);
    
    int y = pdiv(7, x);
    assert(pmul(x, y) == 7);
    
    MOD = 2;
    assert(pnorm(5) == 1);
    
    MOD = 7;
    assert(padd(3, 5) == 1);
    assert(psub(3, 5) == 5);
    assert(pmul(3, 5) == 1);
    assert(pdiv(3, 2) == 5);
    assert(pmul(2, pdiv(3, 2)) == 3);
    
    MOD = 1000000007;
    assert(pnorm(-1) == 1000000006);
    assert(pmul(1000000000, 1000000000) == 49);
    
    printf("All tests passed!\n");
    return 0;
}