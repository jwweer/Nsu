#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAXN 160005
#define MAXM 2000000

typedef struct {
    int to, rev;
    ll cap;
} Edge;

Edge edges[MAXM];
int edge_count = 0;
int first_edge[MAXN], next_edge[MAXM];

int level[MAXN], queue[MAXN], ptr[MAXN];
int rows, cols, total_nodes, source, sink;

void add_directed(int from, int to, ll cap) {
    edges[edge_count] = (Edge){to, edge_count + 1, cap};
    next_edge[edge_count] = first_edge[from];
    first_edge[from] = edge_count++;
    
    edges[edge_count] = (Edge){from, edge_count - 1, 0};
    next_edge[edge_count] = first_edge[to];
    first_edge[to] = edge_count++;
}

void add_undirected(int u, int v, ll w) {
    add_directed(u, v, w);
    add_directed(v, u, w);
}

int bfs() {
    memset(level, -1, total_nodes * sizeof(int));
    int head = 0, tail = 0;
    queue[tail++] = source;
    level[source] = 0;
    
    while (head < tail) {
        int v = queue[head++];
        for (int e = first_edge[v]; e != -1; e = next_edge[e]) {
            if (edges[e].cap > 0 && level[edges[e].to] == -1) {
                level[edges[e].to] = level[v] + 1;
                queue[tail++] = edges[e].to;
            }
        }
    }
    return level[sink] != -1;
}

ll dfs(int v, ll flow) {
    if (v == sink) return flow;
    for (int *p = &ptr[v]; *p != -1; *p = next_edge[*p]) {
        int e = *p;
        if (edges[e].cap > 0 && level[edges[e].to] == level[v] + 1) {
            ll pushed = dfs(edges[e].to, flow < edges[e].cap ? flow : edges[e].cap);
            if (pushed) {
                edges[e].cap -= pushed;
                edges[edges[e].rev].cap += pushed;
                return pushed;
            }
        }
    }
    return 0;
}

ll max_flow() {
    ll flow = 0;
    while (bfs()) {
        for (int i = 0; i < total_nodes; i++) ptr[i] = first_edge[i];
        while (1) {
            ll pushed = dfs(source, 1LL << 60);
            if (!pushed) break;
            flow += pushed;
        }
    }
    return flow;
}

int pixel_id(int r, int c) {
    return r * cols + c;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    memset(first_edge, -1, sizeof(first_edge));
    
    scanf("%d %d", &rows, &cols);
    int cells = rows * cols;
    source = cells;
    sink = cells + 1;
    total_nodes = cells + 2;
    
    ll A[400][400], B[400][400];
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%lld %lld", &A[i][j], &B[i][j]);
        }
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int id = pixel_id(i, j);
            if ((i + j) % 2 == 0) {
                add_directed(source, id, A[i][j]);
                add_directed(id, sink, B[i][j]);
            } else {
                add_directed(source, id, B[i][j]);
                add_directed(id, sink, A[i][j]);
            }
        }
    }
    
    int m;
    scanf("%d", &m);
    
    ll total_bonus = 0;
    
    for (int k = 0; k < m; k++) {
        int r1, c1, r2, c2;
        ll p;
        scanf("%d %d %d %d %lld", &r1, &c1, &r2, &c2, &p);
        r1--; c1--; r2--; c2--;
        int u = pixel_id(r1, c1);
        int v = pixel_id(r2, c2);
        add_undirected(u, v, p);
        total_bonus += p;
    }
    
    ll mincut = max_flow();
    ll answer = mincut - total_bonus;
    
    printf("%lld\n", answer);
    
    int reachable[MAXN] = {0};
    int q[MAXN], front = 0, rear = 0;
    q[rear++] = source;
    reachable[source] = 1;
    
    while (front < rear) {
        int v = q[front++];
        for (int e = first_edge[v]; e != -1; e = next_edge[e]) {
            if (edges[e].cap > 0 && !reachable[edges[e].to]) {
                reachable[edges[e].to] = 1;
                q[rear++] = edges[e].to;
            }
        }
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int id = pixel_id(i, j);
            int is_reachable = reachable[id];
            int label;
            if ((i + j) % 2 == 0) {
                label = is_reachable ? 1 : 0;
            } else {
                label = is_reachable ? 0 : 1;
            }
            printf("%d", label);
        }
        printf("\n");
    }
    
    return 0;
}