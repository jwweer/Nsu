#include <stdio.h>
#include <math.h>

typedef struct {
    double c0, c1, c2, c3;
} Poly;

typedef struct {
    double l, r;
    Poly x, y, z;
} Span;

double eval_poly(const Poly* p, double t, double l) {
    double dt = t - l;
    return p->c0 + p->c1 * dt + p->c2 * dt * dt + p->c3 * dt * dt * dt;
}

double eval_derivative(const Poly* p, double t, double l) {
    double dt = t - l;
    return p->c1 + 2.0 * p->c2 * dt + 3.0 * p->c3 * dt * dt;
}

double integrand(double t, const Span* span) {
    double dx = eval_derivative(&span->x, t, span->l);
    double dy = eval_derivative(&span->y, t, span->l);
    double dz = eval_derivative(&span->z, t, span->l);
    return sqrt(dx * dx + dy * dy + dz * dz);
}

double simpson(const Span* span, int steps) {
    double a = span->l;
    double b = span->r;
    double h = (b - a) / steps;
    double sum = integrand(a, span) + integrand(b, span);
    
    for (int i = 1; i < steps; i++) {
        double t = a + i * h;
        if (i % 2 == 0) {
            sum += 2.0 * integrand(t, span);
        } else {
            sum += 4.0 * integrand(t, span);
        }
    }
    
    return sum * h / 3.0;
}

int main() {
    FILE* fin = fopen("input.txt", "r");
    FILE* fout = fopen("output.txt", "w");
    
    int N;
    fscanf(fin, "%d", &N);
    
    Span spans[1000];
    double total_length = 0.0;
    
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%lf %lf", &spans[i].l, &spans[i].r);
        
        fscanf(fin, "%lf %lf %lf %lf", 
               &spans[i].x.c0, &spans[i].x.c1, &spans[i].x.c2, &spans[i].x.c3);
        fscanf(fin, "%lf %lf %lf %lf", 
               &spans[i].y.c0, &spans[i].y.c1, &spans[i].y.c2, &spans[i].y.c3);
        fscanf(fin, "%lf %lf %lf %lf", 
               &spans[i].z.c0, &spans[i].z.c1, &spans[i].z.c2, &spans[i].z.c3);
        
        int steps = 1000; // Можно увеличить для большей точности
        total_length += simpson(&spans[i], steps);
    }
    
    fprintf(fout, "%.15f\n", total_length);
    
    fclose(fin);
    fclose(fout);
    return 0;
}