#include <stdio.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n;
    fscanf(input, "%d", &n);
    
    int candidate = 0, count = 0;
    long long x;
    
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lld", &x);
        if (count == 0) {
            candidate = x;
            count = 1;
        } else if (x == candidate) {
            count++;
        } else {
            count--;
        }
    }
    
    fseek(input, 0, SEEK_SET);
    fscanf(input, "%d", &n);
    
    int actual_count = 0;
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lld", &x);
        if (x == candidate) {
            actual_count++;
        }
    }
    
    if (actual_count > n / 2) {
        fprintf(output, "YES %d\n", candidate);
    } else {
        fprintf(output, "NO\n");
    }
    
    fclose(input);
    fclose(output);
    return 0;
}