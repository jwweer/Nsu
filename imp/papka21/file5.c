#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PIXELS 160005

typedef struct Edge {
    int to, rev;
    int cap, flow;
} Edge;

Edge* graph[MAX_PIXELS];
int graph_size[MAX_PIXELS];
int graph_cap[MAX_PIXELS];

int level[MAX_PIXELS];
int iter[MAX_PIXELS];

int h, w, total_nodes;
int src, sink;

void add_edge(int from, int to, int cap) {
    Edge e1 = {to, graph_size[to], cap, 0};
    Edge e2 = {from, graph_size[from], 0, 0};
    
    if (graph_size[from] >= graph_cap[from]) {
        graph_cap[from] = graph_cap[from] == 0 ? 4 : graph_cap[from] * 2;
        graph[from] = realloc(graph[from], graph_cap[from] * sizeof(Edge));
    }
    if (graph_size[to] >= graph_cap[to]) {
        graph_cap[to] = graph_cap[to] == 0 ? 4 : graph_cap[to] * 2;
        graph[to] = realloc(graph[to], graph_cap[to] * sizeof(Edge));
    }
    
    graph[from][graph_size[from]++] = e1;
    graph[to][graph_size[to]++] = e2;
}

void bfs(int s) {
    int queue[MAX_PIXELS];
    int front = 0, rear = 0;
    
    for (int i = 0; i < total_nodes; i++) {
        level[i] = -1;
    }
    
    level[s] = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < graph_size[v]; i++) {
            Edge *e = &graph[v][i];
            if (e->cap > e->flow && level[e->to] < 0) {
                level[e->to] = level[v] + 1;
                queue[rear++] = e->to;
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    
    for (; iter[v] < graph_size[v]; iter[v]++) {
        Edge *e = &graph[v][iter[v]];
        if (e->cap > e->flow && level[v] < level[e->to]) {
            int d = dfs(e->to, t, f < e->cap - e->flow ? f : e->cap - e->flow);
            if (d > 0) {
                e->flow += d;
                graph[e->to][e->rev].flow -= d;
                return d;
            }
        }
    }
    return 0;
}

int max_flow(int s, int t) {
    int flow = 0;
    while (1) {
        bfs(s);
        if (level[t] < 0) return flow;
        
        for (int i = 0; i < total_nodes; i++) {
            iter[i] = 0;
        }
        
        int f;
        while ((f = dfs(s, t, INT_MAX)) > 0) {
            flow += f;
        }
    }
}

int pixel_id(int r, int c) {
    return (r - 1) * w + (c - 1) + 2;
}

int main() {
    scanf("%d %d", &h, &w);
    
    total_nodes = h * w + 2;
    src = 0;
    sink = 1;
    
    for (int i = 0; i < total_nodes; i++) {
        graph[i] = NULL;
        graph_size[i] = 0;
        graph_cap[i] = 0;
    }
    
    for (int r = 1; r <= h; r++) {
        for (int c = 1; c <= w; c++) {
            int a, b;
            scanf("%d %d", &a, &b);
            int id = pixel_id(r, c);
            add_edge(src, id, a);
            add_edge(id, sink, b);
        }
    }
    
    int m;
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int r1, c1, r2, c2, p;
        scanf("%d %d %d %d %d", &r1, &c1, &r2, &c2, &p);
        int id1 = pixel_id(r1, c1);
        int id2 = pixel_id(r2, c2);
        add_edge(id1, id2, p);
        add_edge(id2, id1, p);
    }
    
    int min_cut_value = max_flow(src, sink);
    
    printf("%d\n", min_cut_value);
    
    int reachable[MAX_PIXELS] = {0};
    int queue[MAX_PIXELS];
    int front = 0, rear = 0;
    queue[rear++] = src;
    reachable[src] = 1;
    
    while (front < rear) {
        int v = queue[front++];
        for (int i = 0; i < graph_size[v]; i++) {
            Edge *e = &graph[v][i];
            if (e->cap > e->flow && !reachable[e->to]) {
                reachable[e->to] = 1;
                queue[rear++] = e->to;
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
    
    for (int i = 0; i < total_nodes; i++) {
        if (graph[i]) free(graph[i]);
    }
    
    return 0;
}