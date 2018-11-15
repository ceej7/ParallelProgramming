# Parallel Programming
These are the projects of the course, Parallel Programming. Two easy tasks are implemented by different parallel architecture.
## Project 1 Pthread
### Pthread Intro
Pthreads(POSIX Threads), is defined as a set of C/C++ language programming types and procedure calls in shared memory multiprocessor architectures, used for defining and manipulating threads.
### TODO: Basic Function
To fork and join Pthread.
```C
int pthread_create(pthread_t *tidp, const pthread_attr_t *attr,              
		   void * (*fun)(void *), void *arg);
```
thread_id  is the thread id or handle (used to halt, etc.) 
thread_attribute various attributes-standard default values obtained by passing a NULL pointer
thread_fun the function to be run (takes and returns void*)
fun_arg an argument can be passed to thread_fun when it starts
return errorcode will be set to nonzero if the create operation fails

```C
int pthread_join(pthread_t thread, void **value_ptr)
```
The second parameter allows the exiting thread to pass information
back to the calling thread (often NULL).
Returns nonzero if there is an error

### Compile
```bash
gcc homework.c -o homework -lpthread
```

### Test
```bash
./homework sample_input.txt
```
### Result
Result is located at "output.txt", with float precision and accurate to the second decimal place.

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
