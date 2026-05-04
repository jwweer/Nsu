#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 6005
#define MAXM 1000005

typedef struct Edge {
    int to, cap, flow, rev;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int level[MAXN], iter[MAXN];
int N, M, O, s, t, total_nodes;
int edge_u[10005], edge_v[10005];

void add_edge(int from, int to, int cap) {
    Edge *e1 = malloc(sizeof(Edge));
    Edge *e2 = malloc(sizeof(Edge));
    
    e1->to = to;
    e1->cap = cap;
    e1->flow = 0;
    e1->rev = (graph[to] ? graph[to]->rev + 1 : 0);
    e1->next = graph[from];
    
    e2->to = from;
    e2->cap = 0;
    e2->flow = 0;
    e2->rev = (graph[from] ? graph[from]->rev + 1 : 0);
    e2->next = graph[to];
    
    graph[from] = e1;
    graph[to] = e2;
}

void bfs(int s) {
    memset(level, -1, total_nodes * sizeof(int));
    int queue[MAXN], front = 0, rear = 0;
    level[s] = 0;
    queue[rear++] = s;
    
    while (front < rear) {
        int v = queue[front++];
        for (Edge *e = graph[v]; e; e = e->next) {
            if (e->cap > e->flow && level[e->to] < 0) {
                level[e->to] = level[v] + 1;
                queue[rear++] = e->to;
            }
        }
    }
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    for (Edge *e = graph[v]; e; e = e->next) {
        if (e->cap > e->flow && level[v] < level[e->to]) {
            int d = dfs(e->to, t, f < e->cap - e->flow ? f : e->cap - e->flow);
            if (d > 0) {
                e->flow += d;
                for (Edge *rev = graph[e->to]; rev; rev = rev->next) {
                    if (rev->to == v && rev->cap > rev->flow) {
                        rev->flow -= d;
                        break;
                    }
                }
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
        for (int i = 0; i < total_nodes; i++) iter[i] = 0;
        int f;
        while ((f = dfs(s, t, INT_MAX)) > 0) {
            flow += f;
        }
    }
}

int in(int v) {
    return v * 2;
}

int out(int v) {
    return v * 2 + 1;
}

void recover_paths(int flow_val) {
    printf("%d\n", flow_val);
    
    int used[MAXN] = {0};
    
    for (int p = 0; p < flow_val; p++) {
        int path[MAXN], path_len = 0;
        int cur = out(s);
        
        while (cur != in(t)) {
            path[path_len++] = cur;
            used[cur] = 1;
            int found = 0;
            for (Edge *e = graph[cur]; e; e = e->next) {
                if (e->flow > 0 && e->cap > 0 && !used[e->to]) {
                    cur = e->to;
                    found = 1;
                    break;
                }
            }
            if (!found) break;
        }
        path[path_len++] = in(t);
        
        int vertices[MAXN], cnt = 0;
        for (int i = 0; i < path_len; i++) {
            int v = path[i] / 2;
            if (cnt == 0 || vertices[cnt-1] != v) {
                vertices[cnt++] = v;
            }
        }
        
        printf("%d\n", cnt - 1);
        for (int i = 0; i < cnt - 1; i++) {
            int u = vertices[i];
            int v = vertices[i+1];
            int edge_num = -1;
            for (int j = 0; j < M; j++) {
                if ((edge_u[j] == u && edge_v[j] == v) || 
                    (O == 0 && edge_u[j] == v && edge_v[j] == u)) {
                    edge_num = j + 1;
                    break;
                }
            }
            printf("%d %d %d\n", u, edge_num, v);
        }
    }
}

int main() {
    scanf("%d %d %d", &N, &M, &O);
    scanf("%d %d", &s, &t);
    
    total_nodes = 2 * N + 2;
    for (int i = 0; i < total_nodes; i++) graph[i] = NULL;
    
    for (int v = 1; v <= N; v++) {
        if (v == s || v == t) {
            add_edge(in(v), out(v), INT_MAX);
        } else {
            add_edge(in(v), out(v), 1);
        }
    }
    
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edge_u[i] = a;
        edge_v[i] = b;
        
        add_edge(out(a), in(b), INT_MAX);
        if (O == 0) {
            add_edge(out(b), in(a), INT_MAX);
        }
    }
    
    int flow = max_flow(out(s), in(t));
    recover_paths(flow);
    
    return 0;
}