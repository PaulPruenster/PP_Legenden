#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main() {
    double startTime = omp_get_wtime();

    long n = 700000000;
    long i, count = 0;
    double x, y, pi;

    srand((unsigned) time(NULL));
    for (i = 0; i < n; i++) {
        x = (double) rand() / RAND_MAX;
        y = (double) rand() / RAND_MAX;

        if (x * x + y * y <= 1) count++;
    }

    pi = 4.0 * count / n;

    printf("Approximate value of pi: %f\n", pi);

    double endTime = omp_get_wtime();
	printf("time: %2.4f seconds\n", endTime-startTime);
    return 0;
}
