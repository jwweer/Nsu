#include <stdio.h>
#include <stdlib.h>

#define MAXQ 500005

typedef struct Node {
    int value;
    int prev;
} Node;

Node stack[MAXQ];
int top[MAXQ];
int version_cnt = 0;

void push(int x) {
    version_cnt++;
    stack[version_cnt].value = x;
    stack[version_cnt].prev = top[version_cnt - 1];
    top[version_cnt] = version_cnt;
}

void pop() {
    version_cnt++;
    top[version_cnt] = stack[top[version_cnt - 1]].prev;
}

void query(int v) {
    if (top[v] == -1) {
        printf("-\n");
        return;
    }
    int cur = top[v];
    while (cur != -1) {
        printf("%d ", stack[cur].value);
        cur = stack[cur].prev;
    }
    printf("\n");
}

int main() {
    int Q;
    scanf("%d", &Q);

    top[0] = -1;
    version_cnt = 0;

    for (int i = 0; i < Q; i++) {
        char op[2];
        scanf("%s", op);
        if (op[0] == '+') {
            int x;
            scanf("%d", &x);
            push(x);
        } else if (op[0] == '-') {
            pop();
        } else if (op[0] == '?') {
            int v;
            scanf("%d", &v);
            query(v);
        }
    }

    return 0;
}