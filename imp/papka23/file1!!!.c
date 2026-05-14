#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 12

int M, N;
char board[MAX][MAX];
int col_used[MAX];
int diag1_used[2*MAX];
int diag2_used[2*MAX];
int queens[MAX];

int solve(int row) {
    if (row == M) return 1;
    
    for (int c = 0; c < N; c++) {
        if (board[row][c] == '.') continue;
        if (col_used[c]) continue;
        if (diag1_used[row - c + N]) continue;
        if (diag2_used[row + c]) continue;
        
        queens[row] = c;
        col_used[c] = 1;
        diag1_used[row - c + N] = 1;
        diag2_used[row + c] = 1;
        
        if (solve(row + 1)) return 1;
        
        col_used[c] = 0;
        diag1_used[row - c + N] = 0;
        diag2_used[row + c] = 0;
    }
    return 0;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    fscanf(in, "%d %d", &M, &N);
    for (int i = 0; i < M; i++) {
        fscanf(in, "%s", board[i]);
    }
    fclose(in);
    
    memset(col_used, 0, sizeof(col_used));
    memset(diag1_used, 0, sizeof(diag1_used));
    memset(diag2_used, 0, sizeof(diag2_used));
    
    if (solve(0)) {
        fprintf(out, "YES\n");
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (board[i][j] == '?' && queens[i] == j)
                    fprintf(out, "X");
                else if (board[i][j] == '?')
                    fprintf(out, ".");
                else
                    fprintf(out, ".");
            }
            fprintf(out, "\n");
        }
    } else {
        fprintf(out, "NO\n");
    }
    
    fclose(out);
    return 0;
}