#include <stdio.h>
#include <stdlib.h>

long long gcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    long long g = gcd(b, a % b, y, x);
    *y -= (a / b) * (*x);
    return g;
}

int main() {
    int k;
    scanf("%d", &k);
    
    long long *M = malloc(k * sizeof(long long));
    long long *A = malloc(k * sizeof(long long));
    
    for (int i = 0; i < k; i++) scanf("%lld", &M[i]);
    for (int i = 0; i < k; i++) scanf("%lld", &A[i]);
    
    long long res_mod = M[0];
    long long res_val = A[0] % res_mod;
    
    for (int i = 1; i < k; i++) {
        long long x, y;
        long long g = gcd(res_mod, M[i], &x, &y);
        
        if ((A[i] - res_val) % g != 0) {
            printf("0\n");
            return 0;
        }
        
        long long lcm = res_mod / g * M[i];
        long long diff = (A[i] - res_val) / g;
        
        long long step = (x * diff) % (M[i] / g);
        if (step < 0) step += M[i] / g;
        
        res_val = res_val + step * res_mod;
        res_mod = lcm;
        res_val %= res_mod;
        if (res_val < 0) res_val += res_mod;
    }
    
    printf("%lld\n", res_val);
    
    free(M);
    free(A);
    return 0;
}