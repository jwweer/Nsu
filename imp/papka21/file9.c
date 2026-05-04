#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 200005
#define MAXQ 200005
#define LOG 18
#define MAXNODES (MAXN * LOG * 2 + MAXQ * LOG)

typedef struct Node {
    int left, right;
    int count;
} Node;

Node tree[MAXNODES];
int node_cnt = 0;

int roots[MAXQ + 5];
int arr[MAXN];
int values[MAXN];
int val_cnt;

int n, q;

int cmp(const void *a, const void *b) {
    return *(int*)a - *(int*)b;
}

void compress() {
    for (int i = 1; i <= n; i++) {
        values[i - 1] = arr[i];
    }
    qsort(values, n, sizeof(int), cmp);
    val_cnt = 1;
    for (int i = 1; i < n; i++) {
        if (values[i] != values[i - 1]) {
            values[val_cnt++] = values[i];
        }
    }
}

int get_index(int x) {
    int lo = 0, hi = val_cnt - 1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        if (values[mid] == x) return mid;
        if (values[mid] < x) lo = mid + 1;
        else hi = mid - 1;
    }
    return -1;
}

int build(int l, int r) {
    int v = node_cnt++;
    tree[v].count = 0;
    if (l != r) {
        int mid = (l + r) / 2;
        tree[v].left = build(l, mid);
        tree[v].right = build(mid + 1, r);
    }
    return v;
}

int update(int prev, int l, int r, int pos, int delta) {
    int v = node_cnt++;
    tree[v] = tree[prev];
    if (l == r) {
        tree[v].count += delta;
        return v;
    }
    int mid = (l + r) / 2;
    if (pos <= mid) {
        tree[v].left = update(tree[prev].left, l, mid, pos, delta);
    } else {
        tree[v].right = update(tree[prev].right, mid + 1, r, pos, delta);
    }
    tree[v].count = tree[tree[v].left].count + tree[tree[v].right].count;
    return v;
}

int query_kth(int v, int l, int r, int k) {
    if (l == r) return l;
    int mid = (l + r) / 2;
    int left_count = tree[tree[v].left].count;
    if (k <= left_count) {
        return query_kth(tree[v].left, l, mid, k);
    } else {
        return query_kth(tree[v].right, mid + 1, r, k - left_count);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &arr[i]);
    }
    
    compress();
   
    node_cnt = 0;
    int empty_root = build(0, val_cnt - 1);
 
    roots[0] = empty_root;
    for (int i = 1; i <= n; i++) {
        int idx = get_index(arr[i]);
        roots[0] = update(roots[0], 0, val_cnt - 1, idx, 1);
    }
    
    int version_cnt = 0;
    scanf("%d", &q);
    
    for (int op = 0; op < q; op++) {
        char type[4];
        scanf("%s", type);
        
        if (strcmp(type, "SET") == 0) {
            int v, i, x;
            scanf("%d %d %d", &v, &i, &x);
            
            int new_root = roots[v];
            
            int old_idx = get_index(arr[i]);
            new_root = update(new_root, 0, val_cnt - 1, old_idx, -1);
            
            int new_idx = get_index(x);
            new_root = update(new_root, 0, val_cnt - 1, new_idx, 1);
            
            arr[i] = x;
            
            version_cnt++;
            roots[version_cnt] = new_root;
            
        } else if (strcmp(type, "KTH") == 0) {
            int v, l, r, k;
            scanf("%d %d %d %d", &v, &l, &r, &k);
            printf("0\n");
        }
    }
    
    return 0;
}