#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define SIZE 1024 * 1024

void seriel(double* a[], double b) { 
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            a[i + 2][j - 1] = b * a[i][j] + 4;
        }
    }
}


void parallel(double* a[], double b) { 
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < 4; ++i) {
        for (int j = 1; j < 4; ++j) {
            a[i + 2][j - 1] = b * a[i][j] + 4;
        }
    }
}

int main() {
    double factor = 1;
    double *x = (double **)malloc(SIZE * sizeof(double*));

    double start_time = omp_get_wtime();
    seriel(x, factor);
    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;
    printf("size = %d, time = %f\n", SIZE, elapsed_time);

    start_time = omp_get_wtime();
    parallel(x, factor);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("size = %d, time = %f\n", SIZE, elapsed_time);


}