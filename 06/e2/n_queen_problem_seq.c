#include <errno.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

bool** init_board(long n){
    bool **board = (bool**) malloc(n * sizeof(bool));
    
    for(u_int i = 0; i<n; i++){
        board[i] = (bool*) malloc(n * sizeof(bool));
        for (u_int j = 0; j<n; j++) {
          board[i][j] = false;
        }
    }

    return board;
}

void free_board(bool ** board, long n){
    for (u_int i = 0; i<n; i++) {
        free(board[i]);
    }

    free(board);
}

int n_queens_solutions(long n){
  bool ** board = init_board(n);
  int solutions = 0;

  for (u_int i = 0; i<n; i++) {
    for (u_int j = 0; j<n; j++) {
      printf("%d\n", board[i][j]);
    }
  }


  //free_board(board, n);
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