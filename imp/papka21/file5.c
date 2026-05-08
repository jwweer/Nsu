#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 160005
#define MAXM 2000000

typedef struct Edge {
    int to, rev;
    long long cap, flow;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int level[MAXN], iter[MAXN];
int h, w, total_nodes, src, sink;

void add_edge(int from, int to, long long cap) {
    Edge *e1 = malloc(sizeof(Edge));
    Edge *e2 = malloc(sizeof(Edge));
    
    e1->to = to; e1->cap = cap; e1->flow = 0; e1->rev = 0; e1->next = graph[from];
    e2->to = from; e2->cap = 0; e2->flow = 0; e2->rev = 0; e2->next = graph[to];
    
    graph[from] = e1;
    graph[to] = e2;
    
    e1->rev = 1;
    e2->rev = 0;
}

void bfs(int s) {
    memset(level, -1, total_nodes * sizeof(int));
    int q[MAXN], front = 0, rear = 0;
    level[s] = 0;
    q[rear++] = s;
    
    while (front < rear) {
        int v = q[front++];
        for (Edge *e = graph[v]; e; e = e->next) {
            if (e->cap > e->flow && level[e->to] < 0) {
                level[e->to] = level[v] + 1;
                q[rear++] = e->to;
            }
        }
    }
}

long long dfs(int v, int t, long long f) {
    if (v == t) return f;
    for (Edge *e = graph[v]; e; e = e->next) {
        if (e->cap > e->flow && level[v] < level[e->to]) {
            long long d = dfs(e->to, t, f < e->cap - e->flow ? f : e->cap - e->flow);
            if (d > 0) {
                e->flow += d;
                Edge *rev = graph[e->to];
                for (int i = 0; i < e->rev; i++) rev = rev->next;
                rev->flow -= d;
                return d;
            }
        }
    }
    return 0;
}

long long max_flow() {
    long long flow = 0;
    while (1) {
        bfs(src);
        if (level[sink] < 0) return flow;
        memset(iter, 0, total_nodes * sizeof(int));
        long long f;
        while ((f = dfs(src, sink, LLONG_MAX)) > 0) {
            flow += f;
        }
    }
}

int pixel_id(int r, int c) {
    return (r-1)*w + c + 2;
}

int main() {
    scanf("%d %d", &h, &w);
    total_nodes = h * w + 2;
    src = 0; sink = 1;
    
    for (int i = 0; i < total_nodes; i++) graph[i] = NULL;
    
    long long sum_b = 0;
    
    for (int r = 1; r <= h; r++) {
        for (int c = 1; c <= w; c++) {
            long long a, b;
            scanf("%lld %lld", &a, &b);
            int id = pixel_id(r, c);
            add_edge(src, id, a);
            add_edge(id, sink, b);
            sum_b += b;
        }
    }
    
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int r1, c1, r2, c2;
        long long p;
        scanf("%d %d %d %d %lld", &r1, &c1, &r2, &c2, &p);
        int id1 = pixel_id(r1, c1);
        int id2 = pixel_id(r2, c2);
        add_edge(id1, id2, p);
        add_edge(id2, id1, p);
    }
    
    long long min_cut = max_flow();
    long long min_energy = sum_b - min_cut;
    
    printf("%lld\n", min_energy);
    
    int reachable[MAXN] = {0};
    int q[MAXN], front = 0, rear = 0;
    q[rear++] = src;
    reachable[src] = 1;
    
    while (front < rear) {
        int v = q[front++];
        for (Edge *e = graph[v]; e; e = e->next) {
            if (e->cap > e->flow && !reachable[e->to]) {
                reachable[e->to] = 1;
                q[rear++] = e->to;
            }
        }
    }
    
    for (int r = 1; r <= h; r++) {
        for (int c = 1; c <= w; c++) {
            int id = pixel_id(r, c);
            printf("%d", reachable[id] ? 0 : 1);
        }
        printf("\n");
    }
    
    return 0;
}