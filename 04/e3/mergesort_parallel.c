#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// This merge-function is from the slides and it sorts two arrays of size na & nb to a new sorted array C of size na + nb
void Merge(int *C, int *A, int *B, int na, int nb) {
	while (na>0 && nb>0) {
		if (*A <= *B){
			*C++ = *A++; na--;} 
		else {
			*C++ = *B++; nb--;}
	}
	while (na>0) {
		*C++ = *A++; na--;
	}
	while (nb>0) {
		*C++ = *B++; nb--;
	}
}

// This mergeSort function is the recursive mergesort we all know. We get the return Array B, the Array with the values 
// which need to be sorted in A and the size of A which is n
void MergeSort(int *B, int *A, int n) {
	if (n==1) {
		B[0] = A[0];}
	else if (n > 1000000){
		// here we create a new array C which will then be our recursive return array B
		int * C = malloc(sizeof(int) * n);

		// here we start the recursion: with the first half of the solution and data array we start the first mergesort and with the 
		// second  half of the solution and data arrays we start the other mergesort. The recursion starts as a task so that multiple threads can go to work right here
		#pragma omp task
        MergeSort(C, A, n/2);
        #pragma omp task
		MergeSort(C+n/2, A+n/2, n-n/2);
		
		// our two halfs of C get merged into the recursive return array B as soon as the two tasks are finished
        #pragma omp taskwait
		Merge(B, C, C+n/2, n/2, n-n/2);

		//now we can free the temporal solution array C again
		free(C);
	}
	else {
		// here we create a new array C which will then be our recursive return array B
		int * C = malloc(sizeof(int) * n);
		// here we start the recursion: with the first half of the solution and data array we start the first mergesort and with the 
		// second  half of the solution and data arrays we start the other mergesort. The recursion starts as a task so that multiple threads can go to work right here
        MergeSort(C, A, n/2);
		MergeSort(C+n/2, A+n/2, n-n/2);
		// our two halfs of C get merged into the recursive return array B as soon as the two tasks are finished
		Merge(B, C, C+n/2, n/2, n-n/2);

		//now we can free the temporal solution array C again
		free(C);
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


	// allocate memory
	int * A = malloc(sizeof(int) * n);
    int * B = calloc(n, sizeof(int));
	// fill matrix
	unsigned int seed = time(NULL);
	for (long i = 0; i < n; ++i) {
		A[i] = rand_r(&seed);
	}

	// Real program starts right here
	double start_time = omp_get_wtime();

	//start MergeSort with the two arrays and the size
	//start MergeSort with the two arrays and the size
	#pragma omp parallel
	{
		#pragma omp single
		MergeSort(B, A, n);
	}


	double end_time = omp_get_wtime();
	printf("time: %2.6f seconds\n", end_time - start_time);

	// cleanup
	free(A);
	free(B);
}