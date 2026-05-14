#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 105

int cap[MAXN][MAXN];
int parent[MAXN];
int N, M, S, T;

int bfs() {
    int q[MAXN], front = 0, rear = 0;
    int vis[MAXN] = {0};
    q[rear++] = S;
    vis[S] = 1;
    parent[S] = -1;

    while (front < rear) {
        int u = q[front++];
        for (int v = 1; v <= N; v++) {
            if (!vis[v] && cap[u][v] > 0) {
                q[rear++] = v;
                parent[v] = u;
                vis[v] = 1;
                if (v == T) return 1;
            }
        }
    }
    return 0;
}

int main() {
    scanf("%d %d", &N, &M);
    scanf("%d %d", &S, &T);

    memset(cap, 0, sizeof(cap));

    int u_[M], v_[M], c_[M];

    for (int i = 0; i < M; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);
        u_[i] = u; v_[i] = v; c_[i] = c;
        cap[u][v] += c;
        cap[v][u] += c;
    }

    int flow = 0;
    while (bfs()) {
        int path_flow = INT_MAX;
        for (int v = T; v != S; v = parent[v]) {
            int u = parent[v];
            if (cap[u][v] < path_flow)
                path_flow = cap[u][v];
        }
        for (int v = T; v != S; v = parent[v]) {
            int u = parent[v];
            cap[u][v] -= path_flow;
            cap[v][u] += path_flow;
        }
        flow += path_flow;
    }

    int reach[MAXN] = {0};
    int q[MAXN], front = 0, rear = 0;
    q[rear++] = S;
    reach[S] = 1;
    while (front < rear) {
        int u = q[front++];
        for (int v = 1; v <= N; v++) {
            if (!reach[v] && cap[u][v] > 0) {
                reach[v] = 1;
                q[rear++] = v;
            }
        }
    }

    int cut_edges[MAXN][2];
    int cut_cnt = 0;
    for (int i = 0; i < M; i++) {
        if (reach[u_[i]] && !reach[v_[i]]) {
            cut_edges[cut_cnt][0] = u_[i];
            cut_edges[cut_cnt][1] = v_[i];
            cut_cnt++;
        } else if (reach[v_[i]] && !reach[u_[i]]) {
            cut_edges[cut_cnt][0] = v_[i];
            cut_edges[cut_cnt][1] = u_[i];
            cut_cnt++;
        }
    }

    printf("%d %d\n", flow, cut_cnt);
    for (int i = 0; i < cut_cnt; i++) {
        printf("%d %d\n", cut_edges[i][0], cut_edges[i][1]);
    }

    return 0;
}