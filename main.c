#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main()
{
  matrix *mtr = read_matrix("big_matrix.dat");

  tridiagonalmatrix_parallel_solve(mtr);

  return 0;
}