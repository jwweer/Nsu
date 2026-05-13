#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXQ 500005

int stack[MAXQ];
int prev_idx[MAXQ];
int version_top[MAXQ];
int cur_version;
int cur_node;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int Q;
    scanf("%d", &Q);
    
    cur_version = 0;
    cur_node = 0;
    version_top[0] = -1;
    
    for (int i = 0; i < Q; i++) {
        char op[3];
        scanf("%s", op);
        
        if (op[0] == '+') {
            int x;
            scanf("%d", &x);
            
            cur_node++;
            stack[cur_node] = x;
            prev_idx[cur_node] = version_top[cur_version];
            
            cur_version++;
            version_top[cur_version] = cur_node;
        }
        else if (op[0] == '-') {
            cur_version++;
            version_top[cur_version] = prev_idx[version_top[cur_version - 1]];
        }
        else if (op[0] == '?') {
            int v;
            scanf("%d", &v);
            
            if (version_top[v] == -1) {
                printf("-\n");
                continue;
            }
            
            int current = version_top[v];
            int first = 1;
            
            while (current != -1) {
                if (!first) printf(" ");
                printf("%d", stack[current]);
                first = 0;
                current = prev_idx[current];
            }
            printf("\n");
        }
    }
    
    return 0;
}