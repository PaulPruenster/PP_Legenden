#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 

#define N 100000001

int main() {
    double start_time, end_time, elapsed_time;
    double *a = (double *) malloc(N * sizeof(double));
    double *b = (double *) malloc(N * sizeof(double));


    start_time = omp_get_wtime();
    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("old: N = %d, time = %f\n", N, elapsed_time);

    start_time = omp_get_wtime();
    for (int i = 0; i < N - 1; i += 2) {
        a[i] = b[i] + b[i + 1];
        a[i + 1] = b[i + 1] + b[i + 2];
    }
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("new: N = %d, time = %f\n", N, elapsed_time);
}