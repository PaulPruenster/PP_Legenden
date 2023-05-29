#include <stdio.h>
#include <stdlib.h>


void printArray(int* arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


int main() {
    int array_size = 100;
    int N = array_size / 2;

    // Normal Loop

    int* A = (int*)malloc((array_size) * sizeof(int));

    for (int i = 0; i < array_size; i++) {
        A[i] = 1;
    }

    for (int i = 4; i <= N; i += 9) {
        for (int j = 0; j <= N; j += 5) {
            A[i] = 0;
        }
    }



    // Normalized Loop

    int* normalizedA = (int*)malloc((array_size) * sizeof(int));

    for (int i = 0; i < array_size; i++) {
        normalizedA[i] = 1;
    }

    for (int i = 0; i <= (N - 4) / 9; i++) {
        for (int j = 0; j <= N / 5; j++) {
            normalizedA[4 + 9 * i] = 0;
        }
    }

    int sameResult = 1;

    for (int i = 0; i < array_size; i++) {
        if (A[i] != normalizedA[i]) {
            sameResult = 0;
            break;
        }
    }

    if (sameResult) {
        printf("The results of the normal loop and the normalized loop are the same.\n");
    } else {
        printf("The results of the normal loop and the normalized loop are different.\n");
        printf("Array A:\n");
        printArray(A, N + 1);
        printf("Normalized Array A:\n");
        printArray(normalizedA, N + 1);
    }

    // Free memory for arrays
    free(A);
    free(normalizedA);

    return 0;
}
