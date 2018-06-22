#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

//compare for local qsort
int cmp(const  void *a,const  void  *b);
//merge for tree_merge
int *merge(int * a, int * b, int n);

int main(int argc,char *argv[]){
	int comm_sz;
	int my_rank;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int n=0;
	int* global=NULL;
	int* local;
	int local_n;
	int * rec_buf;

	
	if(my_rank ==0){
		/*local var statement*/
		char * file;
		FILE *fp;
		int tmp;

		/*Get the sample_input.txt*/
		file=argv[1];
		fp=fopen(file,"r");

		/* i/o to get n */
		while(fscanf(fp,"%d",&tmp)!=EOF)
		{
			n++;
		}
		global=(int *)malloc(sizeof(int)*n);

		/* i/o */
		fseek(fp,0L,SEEK_SET);
		n=0;
		while(fscanf(fp,"%d",&tmp)!=EOF)
		{

			global[n++]=tmp;
		}

		//get local_n in p0
		local_n=n/comm_sz;
	}
	
	//broadcast local_n to all
	MPI_Bcast(&local_n,1,MPI_INT,0,MPI_COMM_WORLD);

	//scatter the global to all
	local=(int *)malloc(sizeof(int)*local_n);
	MPI_Scatter(global,local_n,MPI_INT,local,local_n,MPI_INT,0,MPI_COMM_WORLD);
	free(global);
	global=NULL;
	//sort the local in all
	qsort(local,local_n,sizeof(int),cmp);

	//Step1
	if(my_rank%2==0)
	{
		rec_buf=(int *)malloc(sizeof(int)*local_n);
		MPI_Recv(rec_buf,local_n,MPI_INT,my_rank+1,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int *merged=merge(local,rec_buf,local_n);
		free(rec_buf);
		rec_buf=NULL;
		free(local);
		local=merged;
		local_n=local_n*2;
	}
	else{
		MPI_Send(local,local_n,MPI_INT,my_rank-1,1,MPI_COMM_WORLD);
		free(local);
		local=NULL;
		//return 0;
	}

	//Step2
	if(my_rank%2==0&&my_rank%4==0)
	{
		rec_buf=(int *)malloc(sizeof(int)*local_n);
		MPI_Recv(rec_buf,local_n,MPI_INT,my_rank+2,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int *merged=merge(local,rec_buf,local_n);
		free(rec_buf);
		rec_buf=NULL;
		free(local);
		local=merged;
		local_n=local_n*2;
	}
	else if (my_rank%2==0){
		MPI_Send(local,local_n,MPI_INT,my_rank-2,2,MPI_COMM_WORLD);
		free(local);
		local=NULL;
		//return 0;
	}
	
	//Step3
	if(my_rank%2==0&&my_rank%4==0&&my_rank%8==0)
	{
		rec_buf=(int *)malloc(sizeof(int)*local_n);
		MPI_Recv(rec_buf,local_n,MPI_INT,my_rank+4,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		int *merged=merge(local,rec_buf,local_n);
		free(rec_buf);
		rec_buf=NULL;
		free(local);
		local=merged;
		local_n=local_n*2;
	}
	else if (my_rank%2==0&&my_rank%4==0){
		MPI_Send(local,local_n,MPI_INT,my_rank-4,3,MPI_COMM_WORLD);
		free(local);
		local=NULL;
		//return 0;
	}
	
	//output
	if(my_rank==0)
	{
		int p;
		for(p=0;p<local_n;p++)
		{
			printf("%d ", local[p]);
		}
		printf("\n");
	}
	
	MPI_Finalize();
	return 0;
}

int cmp(const  void *a,const  void  *b)
{

    return *(int *)a-*(int *)b;
}

int *merge(int * a, int * b, int n)
{
	int *out_p=(int *)malloc(sizeof(int)*2*n);
	int i=0,j=0;
	int cnt=0;
	while(cnt<2*n)
	{
		if(i<n&&j<n)
		{
			if(a[i]<=b[j])
			{
				out_p[cnt++]=a[i++];
			}
			else{
				out_p[cnt++]=b[j++];
			}
		}
		else if(i<n)
		{
			out_p[cnt++]=a[i++];
		}
		else{
			out_p[cnt++]=b[j++];
		}
	}
	return out_p;
}