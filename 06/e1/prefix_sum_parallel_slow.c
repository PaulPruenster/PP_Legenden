#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define OMP_NUM_THREADS 1

void addSum(int32_t *A, int32_t *B, int n) {
    while (n-- > 0){
        *(B + 1) = *B + *A;
        ++A;
        ++B;
    }

}


void exclusivePrefixSum(int32_t *a, int32_t *b, int n) {
    if (n <= 1) {
        return;
    }
    
    #pragma omp task
    exclusivePrefixSum(a, b, n/2);
    #pragma omp task
    exclusivePrefixSum(a + n/2, b + n/2, n-n/2);
    
    #pragma omp taskwait
    addSum(a, b, n);
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
    

	double end_time = omp_get_wtime();
	printf("res: %d, time: %2.2f seconds\n", B[n-1], end_time - start_time);

	// cleanup
    return EXIT_SUCCESS;
}