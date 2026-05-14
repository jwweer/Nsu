#include <stdio.h>
#include <string.h>

#define SIZE 9

int board[SIZE][SIZE];

int isValid(int row, int col, int num) {
    for (int c = 0; c < SIZE; c++) {
        if (board[row][c] == num) return 0;
    }
    for (int r = 0; r < SIZE; r++) {
        if (board[r][col] == num) return 0;
    }
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {
            if (board[startRow + r][startCol + c] == num) return 0;
        }
    }
    return 1;
}

int solve() {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(r, c, num)) {
                        board[r][c] = num;
                        if (solve()) return 1;
                        board[r][c] = 0;
                    }
                }
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int N;
    fscanf(in, "%d", &N);
    
    for (int t = 0; t < N; t++) {
        char line[SIZE + 1];
        for (int i = 0; i < SIZE; i++) {
            fscanf(in, "%s", line);
            for (int j = 0; j < SIZE; j++) {
                board[i][j] = (line[j] == '.') ? 0 : (line[j] - '0');
            }
        }
        
        solve();
        
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fprintf(out, "%d", board[i][j]);
            }
            fprintf(out, "\n");
        }
        fprintf(out, "\n");
    }
    
    fclose(in);
    fclose(out);
    return 0;
}