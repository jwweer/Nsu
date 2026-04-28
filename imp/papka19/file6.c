#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 5005
#define MAX_M 100005

typedef struct Edge {
    int to;
    struct Edge* next;
} Edge;

Edge* adj[MAX_N];
Edge edges[MAX_M];
int edge_idx = 0;
int in_degree[MAX_N];
int result[MAX_N];
int heap[MAX_N];
int heap_size = 0;

void add_edge(int u, int v) {
    edges[edge_idx].to = v;
    edges[edge_idx].next = adj[u];
    adj[u] = &edges[edge_idx++];
}

void push(int x) {
    int i = heap_size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p] <= x) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = x;
}

int pop() {
    int ret = heap[0];
    int x = heap[--heap_size];
    int i = 0;
    while (i * 2 + 1 < heap_size) {
        int l = i * 2 + 1;
        int r = i * 2 + 2;
        int child = l;
        if (r < heap_size && heap[r] < heap[l]) child = r;
        if (x <= heap[child]) break;
        heap[i] = heap[child];
        i = child;
    }
    heap[i] = x;
    return ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int N, M;
    scanf("%d %d", &N, &M);
    
    memset(adj, 0, sizeof(adj));
    memset(in_degree, 0, sizeof(in_degree));
    edge_idx = 0;
    
    for (int i = 0; i < M; i++) {
        int B, A;
        scanf("%d %d", &B, &A);
        add_edge(B, A);
        in_degree[A]++;
    }
    
    heap_size = 0;
    for (int i = 1; i <= N; i++) {
        if (in_degree[i] == 0) {
            push(i);
        }
    }
    
    int result_idx = 0;
    
    while (heap_size > 0) {
        int u = pop();
        result[result_idx++] = u;
        
        for (Edge* e = adj[u]; e != NULL; e = e->next) {
            int v = e->to;
            in_degree[v]--;
            if (in_degree[v] == 0) {
                push(v);
            }
        }
    }
    
    if (result_idx != N) {
        printf("bad course\n");
    } else {
        for (int i = 0; i < N; i++) {
            printf("%d ", result[i]);
        }
        printf("\n");
    }
    
    return 0;
}