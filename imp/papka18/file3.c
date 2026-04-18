#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005

int t[MAXN * 3], sa[MAXN * 3], rk[MAXN], tmp[MAXN];

int cmp(int *s, int a, int b, int k, int n) {
    if (rk[a] != rk[b]) return rk[a] < rk[b];
    int ra = a + k <= n ? rk[a + k] : -1;
    int rb = b + k <= n ? rk[b + k] : -1;
    return ra < rb;
}

void csort(int *s, int *sa, int n, int m) {
    int *cnt = (int*)calloc(m + 1, sizeof(int));
    for (int i = 0; i < n; i++) cnt[s[sa[i]]]++;
    for (int i = 1; i <= m; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) tmp[--cnt[s[sa[i]]]] = sa[i];
    for (int i = 0; i < n; i++) sa[i] = tmp[i];
    free(cnt);
}

void build_sa(int *s, int *sa, int n, int m) {
    int *ns = (int*)malloc(n * sizeof(int));
    int *nsa = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) sa[i] = i;
    csort(s, sa, n, m);
    
    rk[sa[0]] = 1;
    for (int i = 1; i < n; i++) {
        rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
    }
    
    for (int k = 1; k < n; k <<= 1) {
        int p = 0;
        for (int i = n - k; i < n; i++) nsa[p++] = i;
        for (int i = 0; i < n; i++) if (sa[i] >= k) nsa[p++] = sa[i] - k;
        
        csort(rk, nsa, n, rk[sa[n - 1]]);
        
        tmp[nsa[0]] = 1;
        for (int i = 1; i < n; i++) {
            tmp[nsa[i]] = tmp[nsa[i - 1]] + cmp(s, nsa[i - 1], nsa[i], k, n);
        }
        
        for (int i = 0; i < n; i++) rk[i] = tmp[i];
        for (int i = 0; i < n; i++) sa[i] = nsa[i];
    }
    
    free(ns);
    free(nsa);
}

int main() {
    char str[MAXN];
    scanf("%s", str);
    int n = strlen(str);
    
    int *s = (int*)malloc((n + 1) * sizeof(int));
    for (int i = 0; i < n; i++) {
        s[i] = str[i] - 'a' + 1;
    }
    s[n] = 0;
    
    build_sa(s, sa, n + 1, 26);
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }
    printf("\n");
    
    free(s);
    return 0;
}