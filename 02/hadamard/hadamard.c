#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int64_t firstVariant(int32_t **a, int32_t **b, int32_t **c, size_t n, size_t s) {
    size_t block_size = s * 4;                                  //block size is the size of the cache block -> cache line size times the size of an int (4 bytes)
    size_t block_count = n / s;                                 //block count is the amount of cache blocks we have -> matrix length / cache line size
    int64_t misses = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
            size_t block_index = (i * n + j) / block_size % block_count;   // gives us the block index which shows us where we can find the data
            misses += (block_index * 3) + 1;
        }
        
    }
    return misses;
}

int64_t secondVariant(int32_t **a, int32_t **b, int32_t **c, size_t n, size_t s) {
    size_t block_size = s * 4;                                  //block size is the size of the cache block -> cache line size times the size of an int (4 bytes)
    size_t block_count = n / s;                                 //block count is the amount of cache blocks we have -> matrix length / cache line size
    int64_t misses = 0;
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
            size_t block_index = (i * n + j) / block_size % block_count;   // gives us the block index which shows us where we can find the data
            misses += (block_index * 3) + 1;
        }
    }
    return misses;
}

int main(){
    /*cache is divided into sets, and each memory address maps to a specific set. 
    The "4-way" part of the name means that there are four cache lines (or blocks) in each set.
    For the sake of simplicity we use multiples of 4 for s, so that the 4 byte integer can be stored.
    Now when using s = 4 we get 4 ints per set (we have 4 cache lines à 4 bytes)*/

    //TODO: find out cache size and simulate a LRU algorithm to find out the cache misses
    
    size_t n = 100;
    size_t s = 4;

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

    printf("cache read misses first variant:%ld\n", firstVariant(a ,b ,c, n, s));
    printf("cache read misses second variant:%ld\n", secondVariant(a ,b ,c, n, s));

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