#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1005

int n;
char lab[MAX][MAX];
int vis[MAX][MAX];

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

struct point {
    int x, y;
};

struct point queue[MAX * MAX];

void bfs(int sx, int sy) {
    int head = 0, tail = 0;
    
    queue[tail].x = sx;
    queue[tail].y = sy;
    tail++;
    vis[sx][sy] = 1;
    
    while (head < tail) {
        int x = queue[head].x;
        int y = queue[head].y;
        head++;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                if (lab[nx][ny] == ' ' && !vis[nx][ny]) {
                    vis[nx][ny] = 1;
                    queue[tail].x = nx;
                    queue[tail].y = ny;
                    tail++;
                }
            }
        }
    }
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    if (in == NULL || out == NULL) {
        return 1;
    }
    
    fscanf(in, "%d", &n);
    
    char line[MAX * 2];
    fgets(line, sizeof(line), in);
    
    for (int i = 0; i < n; i++) {
        fgets(line, sizeof(line), in);
       
        int len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
            len--;
        }
        
        for (int j = 0; j < n; j++) {
            if (j < len) {
                lab[i][j] = line[j];
            } else {
                lab[i][j] = ' ';
            }
        }
    }
    
    fclose(in);
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            vis[i][j] = 0;
        }
    }
    

    int start = -1;
    for (int j = 0; j < n; j++) {
        if (lab[0][j] == ' ') {
            start = j;
            break;
        }
    }
    
    if (start != -1) {
        bfs(0, start);
    }

    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (lab[i][j] == ' ' && !vis[i][j]) {
                result++;
                bfs(i, j);
            }
        }
    }
    
    fprintf(out, "%d\n", result);
    fclose(out);
    
    return 0;
}