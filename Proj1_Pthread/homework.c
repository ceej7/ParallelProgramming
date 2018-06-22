#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/*global var statement*/
int thread_count;
double** A;
double* x;
double* y;
int m;
int n;

void* mat_vect(void *rank);

int main(int argc,char *argv[])
{
	/*local var statement*/
	long thread;					/*use long in case of a warning on 64-bit system*/
	pthread_t *thread_handles;
	int i;
	int j;
	char * file;
	FILE *fp;
	FILE *fp_result;
	char tmp[100];

	/*Get the sample_input.txt*/
	file=argv[1];
	fp=fopen(file,"r");
	fp_result=fopen("output.txt","w");

	/*Get the m, n and the number of threads from command line*/
	fgets(tmp,100,fp);	
	fscanf(fp,"%d\n",&m);	
	fgets(tmp,100,fp);
	fscanf(fp,"%d\n",&n);
	fgets(tmp,100,fp);
	fscanf(fp,"%d\n",&thread_count);
	/*Allocate the memory for A,x.y adn thread_handles*/
	thread_handles=malloc(thread_count*sizeof(pthread_t));
	A=malloc(m*sizeof(char *));
	for(i=0;i<m;i++)
	{
		(*(A+i))=malloc(n*sizeof(double));
	}
	x=malloc(n*sizeof(double));
	y=malloc(m*sizeof(double));

	/*Get the m*n matrix A from user input */
	fgets(tmp,100,fp);
	for(i=0;i<m;i++)
	{
		for(j=0;j<n;j++)
		{
			fscanf(fp,"%lf\n",*(A+i)+j);
		}
	}

	/*Get the n-dimensional Vector x from user input */
	fgets(tmp,100,fp);
	for(i=0;i<n;i++)
	{
		fscanf(fp,"%lf\n",&x[i]);
	}

	/*Threads created with it own number thread*/
	for(thread=0;thread<thread_count;thread++)
	{
		pthread_create(&thread_handles[thread],NULL,mat_vect,(void *) thread);
	}

	/*Wait for the accomplishment of all threads*/
	for(thread=0;thread<thread_count;thread++)
	{
		pthread_join(thread_handles[thread],NULL);
	}

	/*Out put the result in format*/
	for(i=0;i<m;i++)
	{
		//for the normalized output format
		fprintf(fp_result,"%.2lf",y[i]);
		if(i!=m-1)
		{
			fprintf(fp_result," ");
		}
	}

	/*free the memeory the global var*/
	free(thread_handles);
	free(y);
	free(x);
	for(i=0;i<m;i++)
	{
		free((*(A+i)));
	}
	free(A);

	return 0;
}

/*mat calculate thread method*/
void* mat_vect(void *rank)
{
	long my_rank=(long)rank;
	int i,j;
	int my_first_row;
	int my_last_row;
	/*if the number of threads is larger or equal than m*/
	if(m<=thread_count)
	{
		if((int)my_rank<m)
		{
			my_first_row=my_last_row=my_rank;
		}
		else{
			return NULL;
		}
	}
	/*if the number of threads is smaller than m*/
	else{
		int p=m/thread_count;
		int q=m%thread_count;
		if((int)my_rank<q)
		{
			my_first_row=my_rank*(p+1);
			my_last_row=my_first_row+p;
		}
		else{
			my_first_row=q*(p+1)+(my_rank-q)*p;
			my_last_row=my_first_row+p-1;
		}	
	}
	for(i=my_first_row;i<=my_last_row;i++)
	{
		y[i]=0.0;
		for(j=0;j<n;j++)
		{
			y[i]+=A[i][j]*x[j];
		}
	}

	return NULL;
}