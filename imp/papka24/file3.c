#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    long long *a = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lld", &a[i]);
    }
    
    srand(time(NULL));
    
    long long max_g = 1;
    for (int iter = 0; iter < 20; iter++) {
        int idx = rand() % n;
        long long val = a[idx];
        
        long long divisors[10000];
        int div_count = 0;
        
        for (long long d = 1; d * d <= val; d++) {
            if (val % d == 0) {
                divisors[div_count++] = d;
                if (d != val / d) {
                    divisors[div_count++] = val / d;
                }
            }
        }
        
        for (int i = 0; i < div_count; i++) {
            long long g = divisors[i];
            if (g <= max_g) continue;
            
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] % g == 0) {
                    count++;
                    if (count * 2 >= n) break;
                }
            }
            
            if (count * 2 >= n && g > max_g) {
                max_g = g;
            }
        }
    }
    
    fprintf(output, "%lld\n", max_g);
    
    free(a);
    fclose(input);
    fclose(output);
    return 0;
}