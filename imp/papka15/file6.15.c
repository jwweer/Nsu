#include <stdio.h>

#define MAXN 105

double x[MAXN], y[MAXN];

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &x[i], &y[i]);
    }
    
    double c[MAXN];
    for (int i = 0; i < n; i++) c[i] = y[i];
    
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--) {
            c[j] = (c[j] - c[j-1]) / (x[j] - x[j-i]);
        }
    }
    
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            c[i] -= c[j] * x[0];
        }
        c[i] /= x[0];
    }
    
    for (int i = 0; i < n; i++) {
        printf("%.10lf ", c[i]);
    }
    printf("\n");
    
    return 0;
}