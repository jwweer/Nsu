#include <stdio.h>
#include <stdlib.h>

#define MAXQ 500005

typedef struct {
    int value;
    int prev;
} Node;

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    int Q;
    scanf("%d", &Q);
    
    Node* versions = (Node*)malloc((Q + 1) * sizeof(Node));
    versions[0].prev = -1;
    versions[0].value = 0;
    
    int current = 0;
    
    for (int i = 1; i <= Q; i++) {
        char op;
        scanf(" %c", &op);
        
        if (op == '+') {
            int x;
            scanf("%d", &x);
            versions[i].value = x;
            versions[i].prev = current;
            current = i;
        }
        else if (op == '-') {
            versions[i].prev = versions[current].prev;
            current = i;
        }
        else if (op == '?') {
            int v;
            scanf("%d", &v);
            
            if (versions[v].prev == -1) {
                printf("-\n");
            } else {
                int* arr = (int*)malloc(MAXQ * sizeof(int));
                int cnt = 0;
                int cur = v;
                while (cur != -1 && versions[cur].prev != -1) {
                    arr[cnt++] = versions[cur].value;
                    cur = versions[cur].prev;
                }
                for (int j = 0; j < cnt; j++) {
                    if (j > 0) printf(" ");
                    printf("%d", arr[j]);
                }
                printf("\n");
                free(arr);
            }
        }
    }
    
    free(versions);
    return 0;
}