#include <stdio.h>
#include <limits.h>

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n, m;
    fscanf(input, "%d %d", &n, &m);
    
    int A[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(input, "%d", &A[i][j]);
        }
    }
    
    int result_x = 0, result_y = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int is_nash = 1;
            
            for (int x = 0; x < n; x++) {
                if (x != i && A[x][j] <= A[i][j]) {
                    is_nash = 0;
                    break;
                }
            }
            
            if (!is_nash) continue;
            
            for (int y = 0; y < m; y++) {
                if (y != j && A[i][y] >= A[i][j]) {
                    is_nash = 0;
                    break;
                }
            }
            
            if (is_nash) {
                result_x = i + 1;
                result_y = j + 1;
                break;
            }
        }
        if (result_x != 0) break;
    }
    
    fprintf(output, "%d %d\n", result_x, result_y);
    
    fclose(input);
    fclose(output);
    return 0;
}