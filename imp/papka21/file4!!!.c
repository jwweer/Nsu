#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 3005
#define MAXM 600005

typedef struct Edge {
    int to, weight;
    struct Edge *next;
} Edge;

Edge *graph[MAXN];
int dist[MAXN];
int prev[MAXN];
int visited[MAXN];

void add_edge(int u, int v, int w) {
    Edge *e = malloc(sizeof(Edge));
    e->to = v;
    e->weight = w;
    e->next = graph[u];
    graph[u] = e;
    
    e = malloc(sizeof(Edge));
    e->to = u;
    e->weight = w;
    e->next = graph[v];
    graph[v] = e;
}

typedef struct {
    int vertex;
    int dist;
} QueueItem;

QueueItem heap[MAXM];
int heap_size;

void heap_push(int v, int d) {
    int i = heap_size++;
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (heap[parent].dist <= d) break;
        heap[i] = heap[parent];
        i = parent;
    }
    heap[i].vertex = v;
    heap[i].dist = d;
}

QueueItem heap_pop() {
    QueueItem top = heap[0];
    heap_size--;
    QueueItem last = heap[heap_size];
    
    int i = 0;
    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;
        
        if (left < heap_size && heap[left].dist < heap[smallest].dist)
            smallest = left;
        if (right < heap_size && heap[right].dist < heap[smallest].dist)
            smallest = right;
        
        if (smallest == i) break;
        
        heap[i] = heap[smallest];
        i = smallest;
    }
    heap[i] = last;
    
    return top;
}

int dijkstra(int s, int t, int n) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    heap_size = 0;
    
    dist[s] = 0;
    heap_push(s, 0);
    
    while (heap_size > 0) {
        QueueItem cur = heap_pop();
        int u = cur.vertex;
        int d = cur.dist;
        
        if (d != dist[u]) continue;
        if (u == t) break;
        
        for (Edge *e = graph[u]; e; e = e->next) {
            int v = e->to;
            int nd = d + e->weight;
            if (nd < dist[v]) {
                dist[v] = nd;
                prev[v] = u;
                heap_push(v, nd);
            }
        }
    }
    
    return dist[t];
}

int get_path(int t, int *path) {
    int cnt = 0;
    int cur = t;
    while (cur != -1) {
        path[cnt++] = cur;
        cur = prev[cur];
    }
    for (int i = 0; i < cnt / 2; i++) {
        int tmp = path[i];
        path[i] = path[cnt - 1 - i];
        path[cnt - 1 - i] = tmp;
    }
    return cnt;
}

int main() {
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);
    
    int queries[20][2];
    for (int i = 0; i < K; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
    }
    
    for (int i = 0; i < M; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
    }
    
    for (int q = 0; q < K; q++) {
        int S = queries[q][0];
        int T = queries[q][1];
        
        int time = dijkstra(S, T, N);
        
        if (time == INT_MAX) {
            printf("NO\n");
        } else {
            int path[MAXN];
            int cnt = get_path(T, path);
            printf("YES %d %d", time, cnt);
            for (int i = 0; i < cnt; i++) {
                printf(" %d", path[i]);
            }
            printf("\n");
        }
    }
    
    for (int i = 1; i <= N; i++) {
        Edge *e = graph[i];
        while (e) {
            Edge *next = e->next;
            free(e);
            e = next;
        }
    }
    
    return 0;
}