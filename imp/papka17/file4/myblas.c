#include <string.h>

// Определяем константы
#define CblasRowMajor 101
#define CblasColMajor 102
#define CblasNoTrans 111
#define CblasTrans 112

// Используем int для всех типов (как в OpenBLAS)
void cblas_dgemm(const int Layout,
                 const int transa,
                 const int transb,
                 const int m,
                 const int n,
                 const int k,
                 const double alpha,
                 const double *a,
                 const int lda,
                 const double *b,
                 const int ldb,
                 const double beta,
                 double *c,
                 const int ldc) {
    
    int i, j, p;
    
    // Проверяем, что всё в нужном формате
    if (Layout != CblasRowMajor) return;
    if (transa != CblasNoTrans || transb != CblasNoTrans) return;
    
    // Умножаем C = alpha * A * B + beta * C
    
    // Сначала умножаем C на beta
    if (beta != 1.0) {
        for (i = 0; i < m; i++) {
            for (j = 0; j < n; j++) {
                c[i * ldc + j] *= beta;
            }
        }
    }
    
    // Вычисляем alpha * A * B
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            double sum = 0.0;
            for (p = 0; p < k; p++) {
                sum += a[i * lda + p] * b[p * ldb + j];
            }
            c[i * ldc + j] += alpha * sum;
        }
    }
}