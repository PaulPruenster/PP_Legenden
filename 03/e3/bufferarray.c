#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main() {
        long n = 100000000;
        unsigned int num_threads = 8;
        double x, y, pi;
        long i, count = 0;

        // long is 32 byte -- padding is times long buffer
        unsigned int padding = 10; // 10 * 32 is 320 byte buffer -- 4 was still false sharing so the aligned bytes read is somewhere between 4 and 10
        long local_counts[num_threads*padding];
        double start_time, end_time;

        unsigned int seed = (unsigned int)time(NULL);
        start_time = omp_get_wtime();
        #pragma omp parallel num_threads(num_threads) private(x, y, i)
        {
                int own_thread_num = omp_get_thread_num();
                unsigned int local_seed = seed + own_thread_num;
                local_counts[own_thread_num*padding] = 0;

                #pragma omp for
                for (i = 0; i < n; i++) {
                        x = (double)rand_r(&local_seed) / RAND_MAX;
                        y = (double)rand_r(&local_seed) / RAND_MAX;

                        if (x * x + y * y <= 1) {
                                local_counts[own_thread_num*padding]++;
                        }
                }
                
                #pragma omp atomic
                count += local_counts[own_thread_num*padding];
        }
        end_time = omp_get_wtime();

        pi = 4.0 * count / n;
        printf("Approximate value of pi: %f\n", pi);
        printf("Time taken: %f seconds\n", end_time - start_time);

        return 0;
}
