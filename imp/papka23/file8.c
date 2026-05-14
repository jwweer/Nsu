#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int x, y;
    double p;
    double dist;
    double profit;
} City;

int cmp(const void *a, const void *b) {
    City *ca = (City*)a;
    City *cb = (City*)b;
    if (cb->profit > ca->profit) return 1;
    if (cb->profit < ca->profit) return -1;
    return 0;
}

int main() {
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    
    int N;
    double C, D;
    fscanf(in, "%d %lf %lf", &N, &C, &D);
    
    City *cities = (City*)malloc(N * sizeof(City));
    
    for (int i = 0; i < N; i++) {
        fscanf(in, "%d %d %lf", &cities[i].x, &cities[i].y, &cities[i].p);
        cities[i].dist = sqrt(cities[i].x*cities[i].x + cities[i].y*cities[i].y);
    }
    
    int firstBatch = N / 10;
    if (firstBatch < 1) firstBatch = 1;
    
    double decay = 1.0;
    for (int i = 0; i < N; i++) {
        double price = cities[i].p;
        if (i >= firstBatch) {
            price *= decay;
            decay *= D;
        }
        cities[i].profit = price - C * cities[i].dist;
    }
    
    qsort(cities, N, sizeof(City), cmp);
    
    double totalProfit = 0;
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (cities[i].profit > 0) {
            totalProfit += cities[i].profit;
            count++;
            fprintf(out, "%d %d\n", cities[i].x, cities[i].y);
        }
    }
    
    fclose(in);
    fclose(out);
    free(cities);
    return 0;
}