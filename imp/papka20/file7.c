#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int head[MAXN], to[MAXM * 2], nxt[MAXM * 2], ecnt;
int tin[MAXN], low[MAXN], timer;
int visited[MAXN];
int is_articulation[MAXN];
int n, m;

int min(int a, int b) {
    return a < b ? a : b;
}

void add_edge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void dfs(int u, int parent) {
    visited[u] = 1;
    tin[u] = low[u] = timer++;
    int children = 0;
    
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        
        if (v == parent) continue;
        
        if (visited[v]) {
            low[u] = min(low[u], tin[v]);
        } else {
            dfs(v, u);
            low[u] = min(low[u], low[v]);
            children++;
            
            if (parent != -1 && low[v] >= tin[u]) {
                is_articulation[u] = 1;
            }
        }
    }
    
    if (parent == -1 && children > 1) {
        is_articulation[u] = 1;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    
    memset(visited, 0, sizeof(visited));
    memset(is_articulation, 0, sizeof(is_articulation));
    timer = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
    
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) cnt++;
    }
    
    printf("%d\n", cnt);
    for (int i = 1; i <= n; i++) {
        if (is_articulation[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    
    return 0;
}