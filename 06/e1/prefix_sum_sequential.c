#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exclusivePrefixSum(int * a, int * b, int n) {


    b[0] = 0;
    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i - 1];
    }
    return b[n-1];

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

    int * A = malloc(sizeof(A) * n);

    for(long i = 0; i < n; ++i) {
		A[i] = 1;
	}

    int * B = malloc(sizeof(B) * n);

	double start_time = omp_get_wtime();

    int res = exclusivePrefixSum(A, B, n);

	double end_time = omp_get_wtime();
	printf("res: %d, time: %2.2f seconds\n", res, end_time - start_time);

	// cleanup
	free(A);
	free(B);
    
    return EXIT_SUCCESS;
}