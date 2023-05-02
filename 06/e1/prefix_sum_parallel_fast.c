#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OMP_NUM_THREADS 8


void exclusivePrefixSum(int *A, int *B, int n) {
    int sum = 0;

	// each thread now calculates the prefix sum of a contiguous subarray of the input array
	// later the prefix sums of each thread are summed up using the reduction, so that we have our end-array b
    #pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++) {
        sum += A[i-1];
        B[i] = sum;
    }
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

    int32_t * A = malloc(sizeof(A) * n);
    int32_t * B = malloc(sizeof(B) * n);


    for(long i = 0; i < n; ++i) {
		A[i] = 1;
        B[i] = 0;
	}

	double start_time = omp_get_wtime();
    #pragma omp parallel
	{
		#pragma omp single
		exclusivePrefixSum(A, B, n);
	}    

	for (int i = 0; i < n; i++)
	{
		printf("%d\n", B[i]);
	}
	

	double end_time = omp_get_wtime();
	printf("res: %d, time: %2.2f seconds\n", B[n-1], end_time - start_time);

	// cleanup
	free(A);
	free(B);
    return EXIT_SUCCESS;
}