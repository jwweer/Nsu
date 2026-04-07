#include "primes.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 10000000

static bool is_prime[MAX_N + 1];
static int prime_count[MAX_N + 1];
static int initialized = 0;

static void init_sieve() {
    if (initialized) return;
    
    memset(is_prime, true, sizeof(is_prime));
    is_prime[0] = is_prime[1] = false;
    
    for (int i = 2; i * i <= MAX_N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= MAX_N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    
    prime_count[0] = 0;
    for (int i = 1; i <= MAX_N; i++) {
        prime_count[i] = prime_count[i-1] + (is_prime[i] ? 1 : 0);
    }
    
    initialized = 1;
}

int isPrime(int x) {
    if (x < 0 || x > MAX_N) return 0;
    init_sieve();
    return is_prime[x] ? 1 : 0;
}

int findNextPrime(int x) {
    init_sieve();
    for (int i = x; i <= MAX_N; i++) {
        if (is_prime[i]) return i;
    }
    return 0;
}

int getPrimesCount(int l, int r) {
    if (l < 0) l = 0;
    if (r > MAX_N) r = MAX_N;
    if (l > r) return 0;
    
    init_sieve();
    return prime_count[r] - prime_count[l];
}