#include <stdio.h>
#include <stdlib.h>
#include "./lib/matrix.h"

int main()
{
  matrix *mtr = read_matrix("./data/big_matrix.dat");

  printf("result\n");
  print_vector(tridiagonalmatrix_left_solve(mtr), mtr->size, "%lf ");
  printf("\n");

  return 0;
}