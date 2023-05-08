#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>



void exclusivePrefixSum(int32_t *A, int32_t *B, int n) {
	// round up chunk size (then the last section is a bit smaller)
	int thread_nums = omp_get_num_threads();
    int chunksize = (n + thread_nums - 1) / thread_nums; 
    int32_t *partial_sums= malloc(sizeof(int32_t) * thread_nums);

    //Each thread calculates the prefix sum of its assigned chunk
    #pragma omp parallel
    {
		// right here we set the start and endpoint for each chunk
        int threadNumber = omp_get_thread_num();
		int start = chunksize * threadNumber;
        int end = chunksize * (threadNumber + 1) < n ? chunksize * (threadNumber + 1) : n;
        int sum = 0;

		//start prefix sum calculation for each thread
        for (int i = start ; i < end; i++) {
            sum += A[i];
            B[i+1] = sum;
        }
        partial_sums[threadNumber] = sum;

		//it is important to wait here, because we need the partial sums of each of the chunks
		#pragma omp barrier

        int offset = 0;

		//getting the offset for each chunk and then adding it to B
        for (int i = 0; i < threadNumber; i++) {
            offset += partial_sums[i];
        }
        for (int i = start; i < end; i++) {
            B[i] += offset;
        }
    }
    free(partial_sums);
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
	
	exclusivePrefixSum(A, B, n);


	double end_time = omp_get_wtime();
	printf("res: %d, time: %2.2f seconds\n", B[n-1], end_time - start_time);

	// cleanup
	free(A);
	free(B);
    return EXIT_SUCCESS;
}