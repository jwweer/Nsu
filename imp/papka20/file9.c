#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXN 100005
#define MAXM 200005
#define INF (1LL << 60)

typedef long long ll;

typedef struct {
    int to, id, w;
} Edge;

typedef struct {
    ll dist;
    int v;
} State;

Edge edges[MAXM];
int head[MAXN], nxt[MAXM], ecnt;
int n, m, k;
int queries[25][2];
int important[MAXN];
int imp_id[MAXN], imp_cnt;
ll dist[45][MAXN];
int prev_vertex[45][MAXN];
int prev_edge_id[45][MAXN];
State heap[MAXM * 2];
int heap_size;

void add_edge(int u, int v, int w, int id) {
    edges[ecnt].to = v;
    edges[ecnt].id = id;
    edges[ecnt].w = w;
    nxt[ecnt] = head[u];
    head[u] = ecnt++;
}

void push(State s) {
    heap[heap_size] = s;
    int i = heap_size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (heap[p].dist <= heap[i].dist) break;
        State tmp = heap[p];
        heap[p] = heap[i];
        heap[i] = tmp;
        i = p;
    }
}

State pop() {
    State res = heap[0];
    heap[0] = heap[--heap_size];
    int i = 0;
    while (1) {
        int left = i * 2 + 1;
        int right = i * 2 + 2;
        int smallest = i;
        if (left < heap_size && heap[left].dist < heap[smallest].dist) smallest = left;
        if (right < heap_size && heap[right].dist < heap[smallest].dist) smallest = right;
        if (smallest == i) break;
        State tmp = heap[i];
        heap[i] = heap[smallest];
        heap[smallest] = tmp;
        i = smallest;
    }
    return res;
}

void dijkstra(int start, int idx) {
    for (int i = 1; i <= n; i++) {
        dist[idx][i] = INF;
        prev_vertex[idx][i] = -1;
        prev_edge_id[idx][i] = -1;
    }
    dist[idx][start] = 0;
    heap_size = 0;
    push((State){0, start});
    
    while (heap_size > 0) {
        State cur = pop();
        if (cur.dist != dist[idx][cur.v]) continue;
        int u = cur.v;
        
        for (int e = head[u]; e != -1; e = nxt[e]) {
            int v = edges[e].to;
            int w = edges[e].w;
            int id = edges[e].id;
            
            if (dist[idx][u] + w < dist[idx][v]) {
                dist[idx][v] = dist[idx][u] + w;
                prev_vertex[idx][v] = u;
                prev_edge_id[idx][v] = id;
                push((State){dist[idx][v], v});
            }
        }
    }
}

int main() {
    scanf("%d %d %d", &n, &m, &k);
    
    for (int i = 0; i < k; i++) {
        scanf("%d %d", &queries[i][0], &queries[i][1]);
        important[queries[i][0]] = 1;
        important[queries[i][1]] = 1;
    }
    
    memset(head, -1, sizeof(head));
    ecnt = 0;
    
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w, i + 1);
    }
    
    imp_cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (important[i]) {
            imp_id[i] = imp_cnt++;
        }
    }
    
    for (int i = 1; i <= n; i++) {
        if (important[i]) {
            dijkstra(i, imp_id[i]);
        }
    }
    
    for (int q = 0; q < k; q++) {
        int A = queries[q][0], B = queries[q][1];
        int idx = imp_id[A];
        
        if (dist[idx][B] == INF) {
            printf("DOOMED\n");
            continue;
        }
        
        int path_edges[MAXM];
        int edge_cnt = 0;
        int cur = B;
        
        while (cur != A) {
            int eid = prev_edge_id[idx][cur];
            path_edges[edge_cnt++] = eid;
            cur = prev_vertex[idx][cur];
        }
        
        printf("quarantine %lld %d", dist[idx][B], edge_cnt);
        for (int i = edge_cnt - 1; i >= 0; i--) {
            printf(" %d", path_edges[i]);
        }
        printf("\n");
    }
    
    return 0;
}