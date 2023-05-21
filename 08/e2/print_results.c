#include <stdio.h>
#include <math.h>

#include "type.h"


void print_results(char class, int n1, int n2, int n3, int niter,
    double t, double mops, char *optype, logical verified, char *npbversion,
    char *compiletime, char *cs1, char *cs2, char *cs3, char *cs4, char *cs5,
    char *cs6, char *cs7)
{
  char size[16];
  int j;

  printf( "\n\n Benchmark Completed.\n");
  printf( " Class           =             %12c\n", class );

  // If this is not a grid-based problem (EP, FT, CG), then
  // we only print n1, which contains some measure of the
  // problem size. In that case, n2 and n3 are both zero.
  // Otherwise, we print the grid size n1xn2xn3

  if ( ( n2 == 0 ) && ( n3 == 0 ) ) {
    printf( " Size            =             %12d\n", n1 );
  } else {
    printf( " Size            =           %4dx%4dx%4d\n", n1, n2, n3 );
  }

  printf( " Iterations      =             %12d\n", niter );
 // printf( " Time in seconds =             %12.2lf\n", t );

  //printf( " Mop/s total     =          %15.2lf\n", mops );
  //printf( " Mop/s/thread    =          %15.2lf\n", mops/(double)num_threads );

  printf( " Operation type  = %24s\n", optype );
  if ( verified )
    printf( " Verification    =             %12s\n", "SUCCESSFUL" );
  else
    printf( " Verification    =             %12s\n", "UNSUCCESSFUL" );
  printf( " Version         =             %12s\n", npbversion );
}

