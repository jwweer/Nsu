#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
typedef long long ll;
 
ll divisors[20000];
int d_cnt;
 
void get_divs(int idx, ll current, ll* factors, int* counts, int f_cnt) {
    if (idx == f_cnt) {
        divisors[d_cnt++] = current;
        return;
    }
    ll p = 1;
    for (int i = 0; i <= counts[idx]; i++) {
        get_divs(idx + 1, current * p, factors, counts, f_cnt);
        if (i < counts[idx]) p *= factors[idx];
    }
}
 
int compare(const void* a, const void* b) {
    ll arg1 = *(const ll*)a;
    ll arg2 = *(const ll*)b;
    if (arg1 < arg2) return 1;
    if (arg1 > arg2) return -1;
    return 0;
}
 
int main() {
    freopen("input.txt", "r", stdin);
 
    int n;
    scanf("%d", &n);
 
    ll* a = malloc(n * sizeof(ll));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
 
    srand(time(NULL));
 
    ll ans = 1;
    int needed = (n + 1) / 2;
    int iterations = (n > 500000) ? 10 : 25;
 
    for (int iter = 0; iter < iterations; iter++) {
        ll val = a[rand() % n];
        
        ll temp_val = val;
        ll factors[64];
        int counts[64];
        int f_cnt = 0;
 
        for (ll i = 2; i * i <= temp_val; i++) {
            if (temp_val % i == 0) {
                factors[f_cnt] = i;
                counts[f_cnt] = 0;
                while (temp_val % i == 0) {
                    temp_val /= i;
                    counts[f_cnt]++;
                }
                f_cnt++;
            }
        }
        if (temp_val > 1) {
            factors[f_cnt] = temp_val;
            counts[f_cnt] = 1;
            f_cnt++;
        }
 
        d_cnt = 0;
        get_divs(0, 1, factors, counts, f_cnt);
        qsort(divisors, d_cnt, sizeof(ll), compare);
 
        for (int i = 0; i < d_cnt; i++) {
            ll d = divisors[i];
            if (d <= ans) break;
 
            int count = 0;
            for (int j = 0; j < n; j++) {
                if (a[j] % d == 0) count++;
                if (count + (n - 1 - j) < needed) break;
            }
 
            if (count >= needed) {
                ans = d;
                break;
            }
        }
    }
 
    printf("%lld\n", ans);
    free(a);
    return 0;
}
