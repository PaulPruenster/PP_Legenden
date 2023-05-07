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

// -- adapted from:
// "https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/"
bool safe_board(int **board, const long n, int column, int row) {
  {
    int i, j;

    /* Check this row on left side */
    for (i = 0; i < column; i++) {
      if (board[row][i])
        return false;
    }

    /* Check upper diagonal on left side */
    for (i = row, j = column; i >= 0 && j >= 0; i--, j--) {
      if (board[i][j])
        return false;
    }

    /* Check lower diagonal on left side */
    for (i = row, j = column; j >= 0 && i < n; i++, j--) {
      if (board[i][j])
        return false;
    }

    return true;
  }
}

void print_board(int **board, const long n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("%d", board[i][j]);
    }
    printf("\n");
  }
}

void clear_board(int **board, const long n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
    }
  }
}

/*
  A recursive utility function to solve N
  Queen problem

  -- adapted from:
"https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/"
*/
bool solveNQUtil(int **board, int col, const long n, int starting_row_i) {
  /* base case: If all queens are placed then return true */
  if (col >= n)
    return true;
  else if (col == 0) { // for starting a new solution
    for (int i = starting_row_i; i < n; i++) {
      if (safe_board(board, n, col, i)) {
        board[i][col] = 1;

        if (solveNQUtil(board, col + 1, n, 0))
          return true;
        board[i][col] = 0; // BACKTRACK
      }
    }
  } else { // just for column 1 and above
    /* Consider this column and try placing this queen in all rows one by one */
    for (int i = 0; i < n; i++) {
      /* Check if the queen can be placed on
      board[i][col] */
      if (safe_board(board, n, col, i)) {
        /* Place this queen in board[i][col] */
        board[i][col] = 1;

        /* recur to place rest of the queens */
        if (solveNQUtil(board, col + 1, n, 0))
          return true;

        /* If placing queen in board[i][col]
        doesn't lead to a solution, then
        remove queen from board[i][col] */
        board[i][col] = 0; // BACKTRACK
      }
    }
  }

  /* If the queen cannot be placed in any row in
         this column col  then return false */
  return false;
}

int n_queens_solutions(const long n) {
  int **board = init_board(n);
  int solutions = 0;

  // idea is now to compute a solution .. 
  // add it to solutions and give it a new starting point
  // for example first startpoint i=0 j=0 -- solution
  // next start is i=1 and j=0

  for (int starting_row_i = 0; starting_row_i<n; starting_row_i++) {
    if (solveNQUtil(board, 0, n, starting_row_i)) {
      //printf("following is a solution\n");
      //print_board(board, n);
      solutions++;
    }

    //reset board
    clear_board(board, n);
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