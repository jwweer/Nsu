#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_M 200005

int M, N;
int *adj[MAX_N];
int *adj_len[MAX_N];
int adj_count[MAX_N];
int dist[MAX_N];
int queue[MAX_N];

void add_edge(int u, int v) {
    adj_count[u]++;
    adj[u] = realloc(adj[u], adj_count[u] * sizeof(int));
    adj[u][adj_count[u] - 1] = v;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d %d", &M, &N);
    
    for (int i = 1; i <= M; i++) {
        adj[i] = NULL;
        adj_count[i] = 0;
    }
    
    for (int i = 0; i < N; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);
    }
    
    for (int i = 1; i <= M; i++) {
        dist[i] = -1;
    }
   
    int head = 0, tail = 0;
    dist[1] = 0;
    queue[tail++] = 1;
    
    while (head < tail) {
        int u = queue[head++];
        for (int i = 0; i < adj_count[u]; i++) {
            int v = adj[u][i];
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                queue[tail++] = v;
            }
        }
    }
    
    for (int i = 1; i <= M; i++) {
        printf("%d\n", dist[i]);
    }
    
    for (int i = 1; i <= M; i++) {
        free(adj[i]);
    }
    
    return 0;
}