#include <stdio.h>
#include <string.h>

#define MAX_N 500

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N;
    scanf("%d\n", &N);
    
    char R[MAX_N][MAX_N + 1];
    for (int i = 0; i < N; i++) {
        fgets(R[i], MAX_N + 1, stdin);
        R[i][strcspn(R[i], "\n")] = '\0';
    }
    
    for (int i = 0; i < N; i++) {
        R[i][i] = '1';
    }
    

    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            if (R[i][k] == '1') {
                for (int j = 0; j < N; j++) {
                    if (R[k][j] == '1') {
                        R[i][j] = '1';
                    }
                }
            }
        }
    }
    
    for (int i = 0; i < N; i++) {
        printf("%s\n", R[i]);
    }
    
    return 0;
}