typedef struct Factors {
    int k;
    int primes[32];
    int powers[32];
} Factors;

void Factorize(int X, Factors *res) {
    res->k = 0;
    if (X <= 1) return;
    
    int n = X;
    int d = 2;
    
    while (d * d <= n) {
        if (n % d == 0) {
            int count = 0;
            while (n % d == 0) {
                n /= d;
                count++;
            }
            res->primes[res->k] = d;
            res->powers[res->k] = count;
            res->k++;
        }
        d++;
    }
    
    if (n > 1) {
        res->primes[res->k] = n;
        res->powers[res->k] = 1;
        res->k++;
    }
}