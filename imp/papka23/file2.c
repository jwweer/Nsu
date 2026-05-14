#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_K 10
#define MAX_M 100

int N, K, M, L;
char effect[MAX_N][MAX_K][MAX_M];
int chosen[MAX_N];
int voltage[MAX_M];
int found = 0;

void dfs(int panel) {
    if (found) return;
    
    if (panel == N) {
        for (int i = 0; i < M; i++) {
            if (voltage[i] != L) return;
        }
        found = 1;
        return;
    }
    
    for (int sw = 0; sw < K; sw++) {
        int ok = 1;
        for (int lamp = 0; lamp < M; lamp++) {
            if (effect[panel][sw][lamp] == 'X') {
                voltage[lamp]++;
                if (voltage[lamp] > L) ok = 0;
            }
        }
        
        if (ok) {
            chosen[panel] = sw + 1;
            dfs(panel + 1);
            if (found) return;
        }
        
        for (int lamp = 0; lamp < M; lamp++) {
            if (effect[panel][sw][lamp] == 'X') {
                voltage[lamp]--;
            }
        }
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    fscanf(in, "%d %d %d %d", &N, &K, &M, &L);
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < K; j++) {
            fscanf(in, "%s", effect[i][j]);
            while ((int)strlen(effect[i][j]) < M) {
                char tmp[200];
                fscanf(in, "%s", tmp);
                strcat(effect[i][j], tmp);
            }
        }
    }
    
    memset(voltage, 0, sizeof(voltage));
    found = 0;
    dfs(0);
    
    if (!found) {
        fprintf(out, "NO\n");
    } else {
        fprintf(out, "YES\n");
        for (int i = 0; i < N; i++) {
            fprintf(out, "%d\n", chosen[i]);
        }
    }
    
    fclose(in);
    fclose(out);
    return 0;
}