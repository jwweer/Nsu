#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005

int *sa, *rank;

void radix_sort(int *a, int *b, int *c, int n, int k) {
    int *cnt = (int*)calloc(k + 1, sizeof(int));
    for (int i = 0; i < n; i++) cnt[c[a[i]]]++;
    for (int i = 1; i <= k; i++) cnt[i] += cnt[i - 1];
    for (int i = n - 1; i >= 0; i--) b[--cnt[c[a[i]]]] = a[i];
    free(cnt);
}

void dc3(int *s, int *sa, int n, int K) {
    int *s12 = (int*)malloc((n + 5) * sizeof(int));
    int *sa12 = (int*)malloc((n + 5) * sizeof(int));
    int *s0 = (int*)malloc((n + 5) * sizeof(int));
    int *sa0 = (int*)malloc((n + 5) * sizeof(int));
    
    int n12 = 0;
    for (int i = 0; i < n + (n % 3 == 1 ? 1 : 0); i++) {
        if (i % 3 != 0) {
            s12[n12++] = i;
        }
    }
    
    radix_sort(s12, sa12, s + 2, n12, K);
    radix_sort(sa12, s12, s + 1, n12, K);
    radix_sort(s12, sa12, s, n12, K);
    
    int rank12 = 0;
    int last[3] = {-1, -1, -1};
    for (int i = 0; i < n12; i++) {
        int idx = sa12[i];
        if (s[idx] != last[0] || s[idx + 1] != last[1] || s[idx + 2] != last[2]) {
            rank12++;
            last[0] = s[idx];
            last[1] = s[idx + 1];
            last[2] = s[idx + 2];
        }
        s12[idx] = rank12;
    }
    
    if (rank12 < n12) {
        dc3(s12, sa12, n12, rank12);
        for (int i = 0; i < n12; i++) {
            s12[sa12[i]] = i + 1;
        }
    } else {
        for (int i = 0; i < n12; i++) {
            sa12[s12[i] - 1] = i;
        }
    }
    
    int n0 = 0;
    for (int i = 0; i < n; i += 3) {
        s0[n0++] = i;
    }
    radix_sort(s0, sa0, s, n0, K);
    
    int p = 0, q = 0;
    int *rank12_arr = (int*)calloc(n + 5, sizeof(int));
    for (int i = 0; i < n12; i++) {
        rank12_arr[sa12[i]] = i + 1;
    }
    
    while (p < n0 && q < n12) {
        int i = sa0[p];
        int j = sa12[q];
        if (j % 3 == 1) {
            if (s[i] < s[j] || (s[i] == s[j] && rank12_arr[i + 1] < rank12_arr[j + 1])) {
                sa[p + q] = i;
                p++;
            } else {
                sa[p + q] = j;
                q++;
            }
        } else {
            if (s[i] < s[j] || (s[i] == s[j] && s[i + 1] < s[j + 1]) ||
                (s[i] == s[j] && s[i + 1] == s[j + 1] && rank12_arr[i + 2] < rank12_arr[j + 2])) {
                sa[p + q] = i;
                p++;
            } else {
                sa[p + q] = j;
                q++;
            }
        }
    }
    
    while (p < n0) sa[p + q] = sa0[p++];
    while (q < n12) sa[p + q] = sa12[q++];
    
    free(s12);
    free(sa12);
    free(s0);
    free(sa0);
    free(rank12_arr);
}

int main() {
    char *s = (char*)malloc(MAXN);
    scanf("%s", s);
    int n = strlen(s);
    
    int *t = (int*)malloc((n + 5) * sizeof(int));
    for (int i = 0; i < n; i++) {
        t[i] = s[i] - 'a' + 1;
    }
    t[n] = 0;
    
    sa = (int*)malloc((n + 5) * sizeof(int));
    rank = (int*)malloc((n + 5) * sizeof(int));
    
    dc3(t, sa, n + 1, 27);
    
    for (int i = 1; i <= n; i++) {
        printf("%d ", sa[i]);
    }
    printf("\n");
    
    free(s);
    free(t);
    free(sa);
    free(rank);
    
    return 0;
}