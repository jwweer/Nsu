#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 10005
#define MAX_M 100005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* graph[MAX_N];
Edge edges[MAX_M * 2];
int edge_idx = 0;
int visited[MAX_N];
int path[MAX_N];
int path_len = 0;

void add_edge(int u, int v) {
    edges[edge_idx].to = v;
    edges[edge_idx].next = graph[u];
    graph[u] = &edges[edge_idx++];
}

int dfs(int u, int depth, int n) {
    path[depth] = u;
    if (depth + 1 == n) return 1;
    
    visited[u] = 1;
    for (Edge* e = graph[u]; e; e = e->next) {
        int v = e->to;
        if (!visited[v]) {
            if (dfs(v, depth + 1, n)) return 1;
        }
    }
    visited[u] = 0;
    return 0;
}

int main() {
    FILE *input = fopen("input.txt", "r");
    FILE *output = fopen("output.txt", "w");
    
    int n, m;
    fscanf(input, "%d %d", &n, &m);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        fscanf(input, "%d %d", &x, &y);
        x--; y--;
        add_edge(x, y);
        add_edge(y, x);
    }
    
    for (int start = 0; start < n; start++) {
        memset(visited, 0, sizeof(visited));
        if (dfs(start, 0, n)) {
            fprintf(output, "%d\n", n);
            for (int i = 0; i < n; i++) {
                fprintf(output, "%d ", path[i] + 1);
            }
            fprintf(output, "\n");
            break;
        }
    }
    
    fclose(input);
    fclose(output);
    return 0;
}