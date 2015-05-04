#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "./lib/matrix.h"

int main()
{
  matrix *mtr = read_matrix("./data/with_ruby_10000.dat");

  clock_t start;
  clock_t end;
  float seconds;

  start = clock();
    tridiagonalmatrix_left_solve(mtr);
  end = clock();
  seconds = (float)(end - start) / CLOCKS_PER_SEC;

  printf("left: %lf\n", seconds);

  start = clock();
    tridiagonalmatrix_right_solve(mtr);
  end = clock();
  seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("right: %lf\n", seconds);

  start = clock();
    tridiagonalmatrix_parallel_solve(mtr);
  end = clock();
  seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("parallel: %lf\n", seconds);

  return 0;
}