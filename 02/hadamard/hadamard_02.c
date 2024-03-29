#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

void secondVariant(int32_t **a, int32_t **b, int32_t **c, size_t n) {
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
        }
    }
}

int main(){
    /*cache is divided into sets, and each memory address maps to a specific set. 
    The "4-way" part of the name means that there are four cache lines (or blocks) in each set.
    For the sake of simplicity we use multiples of 4 for s, so that the 4 byte integer can be stored.
    Now when using s = 4 we get 4 ints per set (we have 4 cache lines à 4 bytes)*/
    
    size_t n = 1000;

    int32_t **a = malloc(n * sizeof(int32_t*));
    int32_t **b = malloc(n * sizeof(int32_t*));
    int32_t **c = malloc(n * sizeof(int32_t*));

    for (size_t i = 0; i < n; ++i) {
        a[i] = malloc(n * sizeof(int32_t));
        b[i] = malloc(n * sizeof(int32_t));
        c[i] = malloc(n * sizeof(int32_t));
    }

    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            a[i][j] = rand();
            b[i][j] = rand();
        }
    }

    secondVariant(a ,b ,c, n);

    for (size_t i = 0; i < n; ++i) {
        free(a[i]);
        free(b[i]);
        free(c[i]);
    }
    free(a);
    free(b);
    free(c);
    return EXIT_SUCCESS;
}