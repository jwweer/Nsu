#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 105
#define MAXK 10000

int cap[MAXN][MAXN];
int parent[MAXN];
int N, K;

int bfs(int s, int t) {
    int queue[MAXN];
    int front = 0, rear = 0;
    int visited[MAXN] = {0};

    queue[rear++] = s;
    visited[s] = 1;
    parent[s] = -1;

    while (front < rear) {
        int u = queue[front++];
        for (int v = 1; v <= N; v++) {
            if (!visited[v] && cap[u][v] > 0) {
                queue[rear++] = v;
                parent[v] = u;
                visited[v] = 1;
                if (v == t) return 1;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;

    while (bfs(s, t)) {
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
    return flow;
}

int main() {
    scanf("%d %d", &N, &K);

    memset(cap, 0, sizeof(cap));

    for (int i = 0; i < K; i++) {
        int v, u, c;
        scanf("%d %d %d", &v, &u, &c);
        cap[v][u] += c;
        cap[u][v] += c;
    }

    int result = max_flow(1, N);
    printf("%d\n", result);

    return 0;
}