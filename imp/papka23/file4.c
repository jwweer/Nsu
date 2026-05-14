#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAX_N 20
#define MAX_M 8
#define MAX_MASK (1 << 8)

int N, M;
char grid[MAX_N][MAX_M];
int memo[MAX_N * MAX_M][MAX_MASK];
int idx, target_mask;

int dfs(int pos, int mask) {
    if (pos == idx) {
        return mask == target_mask ? 1 : 0;
    }
    if (memo[pos][mask] != -1) return memo[pos][mask];
    
    int r = pos / M, c = pos % M;
    if (grid[r][c] == '#') {
        return memo[pos][mask] = dfs(pos + 1, mask);
    }
    
    if (mask & (1 << c)) {
        return memo[pos][mask] = dfs(pos + 1, mask);
    }
    
    int res = 0;
    
    if (r + 1 < N && c + 1 < M && grid[r+1][c] != '#' && grid[r+1][c+1] != '#' &&
        !(mask & (1 << c)) && !(mask & (1 << (c+1)))) {
        int new_mask = mask;
        new_mask |= (1 << c);
        int next_mask = 0;
        if (!(mask & (1 << c))) next_mask |= (1 << c);
        if (!(mask & (1 << (c+1)))) next_mask |= (1 << (c+1));
        res = (res + dfs(pos + 1, mask | (1 << c) | (1 << (c+1)))) % MOD;
    }
    
    return memo[pos][mask] = res;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int T;
    fscanf(in, "%d", &T);
    
    for (int t = 0; t < T; t++) {
        fscanf(in, "%d %d", &N, &M);
        for (int i = 0; i < N; i++) {
            fscanf(in, "%s", grid[i]);
        }
        
        memset(memo, -1, sizeof(memo));
        idx = N * M;
        target_mask = 0;
        
        int result = dfs(0, 0);
        fprintf(out, "%d\n", result);
    }
    
    fclose(in);
    fclose(out);
    return 0;
}