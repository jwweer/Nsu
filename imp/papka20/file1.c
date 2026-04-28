#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 100005
#define MAXM 200005

int head[MAXN], to[MAXM], nxt[MAXM], indeg[MAXN];
int topo[MAXN];
int ans[MAXN];
int n, m, ecnt;

void add_edge(int u, int v) {
    to[ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
    indeg[v]++;
}

int main() {
    scanf("%d %d", &n, &m);

    memset(head, -1, sizeof(head));
    memset(indeg, 0, sizeof(indeg));
    ecnt = 0;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }

    int *queue = (int*)malloc(n * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            queue[rear++] = i;
        }
    }

    int topo_cnt = 0;
    while (front < rear) {
        int u = queue[front++];
        topo[topo_cnt++] = u;

        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = to[e];
            if (--indeg[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    if (topo_cnt != n) {
        printf("NO\n");
        free(queue);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        ans[topo[i]] = i + 1;
    }

    printf("YES\n");
    for (int i = 1; i <= n; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");

    free(queue);
    return 0;
}