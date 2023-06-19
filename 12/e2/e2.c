#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h> 
#include <math.h>

#define N 100000001

// Example 1: Loop Unrolling
void old1() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N - 1; ++i) {
        a[i] = b[i] + b[i + 1];
    }

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
}

void new1() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N - 1; i += 2) {
        a[i] = b[i] + b[i + 1];
        a[i + 1] = b[i + 1] + b[i + 2];
    }

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
}

// Example 2: Loop-Invariant Code Motion
void old2() {
    double *a = (double *) malloc(N * sizeof(double));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        a[i] *= hypot(0.3, 0.4);
    }

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
}

void new2() {
    double *a = (double *) malloc(N * sizeof(double));
    double factor = hypot(0.3, 0.4);
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        a[i] *= factor;
    }

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
}

// Example 3: Loop Unswitching
void old3() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        if (N % 2) {
            a[i] = b[i] + 5;
        } else {
            a[i] = c[i] + 5;
        }
    }

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

void new3() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    if (N % 2) {
        for (int i = 0; i < N; ++i) {
            a[i] = b[i] + 5;
        }
    } else {
        for (int i = 0; i < N; ++i) {
            a[i] = c[i] + 5;
        }
    }

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

// Example 4: Loop Fission/Distribution
void old4() {
    int sum_a = 0, sum_b = 0, sum_c = 0;
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
        sum_b += b[i];
        sum_c += c[i];
    }

    printf("%d %d %d\n", sum_a, sum_b, sum_c);

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

void new4() {
    int sum_a = 0, sum_b = 0, sum_c = 0;
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_b += b[i];
    }
    for (int i = 0; i < N; ++i) {
        sum_c += c[i];
    }

    printf("%d %d %d\n", sum_a, sum_b, sum_c);

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

// Example 5: Loop Peeling and Loop Fusion/Combination
void old5() {
    int *a = (int *) malloc(N * sizeof(int));
    int min = a[0];
    int sum = 0;
    double start_time = omp_get_wtime();

    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
    }
    for (int i = 0; i < N; ++i) {
        sum += a[i];
    }

    printf("%d %d\n", min, sum);

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
}

void new5() {
    int *a = (int *) malloc(N * sizeof(int));
    int min = a[0];
    int sum = a[0];
    double start_time = omp_get_wtime();

    for (int i = 1; i < N; ++i) {
        min = (a[i] < min) ? a[i] : min;
        sum += a[i];
    }

    printf("%d %d\n", min, sum);

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
}

// Example 6: Loop Splitting
void old6() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; ++i) {
        if (i % 2) {
            a[i] = b[i] + 4;
        } else {
            a[i] = c[i] + 5;
        }
    }

    double end_time = omp_get_wtime();
    printf("old: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

void new6() {
    int *a = (int *) malloc(N * sizeof(int));
    int *b = (int *) malloc(N * sizeof(int));
    int *c = (int *) malloc(N * sizeof(int));
    double start_time = omp_get_wtime();

    for (int i = 0; i < N; i += 2) {
        a[i] = c[i] + 5;
        a[i + 1] = b[i + 1] + 4;
    }

    double end_time = omp_get_wtime();
    printf("new: N = %d, time = %f\n", N, end_time - start_time);
    free(a);
    free(b);
    free(c);
}

// Example 7: Loop Tiling TODO # DO NOT RUN ON LCC2 #
// void old7() {
//     double **a = (double **) malloc(N * sizeof(double *));
//     double **b = (double **) malloc(N * sizeof(double *));
//     double **c = (double **) malloc(N * sizeof(double *));
//     for (int i = 0; i < N; ++i) {
//         a[i] = (double *) malloc(N * sizeof(double));
//         b[i] = (double *) malloc(N * sizeof(double));
//         c[i] = (double *) malloc(N * sizeof(double));
//     }
//     double start_time = omp_get_wtime();

//     for (int i = 0; i < N; ++i) {
//         for (int j = 0; j < N; ++j) {
//             for (int k = 0; k < N; ++k) {
//                 c[i][j] = a[i][k] * b[k][j];
//             }
//         }
//     }

//     double end_time = omp_get_wtime();
//     printf("old: N = %d, time = %f\n", N, end_time - start_time);
//     for (int i = 0; i < N; ++i) {
//         free(a[i]);
//         free(b[i]);
//         free(c[i]);
//     }
//     free(a);
//     free(b);
//     free(c);
// }


int main() {
    // Example 1: Loop Unrolling
    old1();
    new1();

    // Example 2: Loop-Invariant Code Motion
    old2();
    new2();

    // Example 3: Loop Unswitching
    old3();
    new3();

    // Example 4: Loop Fission/Distribution
    old4();
    new4();

    // Example 5: Loop Peeling and Loop Fusion/Combination
    old5();
    new5();

    // Example 6: Loop Splitting
    old6();
    new6();

    // Example 7: Loop Tiling
    //old7();
}