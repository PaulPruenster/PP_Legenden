#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1024 * 1024

void seriel(int *x, int *y, double factor, int n, int twice) {
  x[0] = x[0] + 5 * y[0];
  for (int i = 1; i < n; i++) {
    x[i] = x[i] + 5 * y[i];
    if (twice) {
      x[i - 1] = 2 * x[i - 1];
    }
  }
}

void parallel(int *x, int *y, double factor, int n, int twice) {
  x[0] = x[0] + 5 * y[0];
  if (twice) {
    for (int i = 1; i < n; i++) {
      x[i] = x[i] + 5 * y[i];
      x[i - 1] = 2 * x[i - 1];
    }
  } else {
    for (int i = 1; i < n; i++) {
      x[i] = x[i] + 5 * y[i];
    }
  }
}

int main(int argc, char **argv) {

  double start_time, end_time, elapsed_time;
  double factor = 1;
  float *x = (int *)malloc(SIZE * sizeof(int));
  float *y = (int *)malloc(SIZE * sizeof(int));

  start_time = omp_get_wtime();
  seriel(x, y, factor, SIZE, 1);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
  start_time = omp_get_wtime();
  seriel(x, y, factor, SIZE, 0);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);

  start_time = omp_get_wtime();
  parallel(x, y, factor, SIZE, 1);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
  start_time = omp_get_wtime();
  parallel(x, y, factor, SIZE, 0);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
}