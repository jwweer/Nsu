#include <stdio.h>
#include <stdlib.h>

#define MAX_N 30

int n;
int puzzle[MAX_N][MAX_N];
int target[MAX_N][MAX_N];

void rotate_clockwise(int i, int j, int k) {
    i--; j--;
    int temp[MAX_N][MAX_N];
    
    for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
            temp[x][y] = puzzle[i + x][j + y];
        }
    }
    
    for (int x = 0; x < k; x++) {
        for (int y = 0; y < k; y++) {
            puzzle[i + y][j + k - 1 - x] = temp[x][y];
        }
    }
}

int calculate_quality() {
    int good_pairs = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n - 1; j++) {
            if (puzzle[i][j] < puzzle[i][j + 1]) {
                good_pairs++;
            }
        }
    }
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n; j++) {
            if (puzzle[i][j] < puzzle[i + 1][j]) {
                good_pairs++;
            }
        }
    }
    
    return good_pairs;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    fscanf(input, "%d", &n);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(input, "%d", &puzzle[i][j]);
        }
    }
    
    int moves[500][3];
    int move_count = 0;
    
    int target_quality = n * n * (n - 1);
    
    for (int iter = 0; iter < 100 && move_count < 500; iter++) {
        int best_improvement = 0;
        int best_i = 1, best_j = 1, best_k = 1;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int max_k = n - ((i > j ? i : j) - 1);
                for (int k = 2; k <= max_k && k <= n - i + 1 && k <= n - j + 1; k++) {
                    rotate_clockwise(i, j, k);
                    int new_quality = calculate_quality();
                    int improvement = new_quality - target_quality;
                    
                    if (improvement > best_improvement) {
                        best_improvement = improvement;
                        best_i = i;
                        best_j = j;
                        best_k = k;
                    }
                    
                    // Откат
                    rotate_clockwise(i, j, k);
                    rotate_clockwise(i, j, k);
                    rotate_clockwise(i, j, k);
                }
            }
        }
        
        if (best_improvement > 0) {
            rotate_clockwise(best_i, best_j, best_k);
            moves[move_count][0] = best_i;
            moves[move_count][1] = best_j;
            moves[move_count][2] = best_k;
            move_count++;
            target_quality = calculate_quality();
        } else {
            break;
        }
    }
    
    fprintf(output, "%d\n", move_count);
    for (int i = 0; i < move_count; i++) {
        fprintf(output, "%d %d %d\n", moves[i][0], moves[i][1], moves[i][2]);
    }
    
    fclose(input);
    fclose(output);
    return 0;
}