#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000000

void seriel(int *x, int *y, int n, int twice) {
  x[0] = x[0] + 5 * y[0];
  for (int i = 1; i < n; i++) {
    x[i] = x[i] + 5 * y[i];
    if (twice) {
      x[i - 1] = 2 * x[i - 1];
    }
  }
}

void parallel(int *x, int *y, int n, int twice) {
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

int main() {

  double start_time, end_time, elapsed_time;
  int *x = (int *)malloc(SIZE * sizeof(int));
  int *y = (int *)malloc(SIZE * sizeof(int));

  start_time = omp_get_wtime();
  seriel(x, y, SIZE, 1);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
  start_time = omp_get_wtime();
  seriel(x, y, SIZE, 0);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);

  start_time = omp_get_wtime();
  parallel(x, y, SIZE, 1);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
  start_time = omp_get_wtime();
  parallel(x, y, SIZE, 0);
  end_time = omp_get_wtime();
  elapsed_time = end_time - start_time;
  printf("size = %d, time = %f\n", SIZE, elapsed_time);
}