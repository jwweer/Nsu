#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXM 200005

int head[MAXN], to[MAXM], nxt[MAXM], ecnt;
int color[MAXN];
int parent[MAXN];
int cycle_start, cycle_end;
int n, m;

void add_edge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

int dfs(int u) {
    color[u] = 1;
    
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        
        if (color[v] == 0) {
            parent[v] = u;
            if (dfs(v))
                return 1;
        } else if (color[v] == 1) {
            cycle_start = v;
            cycle_end = u;
            return 1;
        }
    }
    
    color[u] = 2;
    return 0;
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    memset(color, 0, sizeof(color));
    memset(parent, -1, sizeof(parent));
    cycle_start = -1;
    
    for (int i = 1; i <= n; i++) {
        if (color[i] == 0) {
            if (dfs(i)) {
                int *cycle = (int*)malloc((n + 1) * sizeof(int));
                int cnt = 0;
                
                int v = cycle_end;
                while (v != cycle_start) {
                    cycle[cnt++] = v;
                    v = parent[v];
                }
                cycle[cnt++] = cycle_start;
                
                printf("%d\n", cnt);
                for (int i = cnt - 1; i >= 0; i--) {
                    printf("%d ", cycle[i]);
                }
                printf("\n");
                
                free(cycle);
                return 0;
            }
        }
    }
    
    printf("-1\n");
    return 0;
}