#include <stdio.h>
#include <math.h>

double solve(int n, int m, double p) {
    double q = 1 - p;
    double comp1 = n * m * pow(q, 4);
    double comp2 = (n * m - n - m + 1) * 2 * p * pow(q, 6) + 
                   (n - 2) * (m - 2) * 4 * p * pow(q, 6);
    double comp3 = (n * m - n - m + 1) * 4 * pow(p, 2) * pow(q, 8) +
                   (n - 2) * (m - 2) * 4 * pow(p, 2) * pow(q, 8) +
                   (n - 2) * (m - 2) * 8 * pow(p, 2) * pow(q, 8);
    
    return (comp1 + comp2 + comp3) / (n * m);
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int q;
    fscanf(input, "%d", &q);
    
    for (int t = 0; t < q; t++) {
        int n, m;
        double p;
        fscanf(input, "%d %d %lf", &n, &m, &p);
        
        double result = solve(n, m, p);
        fprintf(output, "%.10f\n", result);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}