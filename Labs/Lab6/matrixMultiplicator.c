#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void *thread_routine(void *arg)
{
    int *args = (int *)arg;
    int len = args[0];
    //printf("!! LUNGIME=%d !!",len);
    //len = 3;
    //printf("!! LUNGIME=%d !!",len);
    int *ret = malloc(sizeof(int));
    *ret = 0;

    for (int i = 1; i <= len; i++)
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
	int args[COUNT][2*n+1];



	cont = 0;
	for(int i=0;i<n;i++)
	{
		for(int k=0;k<n;k++)
		{
			for(int j=0;j<n;j++)
			{
				args[cont][j+1] = matrix[i][j];
			}
			args[cont][0]=n;
			cont++;
		}
	}
	
	cont = 0;
	for(int k=0;k<n;k++)
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				args[cont][j+n+1] = matrix2[j][i];
			}
			cont++;
		}
/*
	for(int i=0;i<COUNT;i++)
	{
		for(int j=0;j<2*n;j++)
			printf("%d ", args[i][j]);
		printf("\n");
	}
*/
	for(int i=0;i<COUNT;i++)
		pthread_create(&thread[i],NULL,thread_routine,args[i]);	
	
		
		
	
	cont = 0;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
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
