#include <stdio.h>

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int n;
    fscanf(in, "%d", &n);
    
    int candidate = 0;
    int count = 0;
    int x;
    
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &x);
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }
    
    fclose(in);
    
    in = fopen("input.txt", "r");
    fscanf(in, "%d", &n);
    
    int freq = 0;
    for (int i = 0; i < n; i++) {
        fscanf(in, "%d", &x);
        if (x == candidate) {
            freq++;
        }
    }
    
    fclose(in);
    
    if (freq > n / 2) {
        fprintf(out, "YES\n%d\n", candidate);
    } else {
        fprintf(out, "NO\n");
    }
    
    fclose(out);
    
    return 0;
}