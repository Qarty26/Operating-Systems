#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *thread_routine(void *arg)
{
    int *args = (int *)arg;
    int len = 2;
    int *ret = malloc(sizeof(int));
    *ret = 0;

    for (int i = 0; i < len; i++)
    {
        *ret += args[i] * args[i + len];
    }
    return (void *)ret;
}

int main(int argc, char** argv)
{

	int n =atoi( argv[1]);
	#define COUNT n*n	
	int cont = 2;
	int matrix[100][100],matrix2[100][100];


	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			matrix[i][j] = atoi( argv[cont]);
			cont++;
		}
		
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			matrix2[i][j] = atoi( argv[cont]);
			cont++;
		}


	pthread_t thread[COUNT];
	int args[COUNT+1][2*n];



	cont = 0;
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<n;k++)
		{
			for(int j=0;j<n;j++)
			{
				args[cont][j] = matrix[i][j];
			}
			cont++;
		}
	}
	
	cont = 0;
	for(int k=0;k<n;k++)
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			args[cont][j+n] = matrix2[j][i];
		}
		cont++;
	}

	for(int i=0;i<COUNT;i++)
		pthread_create(&thread[i],NULL,thread_routine,args[i]);	
	
		
		
	
	cont = 0;
	for(int i=0;i<COUNT/2;i++)
	{
		for(int j=0;j<COUNT/2;j++)
		{
			int* ret;
			pthread_join(thread[cont],(void **)&ret);
			printf("%d ",*ret);
			cont++;
		}
		printf("\n");
	}
	
	return 0;		
}
/*
i have a function that returns the result of only a cell from a matrix. In that function i recieve as a parameter an array that is like this: the first half are the numbers from the line from the first matrix, and the second half are numbers from the column from the second matrix. I already have this function and it works perfecty. I need an algorithm that creates the array that i will give as a parameter*/
