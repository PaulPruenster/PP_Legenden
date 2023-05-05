#include <errno.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int **init_board(const long n) {
  int **board = (int **)malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++) {
    board[i] = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
      // printf("inside init: %d\n", board[i][j]);
    }
  }

  return board;
}

void free_board(int **board, const long n) {
  for (int i = 0; i < n; i++) {
    free(board[i]);
  }

  free(board);
}

bool currently_possible(int **board, const long n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j]) {
        // go straight row (j is fix)
        for (int k = 0; k < n; k++) {
          if (i == k)
            continue;
          if (board[k][j])
            return false;
        }

        // go straight column (i is fix)
        for (int k = 0; k < n; k++) {
          if (j == k)
            continue;
          if (board[i][k])
            return false;
        }

        // go left top to right bottom diagonal
        // find diagonal start
        int di = (i >= j) ? (i - j) : 0;
        int dj = (j >= i) ? (j - i) : 0;

        while (di < n && dj < n) {
          if (di == i && dj == j) {
          } else if (board[di][dj]) {
            return false;
          }
          dj++;
          di++;
        }

        // go right top to left bottom diagonal
        // find diagonal start
        dj = ((i + j) > n) ? n : (i + j);
        di = ((i + j) <= n) ? 0 : ((i + j) - n);

        while (di < n && dj >= 0) {
          if (di == i && dj == j) {
          } else if (board[di][dj]) {
            return false;
          }
          di++;
          dj--;
        }
      }
    }
  }
  return true;
}

void clear_board(int** board, const long n){
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }
}

int n_queens_solutions(const long n) {
  int **board = init_board(n);
  int solutions = 0;
  int queens = 0;

  // iterate over searching current solution
      // iterate over each field and set queen if possible
  
  
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 1;
      if (currently_possible(board, n)) {
        queens++;
        if (queens >= 8)
          solutions++;
        break;
      }
      board[i][j] = 0;
    }
  }

  free_board(board, n);
  return solutions;
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

  double start_time = omp_get_wtime();

  // func

  int result = n_queens_solutions(n);

  double end_time = omp_get_wtime();

  printf("res: %d, time: %2.2f seconds\n", result, end_time - start_time);

  // cleanup
  return EXIT_SUCCESS;
}