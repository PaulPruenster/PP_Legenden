#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef OMP_NUM_THREADS
    #define OMP_NUM_THREADS 8
#endif

int dellanoy(int i, int j, int n) {

    if (i == n || j == n ) {
        return 1;
    }

    int b1, b2, b3;
    #pragma omp task shared(b1)
    b1 = dellanoy(i + 1, j + 1, n);

    #pragma omp task shared(b2)
    b2 = dellanoy(i + 1, j, n);
    
    #pragma omp task shared(b3)
    b3 = dellanoy(i, j + 1, n);

    #pragma omp taskwait
    return b1 + b2 + b3;
}

int main(int argc, char **argv) {
	// handle input
	if (argc != 2) {
		fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
		return EXIT_FAILURE;
	}
	errno = 0;
	char *str = argv[1];
	char *endptr;
	long n = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (n < 0) {
		fprintf(stderr, "Error: matrix size must not be negative!\n");
		return EXIT_FAILURE;
	}

	double start_time = omp_get_wtime();

    int res = 0;
    #pragma omp parallel
	{
		#pragma omp single
		res = dellanoy(0, 0, n);
	}

	double end_time = omp_get_wtime();
	printf("res: %d, time: %2.2f seconds\n", res, end_time - start_time);

	// cleanup
    return EXIT_SUCCESS;
}