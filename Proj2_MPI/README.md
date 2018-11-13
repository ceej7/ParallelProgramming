## Project 2 MPI
### MPI Intro
Message passing is the principle alternative to shared memory parallel programming, predominant programming model for supercomputers and clusters.
### TODO: Hello
To fork and join Pthread.
```C
#include "mpi.h"
#include <stdio.h>
int main( int argc, char *argv[] )
{
	int rank, size;
	MPI_Init( &argc, &argv );
	MPI_Comm_rank( MPI_COMM_WORLD, &rank );
	MPI_Comm_size( MPI_COMM_WORLD, &size );
	printf( ”Greetings from process %d of %d\n", rank, size );
	MPI_Finalize();
	return 0;
}
```
### Compile
```bash
mpiexec -g -Wal -o homework homework.c
```
### Test
```bash
mpiexec -n 8 ./homework input.txt
```
### Result
Result is located at "output.txt", with a sorted numeric list.
