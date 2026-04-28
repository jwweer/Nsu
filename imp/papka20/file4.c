#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 5005
#define MAXM 50005
#define INF (1LL << 60)

typedef long long ll;

typedef struct {
    int to, w;
} Edge;

Edge edges[MAXM];
int head[MAXN], nxt[MAXM], ecnt;
ll dist[MAXN];
int parent[MAXN];
int in_queue[MAXN];
int queue[MAXN * 10];
int n, m, k;
int friends[55];

void add_edge(int u, int v, int w) {
    edges[ecnt].to = v;
    edges[ecnt].w = w;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void spfa(int start) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        parent[i] = -1;
        in_queue[i] = 0;
    }
    dist[start] = 0;
    
    int front = 0, rear = 0;
    queue[rear++] = start;
    in_queue[start] = 1;
    
    while (front < rear) {
        int u = queue[front++];
        in_queue[u] = 0;
        
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = edges[e].to;
            int w = edges[e].w;
            
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                
                if (!in_queue[v]) {
                    queue[rear++] = v;
                    in_queue[v] = 1;
                }
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < k; i++) {
        scanf("%d", &friends[i]);
    }
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int a, b, w;
        scanf("%d %d %d", &a, &b, &w);
        add_edge(a, b, w);
    }
    
    spfa(1);
    
    int path[MAXN];
    for (int i = 0; i < k; i++) {
        int target = friends[i];
        
        int path_len = 0;
        int cur = target;
        while (cur != -1) {
            path[path_len++] = cur;
            cur = parent[cur];
        }
        
        printf("%lld %d", dist[target], path_len);
        for (int j = path_len - 1; j >= 0; j--) {
            printf(" %d", path[j]);
        }
        printf("\n");
    }
    
    return 0;
}