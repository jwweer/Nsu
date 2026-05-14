#include <stdio.h>
#include <string.h>

#define MAX_V 10

int m, V, E;
int graph[MAX_V][MAX_V];
int colors[MAX_V];

int isSafe(int v, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && colors[i] == c) return 0;
    }
    return 1;
}

int solve(int v) {
    if (v == V) return 1;
    
    for (int c = 1; c <= m; c++) {
        if (isSafe(v, c)) {
            colors[v] = c;
            if (solve(v + 1)) return 1;
            colors[v] = 0;
        }
    }
    return 0;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    fscanf(in, "%d", &m);
    fscanf(in, "%d", &V);
    
    memset(graph, 0, sizeof(graph));
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2) {
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    fclose(in);
    
    memset(colors, 0, sizeof(colors));
    int result = solve(0);
    
    fprintf(out, "%d\n", result);
    fclose(out);
    return 0;
}