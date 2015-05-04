#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "matrix.h"

int main()
{
  matrix *mtr = read_matrix("matrix2.dat");
  
  tridiagonalmatrix_left_solve(mtr);

  return 0;
}