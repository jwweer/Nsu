#include "modular.h"

static int fast_pow(int base, int exp) {
    long long result = 1;
    long long mult = base;
    int current_mod = MOD;

    while (exp > 0) {
        if (exp & 1) {
            result = (result * mult) % current_mod;
        }
        mult = (mult * mult) % current_mod;
        exp >>= 1;
    }
    return (int)result;
}

int pnorm(int val) {
    int m = MOD;
    int r = val % m;
    if (r < 0) r += m;
    return r;
}

int padd(int a, int b) {
    return (int)(((long long)a + b) % MOD);
}

int psub(int a, int b) {
    int m = MOD;
    int diff = a - b;
    if (diff < 0) diff += m;
    return diff;
}

int pmul(int a, int b) {
    return (int)(((long long)a * b) % MOD);
}

int pdiv(int a, int b) {
    return pmul(a, fast_pow(b, MOD - 2));
}

int MOD = 0;