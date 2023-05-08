#include <errno.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

int solutions;

int **init_board(const long n) {
  int **board = (int **)malloc(n * sizeof(int *));

  for (int i = 0; i < n; i++) {
    board[i] = (int *)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
      board[i][j] = 0;
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

/*
  A recursive utility function to solve N
  Queen problem

  -- adapted from:
"https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/"
*/
void solveNQUtil(int **board, int col, const long n) {
  /* base case: If all queens are placed then return true */
  if (col >= n){
    solutions++;
  } else {
    /* Consider this column and try placing this queen in all rows one by one */
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
      /* Check if the queen can be placed on
      board[i][col] */
      if (safe_board(board, n, col, i)) {
        /* Place this queen in board[i][col] */
        board[i][col] = 1;

        /* recur to place rest of the queens */
        solveNQUtil(board, col + 1, n);

        /* If placing queen in board[i][col]
        doesn't lead to a solution, then
        remove queen from board[i][col] */
        board[i][col] = 0; // BACKTRACK
      }
    }
  }

  /* If the queen cannot be placed in any row in
         this column col  then return */
}

void n_queens_solutions(const long n) {
  int **board = init_board(n);

  // idea is now to compute a solution .. 
  // add it to solutions and give it a new starting point
  // for example first startpoint i=0 j=0 -- solution
  // next start is i=1 and j=0

  solveNQUtil(board, 0, n);

  free_board(board, n);
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
  #pragma omp parallel 
	{
		#pragma omp single
		n_queens_solutions(n);
	}
  

  double end_time = omp_get_wtime();

  printf("res: %d, time: %2.2f seconds\n", solutions, end_time - start_time);

  return EXIT_SUCCESS;
}