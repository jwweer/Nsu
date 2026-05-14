#include "modular.h"

int MOD;

int pnorm(int a) {
    int r = a % MOD;
    return r < 0 ? r + MOD : r;
}

int padd(int a, int b) {
    return (a + b) % MOD;
}

int psub(int a, int b) {
    int r = a - b;
    return r < 0 ? r + MOD : r;
}

int pmul(int a, int b) {
    return (int)((long long)a * b % MOD);
}

static int mod_inv(int a) {
    int exp = MOD - 2;
    long long result = 1;
    long long base = a % MOD;
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    return (int)result;
}

int pdiv(int a, int b) {
    return pmul(a, mod_inv(b));
}