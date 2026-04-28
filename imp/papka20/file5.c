#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 100005

int head[MAXN], to[MAXM], nxt[MAXM], ecnt;
int headT[MAXN], toT[MAXM], nxtT[MAXM], ecntT;
int visited[MAXN];
int order[MAXN], order_cnt;
int comp[MAXN], comp_cnt;
int n, m;

void add_edge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
    
    toT[ecntT] = u;
    nxtT[ecntT] = headT[v];
    headT[v] = ecntT++;
}

void dfs1(int u) {
    visited[u] = 1;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (!visited[v]) {
            dfs1(v);
        }
    }
    order[order_cnt++] = u;
}

void dfs2(int u, int id) {
    visited[u] = 1;
    comp[u] = id;
    for (int e = headT[u]; e != -1; e = nxtT[e]) {
        int v = toT[e];
        if (!visited[v]) {
            dfs2(v, id);
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    
    memset(head, -1, sizeof(head));
    memset(headT, -1, sizeof(headT));
    ecnt = ecntT = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    memset(visited, 0, sizeof(visited));
    order_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            dfs1(i);
        }
    }
    
    memset(visited, 0, sizeof(visited));
    comp_cnt = 0;
    for (int i = order_cnt - 1; i >= 0; i--) {
        int u = order[i];
        if (!visited[u]) {
            dfs2(u, comp_cnt++);
        }
    }
    
    printf("%d\n", comp_cnt);
    for (int i = 1; i <= n; i++) {
        printf("%d ", comp[i] + 1);
    }
    printf("\n");
    
    return 0;
}