#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 105

typedef struct {
    int x, y, dist;
} Point;

int M, N;
char maze[MAX_N][MAX_N + 1];
int visited[MAX_N][MAX_N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
Point queue[MAX_N * MAX_N];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    
    scanf("%d %d\n", &M, &N);
    
    int startX = -1, startY = -1;
    int endX = -1, endY = -1;
    
    for (int i = 0; i < M; i++) {
        fgets(maze[i], MAX_N + 1, stdin);
        maze[i][strcspn(maze[i], "\n")] = '\0';
        for (int j = 0; j < N; j++) {
            if (maze[i][j] == 'S') {
                startX = i;
                startY = j;
                maze[i][j] = '.';
            } else if (maze[i][j] == 'F') {
                endX = i;
                endY = j;
                maze[i][j] = '.';
            }
        }
    }
    
    memset(visited, 0, sizeof(visited));
    
    int front = 0, rear = 0;
    queue[rear++] = (Point){startX, startY, 0};
    visited[startX][startY] = 1;
    
    int result = -1;
    
    while (front < rear) {
        Point p = queue[front++];
        
        if (p.x == endX && p.y == endY) {
            result = p.dist;
            break;
        }
        
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N && 
                maze[nx][ny] == '.' && !visited[nx][ny]) {
                visited[nx][ny] = 1;
                queue[rear++] = (Point){nx, ny, p.dist + 1};
            }
        }
    }
    
    printf("%d\n", result);
    
    return 0;
}