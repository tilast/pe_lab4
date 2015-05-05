#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "./lib/matrix.h"

int main(int argc, char** argv)
{
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Find out rank, size
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // We are assuming at least 2 processes for this task
  if (world_size != 2) {
    fprintf(stderr, "This taks can be executed in 2 processes only %s\n", argv[0]);
    MPI_Abort(MPI_COMM_WORLD, 1); 

    return 1;
  }

  // matrix *mtr = read_matrix("./data/with_ruby_10000.dat");
  matrix *mtr = read_matrix("./data/big_matrix.dat");

  int p = mtr->size / 2 + (mtr->size % 2);
  double* alphas = allocate(double, mtr->size);
  double* betas  = allocate(double, mtr->size);
  double* xies   = allocate(double, mtr->size);
  double* etas   = allocate(double, mtr->size);
  double* xs     = allocate(double, mtr->size);

  if(world_rank == 0)
  {
    calculate_alphas_and_betas(mtr, alphas, betas, p);
    MPI_Send(alphas, mtr->size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
    MPI_Send(betas, mtr->size, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD);

    MPI_Recv(xies, mtr->size, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(etas, mtr->size, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }
  else
  {
    calculate_xies_and_etas(mtr, xies, etas, p);
    MPI_Send(xies, mtr->size, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    MPI_Send(etas, mtr->size, MPI_DOUBLE, 0, 3, MPI_COMM_WORLD);

    MPI_Recv(alphas, mtr->size, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(betas, mtr->size, MPI_DOUBLE, 1, 3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  }

  xs[p] = (alphas[p+1]*etas[p+1] + betas[p+1]) / (1 - alphas[p+1]*xies[p+1]);


  if(world_rank == 0)
  {
    for(int i = p - 1; i >= 0; --i)
    {
      xs[i] = alphas[i+1] * xs[i+1] + betas[i+1];
    }

    double* xs_temp = allocate(double, mtr->size);
    MPI_Recv(xs_temp, mtr->size, MPI_DOUBLE, 1, 4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for(int i = 0; i < p; ++i)
    {
      xs[i] = xs_temp[i];
    }

    print_vector(xs, mtr->size, "%lf ");
  }
  else
  {
    for(int i = p; i < mtr->size - 1; ++i)
    {
      xs[i + 1] = xies[i+1] * xs[i] + etas[i+1];
    }

    MPI_Send(xs, mtr->size, MPI_DOUBLE, 0, 4, MPI_COMM_WORLD);
  }

  return 0;
}