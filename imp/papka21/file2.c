#include <stdio.h>
#include <string.h>

#define MAX 105

int A, B, M;
int g[MAX][MAX];
int matchU[MAX];
int matchV[MAX];
int used[MAX];

int try_kuhn(int u) {
    for (int v = 1; v <= B; v++) {
        if (g[u][v] && !used[v]) {
            used[v] = 1;
            if (matchV[v] == 0 || try_kuhn(matchV[v])) {
                matchU[u] = v;
                matchV[v] = u;
                return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d %d", &A, &B, &M);

    memset(g, 0, sizeof(g));
    for (int i = 0; i < M; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        g[x][y] = 1;
    }

    memset(matchU, 0, sizeof(matchU));
    memset(matchV, 0, sizeof(matchV));

    int matching = 0;
    for (int u = 1; u <= A; u++) {
        memset(used, 0, sizeof(used));
        if (try_kuhn(u))
            matching++;
    }

    printf("%d\n", matching);
    for (int u = 1; u <= A; u++) {
        if (matchU[u])
            printf("%d %d\n", u, matchU[u]);
    }

    return 0;
}