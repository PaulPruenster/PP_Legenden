#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define CACHE_SIZE 5


int cache[CACHE_SIZE];

// Declare a global array to keep track of the age of each element in the cache
int age[CACHE_SIZE];

// Declare a global variable to keep track of the current age
int64_t current_age = 0;

int find_lru_index() {
    int lru_index = 0;
    int lru_age = age[0];

    for (int i = 1; i < CACHE_SIZE; i++) {
        if (age[i] < lru_age) {
            lru_age = age[i];
            lru_index = i;
        }
    }

    return lru_index;
}

// Function to check if an element is present in the cache
bool is_present(int element) {
    for (int i = 0; i < CACHE_SIZE; i++) {
        if (cache[i] == element) {
            age[i] = current_age++;
            return true;
        }
    }

    return false;
}

// Function to insert an element into the cache
bool insert(int element) {
    // Check if the element is already present in the cache
    if (is_present(element)) {
        return true;
    }

    // Find the index of the element with the least recently used age
    int lru_index = find_lru_index();

    // Replace the element with the least recently used age
    cache[lru_index] = element;
    age[lru_index] = current_age++;
    return false;
}

int64_t firstVariant(int32_t **a, int32_t **b, int32_t **c, size_t n, size_t s) {
int64_t misses = 0;
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            c[i][j] = a[i][j] * b[i][j];
            size_t block_index = (i * n + j) / s;   // gives us the block index which shows us where we can find the data
            if (!insert(block_index)){
                ++misses;
            }
        }
        
    }
    return misses;
}

int64_t secondVariant(int32_t **a, int32_t **b, int32_t **c, size_t n, size_t s) {
    int64_t misses = 0;
    for (size_t j = 0; j < n; ++j) {
        for (size_t i = 0; i < n; ++i) {
            c[i][j] = a[i][j] * b[i][j];
            size_t block_index = (i * n + j) / s;   // gives us the block index which shows us where we can find the data
            if (!insert(block_index)){
                ++misses;
            }
        }
    }
    return misses;
}

int main(){
    /*cache is divided into sets, and each memory address maps to a specific set. 
    The "4-way" part of the name means that there are four cache lines (or blocks) in each set.
    For the sake of simplicity we use multiples of 4 for s, so that the 4 byte integer can be stored.
    Now when using s = 4 we get 4 ints per set (we have 4 cache lines à 4 bytes)*/
    
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