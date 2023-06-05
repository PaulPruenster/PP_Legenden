#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>



#define SIZE 1024 * 1024 *100


void seriel(double* x, double* y,double* z, int n) { 
    for (int i = 1; i<n; i++) {
        x[i] = (x[i] + y[i-1]) / 2;
        y[i] = y[i] + z[i] * 3;
    }
}


void parallel(double* x, double* y, double* z, int n) { 

    #pragma omp parallel for
    for (int i = 1; i<n; i++) {
        y[i] = y[i] + z[i] * 3;
    }

    #pragma omp parallel for
    for (int i = 1; i<n; i++) {
        x[i] = (x[i] + y[i-1]) / 2;
    }
}   

int main() {

    double start_time, end_time, elapsed_time;
    double *x = (double *) malloc(SIZE * sizeof(double));
    double *y = (double *) malloc(SIZE * sizeof(double));
    double *z = (double *) malloc(SIZE * sizeof(double));

    start_time = omp_get_wtime();
    seriel(x, y, z, SIZE);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("seriel: size = %d, time = %f\n", SIZE, elapsed_time);

    start_time = omp_get_wtime();
    parallel(x, y, z, SIZE);
    end_time = omp_get_wtime();
    elapsed_time = end_time - start_time;
    printf("parallel: size = %d, time = %f\n", SIZE, elapsed_time);


}