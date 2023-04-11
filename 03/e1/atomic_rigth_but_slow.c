#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#ifndef OMP_NUM_THREADS
#define OMP_NUM_THREADS 8
#endif

int main() {
    long n = 500000000;
    long count = 0;
    double x, y, pi;
    long i;
    double start_time, end_time;

    unsigned int seed = (unsigned int)time(NULL);
    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(OMP_NUM_THREADS) private(x, y, i)
    {
        unsigned int local_seed = seed + omp_get_thread_num();
        #pragma omp for
        for (i = 0; i < n; i++) {
            x = (double)rand_r(&local_seed) / RAND_MAX;
            y = (double)rand_r(&local_seed) / RAND_MAX;
            if (x * x + y * y <= 1) {
                #pragma omp atomic
                count++;
            }
        }
    }
    end_time = omp_get_wtime();

    pi = 4.0 * count / n;
    printf("Approximate value of pi: %f\n", pi);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
