#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
    long n = 700000000;
    int num_threads = 8;
    double x, y, pi;
    long i, count = 0;
    double start_time, end_time;

     unsigned int seed = (unsigned int)time(NULL);
    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(num_threads) private(x, y, i)
    {
        unsigned int local_seed = seed + omp_get_thread_num();
        long local_count = 0;
        #pragma omp for
        for (i = 0; i < n; i++) {
            x = (double)rand_r(&local_seed) / RAND_MAX;
            y = (double)rand_r(&local_seed) / RAND_MAX;
            if (x * x + y * y <= 1) {
                local_count++;
            }
        }
        #pragma omp atomic
        count += local_count;
    }
    end_time = omp_get_wtime();

    pi = 4.0 * count / n;
    printf("Approximate value of pi: %f\n", pi);
    printf("Time taken: %f seconds\n", end_time - start_time);

    return 0;
}
