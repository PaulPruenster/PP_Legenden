#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

// https://www.thecrazyprogrammer.com/2015/03/c-program-for-n-queens-problem-using-backtracking.html

int board[20],count;

void queen(int row,int n);

int main(int argc, char**argv)
{
    if (argc != 2) {
        fprintf(stderr, "Error: usage: %s <n>\n", argv[0]);
        return EXIT_FAILURE;
    }
    int errno = 0;
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
        fprintf(stderr, "Error: n size must not be negative!\n");
        return EXIT_FAILURE;
    }

    double start_time = omp_get_wtime();
    queen(1,n);
    double end_time = omp_get_wtime();

    printf("Solution: %d, time: %2.2f seconds\n", count, end_time - start_time);
    return 0;
}

/*funtion to check conflicts
If no conflict for desired postion returns 1 otherwise returns 0*/
int place(int row,int column)
{
    for(int i=1;i<=row-1;++i)
    {
        //checking column and digonal conflicts
        if(board[i]==column)
            return 0;
        else if(abs(board[i]-column)==abs(i-row))
            return 0;
    }

    return 1; //no conflicts
}

//function to check for proper positioning of queen
void queen(int row,int n)
{
    for(int column=1;column<=n;++column)
    {
        if(place(row,column))
        {
        board[row]=column; //no conflicts so place queen
        if(row==n) //dead end
            count++; //printing the board configuration
        else //try queen with next position
            queen(row+1,n);
        }
    }
}