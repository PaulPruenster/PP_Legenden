#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <xmmintrin.h>

void compiler_specific_function(float * A, float * B, float * C, int  size){
    int repetitions = 1000000;
    for(int run = 0; run < repetitions; ++run) {
        for(int i = 0; i < size; i+=4) {
            __m128 a = _mm_loadu_ps(&A[i]);
            __m128 b = _mm_loadu_ps(&B[i]);
            __m128 c = _mm_loadu_ps(&C[i]);

            __m128 bc = _mm_mul_ps(b, c);
            __m128 result = _mm_add_ps(a, bc);

            _mm_storeu_ps(&A[i], result);
        }
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
	long size = strtol(str, &endptr, 0);
	if (errno != 0) {
		perror("strtol");
		return EXIT_FAILURE;
	}
	if (endptr == str) {
		fprintf(stderr, "Error: no digits were found!\n");
		return EXIT_FAILURE;
	}
	if (size < 0) {
		fprintf(stderr, "Error: array size must not be negative!\n");
		return EXIT_FAILURE;
	}

    float * A = malloc(sizeof(A) * size);
    float * B = malloc(sizeof(B) * size);
    float * C = malloc(sizeof(C) * size);


    for(long i = 0; i < size; ++i) {
		A[i] = 0;
        B[i] = 2;
        C[i] = 3;
	}

	double start_time = omp_get_wtime();

    compiler_specific_function(A, B, C, size);

	double end_time = omp_get_wtime();

    for(long i = 0; i < size; ++i) {
		float realValue = A[i];
        float expectedValue = 6.0 * 1000000;
        assert(realValue == expectedValue);
	}

	printf("time: %2.2f seconds\n", end_time - start_time);

	// cleanup
    return EXIT_SUCCESS;
}