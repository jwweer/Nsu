#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 2005
#define MAXM 6005
#define INF (1LL << 60)

typedef long long ll;

typedef struct {
    int u, v;
    ll w;
} Edge;

Edge edges[MAXM];
int head[MAXN], to[MAXM], nxt[MAXM], ecnt;
ll dist[MAXN];
int reachable[MAXN];
int neg_cycle[MAXN];
int visited[MAXN];
int n, m, s;

void add_edge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void dfs_reachable(int u) {
    reachable[u] = 1;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (!reachable[v]) {
            dfs_reachable(v);
        }
    }
}

void dfs_neg(int u) {
    neg_cycle[u] = 1;
    for (int e = head[u]; e != -1; e = nxt[e]) {
        int v = to[e];
        if (!neg_cycle[v]) {
            dfs_neg(v);
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &s);
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        scanf("%d %d %lld", &u, &v, &w);
        edges[i] = (Edge){u, v, w};
        add_edge(u, v);
    }
    
    for (int i = 1; i <= n; i++) {
        reachable[i] = 0;
    }
    dfs_reachable(s);
    
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    
    for (int i = 1; i < n; i++) {
        int updated = 0;
        for (int j = 0; j < m; j++) {
            int u = edges[j].u, v = edges[j].v;
            ll w = edges[j].w;
            if (!reachable[u]) continue;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if (!updated) break;
    }
    
    for (int i = 1; i <= n; i++) {
        neg_cycle[i] = 0;
    }
    
    for (int j = 0; j < m; j++) {
        int u = edges[j].u, v = edges[j].v;
        ll w = edges[j].w;
        if (!reachable[u]) continue;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            dfs_neg(v);
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (!reachable[i]) {
            printf("*\n");
        } else if (neg_cycle[i]) {
            printf("-\n");
        } else {
            printf("%lld\n", dist[i]);
        }
    }
    
    return 0;
}