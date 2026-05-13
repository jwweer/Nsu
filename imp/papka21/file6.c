#include <stdio.h>
#include <stdlib.h>

#define MAXQ 500005

typedef struct {
    int value;
    int prev;
} Node;

Node nodes[MAXQ];
int top[MAXQ];
int node_cnt;
int version;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int Q;
    scanf("%d", &Q);
    
    top[0] = -1;
    node_cnt = 0;
    version = 0;
    
    for (int i = 0; i < Q; i++) {
        char op[2];
        scanf("%s", op);
        
        if (op[0] == '+') {
            int x;
            scanf("%d", &x);
            
            node_cnt++;
            nodes[node_cnt].value = x;
            nodes[node_cnt].prev = top[version];
            
            version++;
            top[version] = node_cnt;
        }
        else if (op[0] == '-') {
            version++;
            top[version] = nodes[top[version - 1]].prev;
        }
        else if (op[0] == '?') {
            int v;
            scanf("%d", &v);
            
            if (top[v] == -1) {
                printf("-\n");
            } else {
                int cur = top[v];
                while (cur != -1) {
                    printf("%d ", nodes[cur].value);
                    cur = nodes[cur].prev;
                }
                printf("\n");
            }
        }
    }
    
    return 0;
}