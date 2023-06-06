#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include <math.h>



#define SIZE 100000000

void seriel(double* x, double* y, double factor, int n) { 
    for (int i=0; i < n; i++) {
        x[i] = factor * y[i];
        factor = factor / 2;
    }
}


void parallel(double* x, double* y, int n) { 
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        x[i] = y[i] / pow(2, i);
    }
}   

int main() {

    double start_time, end_time, elapsed_time;
    double factor = 1;
    double *x = (double *) malloc(SIZE * sizeof(double));
    double *y = (double *) malloc(SIZE * sizeof(double));

    start_time = omp_get_wtime();
    seriel(x, y, factor, SIZE);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("seriel: size = %d, time = %f\n", SIZE, elapsed_time);

    start_time = omp_get_wtime();
    parallel(x, y, SIZE);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("parallel: size = %d, time = %f\n", SIZE, elapsed_time);


}