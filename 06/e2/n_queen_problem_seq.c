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
bool solveNQUtil(int **board, int col, const long n) {
  /* base case: If all queens are placed then return true */
  if (col >= n)
    return true;

  /* Consider this column and try placing this queen in all rows one by one */
  for (int i = 0; i < n; i++) {
    /* Check if the queen can be placed on
    board[i][col] */
    if (safe_board(board, n, col, i)) {
      /* Place this queen in board[i][col] */
      board[i][col] = 1;

      /* recur to place rest of the queens */
      if (solveNQUtil(board, col + 1, n))
        return true;

      /* If placing queen in board[i][col]
      doesn't lead to a solution, then
      remove queen from board[i][col] */
      board[i][col] = 0; // BACKTRACK
    }
  }
  /* If the queen cannot be placed in any row in
         this column col  then return false */
  return false;
}

int n_queens_solutions(const long n) {
  int **board = init_board(n);
  // int solutions = 0;
  // int set_queens_counter = 0;
  // int i_queens[n]; // coordinates in i
  // int j_queens[n]; // coordinates in j
  // bool finished = false;

  // print_board(board, n);

  if (solveNQUtil(board, 0, n)) {
    printf("following is a solution\n");
    print_board(board, n);
  }

  // iterate over searching current solution
  /*while (!finished) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        board[i][j] = 1;
        i_queens[set_queens_counter] = i;
        j_queens[set_queens_counter] = j;
        set_queens_counter++;

        if (currently_possible(board, n)) {
          if (set_queens_counter >= 8)
            solutions++;
          // reset last queen
          // and set i and j to the values of the queen
        }
        board[i][j] = 0;
      }
    }
  }*/
  // iterate over each field and set queen if possible

  free_board(board, n);
  return 0;
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