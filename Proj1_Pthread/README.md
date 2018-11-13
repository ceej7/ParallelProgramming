## Project 1 Pthread
### Pthread Intro
Pthreads are defined as a set of C/C++ language programming types and procedure calls in shared memory multiprocessor architectures, implemented with a pthread.h header/include file and a thread library - though this library may be part of another library, such as libc, in some implementations.
### TODO: Basic Function
To fork and join Pthread.
```C
int pthread_create(pthread_t *,                                        
		   const pthread_attr_t *,              
		   void * (*)(void *),   
                   void *);
\\thread_id  is the thread id or handle (used to halt, etc.) 
\\thread_attribute various attributes-standard default values obtained by passing a NULL pointer
\\thread_fun the function to be run (takes and returns void*)
\\fun_arg an argument can be passed to thread_fun when it starts
\\errorcode will be set to nonzero if the create operation fails

int pthread_join(pthread_t thread, void **value_ptr)
\\The second parameter allows the exiting thread to pass information
\\back to the calling thread (often NULL).
\\Returns nonzero if there is an error
```
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
