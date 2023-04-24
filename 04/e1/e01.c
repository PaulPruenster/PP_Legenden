#include <stdio.h>
#include <omp.h>
#include <time.h>

int main() {
  const int N = 100000000;
  int x = 0;

  double start_time = omp_get_wtime();

  #pragma omp parallel for num_threads(4) shared(x) 
  for (int i = 0; i < N; i++) {
  #pragma omp atomic
    x++;
  }

  double end_time = omp_get_wtime();
  printf("x = %d\n", x);
  printf("Time taken  = %f seconds\n", end_time - start_time);

  return 0;
}
