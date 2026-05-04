#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 3005
#define MAXM 20005

int N, M, O, s, t;

int cap[MAXN][MAXN];
int parent[MAXN];

int bfs() {
    int q[MAXN], front = 0, rear = 0;
    int vis[MAXN] = {0};
    q[rear++] = s;
    vis[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        int u = q[front++];
        for (int v = 1; v <= N; v++) {
            if (!vis[v] && cap[u][v] > 0) {
                q[rear++] = v;
                parent[v] = u;
                vis[v] = 1;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

int uu[MAXM], vv[MAXM];

int main() {
    scanf("%d %d %d", &N, &M, &O);
    scanf("%d %d", &s, &t);

    memset(cap, 0, sizeof(cap));

    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        uu[i] = a; vv[i] = b;
        if (O == 0) { 
            cap[a][b] += 1;
            cap[b][a] += 1;
        } else { 
            cap[a][b] += 1;
        }
    }

    int flow = 0;
    while (bfs()) {
        int path_flow = INT_MAX;
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            if (cap[u][v] < path_flow)
                path_flow = cap[u][v];
        }
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= path_flow;
            cap[v][u] += path_flow;
        }
        flow += path_flow;
    }

    printf("%d\n", flow);
    return 0;
}