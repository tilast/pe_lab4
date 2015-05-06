# lab 4
Create ```bin``` folder:
```
mkdir bin
```

## OpenMP
To compile open mp version:
```
gcc main.c -o ./bin/openmp -std=c99
```
To run this:
```
./bin/openmp
```

# MPI
To install MPI on Ubuntu:
```
https://jetcracker.wordpress.com/2012/03/01/how-to-install-mpi-in-ubuntu/
```
To compile mpi version:
```
mpicc mpi.c -o ./bin/mpiversion -std=c99
```
To run this(works just with 2 processes):
```
mpirun -np 2 ./bin/mpiversion
```
