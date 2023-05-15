#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>


#define REPETITIONS 1000000

void multiply_add(float *a, float *b, float *c, int size) {
  #pragma omp simd //simdlen(2048)
    for (int i = 0; i < size; ++i) {
        a[i] += b[i] * c[i];
    }
}

int main(int argc, char *argv[]) {

    int n = 5;
    if (argc > 1) {
        sscanf(argv[1], "%d", &n);
    }

    int size_array[5] = {2048, 5000, 10000, 50000, 100000};


    for (int i = 0; i < n; ++i) {
        int size = size_array[i];
        float *a = (float *) malloc(size * sizeof(float));
        float *b = (float *) malloc(size * sizeof(float));
        float *c = (float *) malloc(size * sizeof(float));

        for (int i = 0; i < size; ++i) {
            a[i] = 0.0f;
            b[i] = 2;
            c[i] = 3;
        }

	    double start_time = omp_get_wtime();
        
        for (int run = 0; run < REPETITIONS; ++run) {
            multiply_add(a, b, c, size);
        }
	    double end_time = omp_get_wtime();

        
        /*if (size == 2048){
            for (int j = 0; i < 2048; ++i){
                printf("%f ", a[j]);
            }
        }*/
        
        
        double elapsed_time = end_time - start_time;

        printf("size = %d, time = %f\n", size, elapsed_time);

        free(a);
        free(b);
        free(c);
    }

    return 0;
}
