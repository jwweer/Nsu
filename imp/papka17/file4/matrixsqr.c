#include <stdio.h>
void cblas_dgemm(const int Layout, const int transa, const int transb,
                 const int m, const int n, const int k,
                 const double alpha,
                 const double *a, const int lda,
                 const double *b, const int ldb,
                 const double beta,
                 double *c, const int ldc);

void MatrixSqr(int n, const double *A, double *R) {
    // Константы из cblas.h
    const int CblasRowMajor = 101;
    const int CblasNoTrans = 111;
    
    // R = A * A
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
                n, n, n, 1.0, A, n, A, n, 0.0, R, n);
}