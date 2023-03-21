#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    long n = 700000000;
    int num_threads = 1;
    double x, y, pi;
    long i, count = 0;
    double start_time, end_time;

    if (argc > 1) {
        num_threads = atoi(argv[1]);
        if (num_threads <= 0) {
            printf("Invalid number of threads: %d\n", num_threads);
            exit(1);
        }
    }

    srand((unsigned int)time(NULL));
    start_time = omp_get_wtime();
    #pragma omp parallel num_threads(num_threads) private(x, y, i) reduction(+:count)
    {
        #pragma omp for
        for (i = 0; i < n; i++) {
            x = (double)rand() / RAND_MAX;
            y = (double)rand() / RAND_MAX;
            if (x * x + y * y <= 1) {
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
