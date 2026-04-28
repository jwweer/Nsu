#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 305
#define INF (1LL << 60)

typedef long long ll;

ll dist[MAXN][MAXN];
int next_node[MAXN][MAXN];
int n, m, p, k;

void print_path(int u, int v) {
    if (next_node[u][v] == -1) {
        printf("1 %d\n", u);
        return;
    }
    int cnt = 0;
    int path[MAXN];
    int cur = u;
    while (cur != v) {
        path[cnt++] = cur;
        cur = next_node[cur][v];
    }
    path[cnt++] = v;
    
    printf("%d", cnt);
    for (int i = 0; i < cnt; i++) {
        printf(" %d", path[i]);
    }
    printf("\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    
    scanf("%d %d %d %d", &n, &m, &p, &k);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist[i][j] = 0;
                next_node[i][j] = -1;
            } else {
                dist[i][j] = INF;
                next_node[i][j] = -1;
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;
            next_node[u][v] = v;
            next_node[v][u] = u;
        }
    }
    
    for (int mid = 1; mid <= n; mid++) {
        for (int i = 1; i <= n; i++) {
            if (dist[i][mid] == INF) continue;
            for (int j = 1; j <= n; j++) {
                if (dist[mid][j] == INF) continue;
                if (dist[i][j] > dist[i][mid] + dist[mid][j]) {
                    dist[i][j] = dist[i][mid] + dist[mid][j];
                    next_node[i][j] = next_node[i][mid];
                }
            }
        }
    }
    
    for (int i = 0; i < p; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld ", dist[s][t]);
        print_path(s, t);
    }
    
    for (int i = 0; i < k; i++) {
        int s, t;
        scanf("%d %d", &s, &t);
        printf("%lld\n", dist[s][t]);
    }
    
    return 0;
}