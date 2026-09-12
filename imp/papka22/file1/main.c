#include "modular.h"
#include <assert.h>
#include <limits.h>

static int ref_norm(int val) {
    int r = val % MOD;
    if (r < 0) r += MOD;
    return r;
}

static int ref_mul(int a, int b) {
    return (int)((1LL * a * b) % MOD);
}

static int ref_inv(int val) {
    long long r0 = MOD, r1 = val;
    long long s0 = 0, s1 = 1;

    while (r1 != 0) {
        long long q = r0 / r1;
        long long tmp_r = r0 - q * r1;
        r0 = r1;
        r1 = tmp_r;
        long long tmp_s = s0 - q * s1;
        s0 = s1;
        s1 = tmp_s;
    }

    s0 %= MOD;
    if (s0 < 0) s0 += MOD;
    return (int)s0;
}

static int ref_div(int a, int b) {
    return ref_mul(a, ref_inv(b));
}

static void test_small(int prime) {
    MOD = prime;

    int nums[] = {0, 1, prime-1, prime, prime+1, -1, -prime, -prime-1, 100, -100, INT_MAX, INT_MIN};
    int num_cnt = sizeof(nums) / sizeof(nums[0]);

    for (int i = 0; i < num_cnt; i++) {
        assert(pnorm(nums[i]) == ref_norm(nums[i]));
    }

    int vals[] = {0, 1, 2, prime/2, prime-2, prime-1};
    int val_cnt = sizeof(vals) / sizeof(vals[0]);

    for (int i = 0; i < val_cnt; i++) {
        for (int j = 0; j < val_cnt; j++) {
            int x = vals[i];
            int y = vals[j];
            if (x < 0 || x >= prime) continue;
            if (y < 0 || y >= prime) continue;

            assert(padd(x, y) == ref_norm(x + y));
            assert(psub(x, y) == ref_norm(x - y));
            assert(pmul(x, y) == ref_mul(x, y));

            if (y != 0) {
                assert(pdiv(x, y) == ref_div(x, y));
            }
        }
    }
}

static void test_edges(int prime) {
    MOD = prime;

    assert(pnorm(prime) == 0);
    assert(pnorm(-prime) == 0);
    assert(padd(prime-1, 1) == 0);
    assert(psub(0, 1) == prime-1);
    assert(pmul(prime-1, prime-1) == 1);

    assert(pdiv(0, 1) == 0);
    assert(pdiv(1, 1) == 1);
    assert(pdiv(prime-1, 1) == prime-1);
    assert(pdiv(1, prime-1) == prime-1);
    assert(pdiv(prime-1, prime-1) == 1);
}

static void test_mod_switch(void) {
    MOD = 7;
    assert(pnorm(10) == 3);
    assert(padd(5, 6) == 4);
    assert(psub(5, 6) == 6);
    assert(pmul(3, 5) == 1);
    assert(pdiv(3, 5) == 2);

    MOD = 13;
    assert(pnorm(10) == 10);
    assert(padd(5, 6) == 11);
    assert(psub(5, 6) == 12);
    assert(pmul(3, 5) == 2);
    assert(pdiv(3, 5) == 8);

    MOD = 7;
    assert(pnorm(10) == 3);
    assert(padd(5, 6) == 4);
}

static void test_large(void) {
    MOD = 1000000007;
    assert(pnorm(2000000000) == 2000000000 % MOD);
    assert(pmul(1000000006, 1000000006) == 1);
    assert(pdiv(1, 2) == 500000004);
    assert(pmul(2, 500000004) == 1);
    assert(pdiv(1000000006, 1000000006) == 1);
}

int main(void) {
    test_small(2);
    test_small(3);
    test_small(5);
    test_small(13);
    test_small(17);

    MOD = 50021;
    assert(pmul(50020, 50020) == 1);

    test_edges(50021);
    test_edges(65537);
    test_mod_switch();
    test_large();

    return 0;
}