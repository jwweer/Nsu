#include <stdio.h>
#include <stdlib.h>

double Function(double x);

double derivative(double x, double eps) {
    return (Function(x + eps) - Function(x - eps)) / (2.0 * eps);
}

int main() {
    int M;
    scanf("%d", &M);
    
    double eps = 1e-7;
    
    for (int i = 0; i < M; i++) {
        double x;
        scanf("%lf", &x);
        double result = derivative(x, eps);
        printf("%.16lf\n", result);
    }
    
    return 0;
}