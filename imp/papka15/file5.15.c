#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long long x, y;
} Point;

Point p[100005];
int used[100005];

long long cross(Point o, Point a, Point b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

long long dist2(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &p[i].x, &p[i].y);
    }
    
    int start = 0;
    for (int i = 1; i < n; i++) {
        if (p[i].y < p[start].y || (p[i].y == p[start].y && p[i].x < p[start].x)) {
            start = i;
        }
    }
    
    int hull[100005];
    int hull_size = 0;
    int cur = start;
    
    do {
        hull[hull_size++] = cur;
        used[cur] = 1;
        int nxt = (cur + 1) % n;
        for (int i = 0; i < n; i++) {
            if (i == cur) continue;
            long long cr = cross(p[cur], p[i], p[nxt]);
            if (cr > 0 || (cr == 0 && dist2(p[cur], p[i]) > dist2(p[cur], p[nxt]))) {
                nxt = i;
            }
        }
        cur = nxt;
    } while (cur != start);
    
    printf("%d\n", hull_size);
    for (int i = 0; i < hull_size; i++) {
        printf("%lld %lld\n", p[hull[i]].x, p[hull[i]].y);
    }
    
    return 0;
}