#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], edge_id[MAXM * 2], ecnt;
int tin[MAXN], low[MAXN], timer;
int visited[MAXN];
int is_bridge[MAXM];
int n, m;

int min(int a, int b) {
    return a < b ? a : b;
}

void add_edge(int u, int v, int id) {
    to[ecnt] = v;
    edge_id[ecnt] = id;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void dfs(int u, int parent_edge) {
    visited[u] = 1;
    tin[u] = low[u] = timer++;
    
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        int id = edge_id[e];
        
        if (id == parent_edge) continue;
        
        if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, id);
            low[u] = min(low[u], low[v]);
            if (low[v] > tin[u]) {
                is_bridge[id] = 1;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v, i);
        add_edge(v, u, i);
    }
    
    memset(visited, 0, sizeof(visited));
    memset(is_bridge, 0, sizeof(is_bridge));
    timer = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
    
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) cnt++;
    }
    
    printf("%d\n", cnt);
    for (int i = 0; i < m; i++) {
        if (is_bridge[i]) {
            printf("%d ", i + 1);
        }
    }
    printf("\n");
    
    return 0;
}