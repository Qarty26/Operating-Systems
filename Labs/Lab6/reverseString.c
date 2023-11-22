#include <errno.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>


void *thread_routine(void *arg)
{
	char* str = (char*) arg;
	int length = strlen(str);
	int i,j;
	for(i=0,j=length-1;i<j;i++,j--)
	{
		char temp =  str[i];
		str[i]=str[j];
		str[j]=temp;
	}			 

	printf("%s",str);
}


int main(int argc, char** argv)
{

	pthread_t thread;
	pthread_create(&thread,NULL,thread_routine,argv[1]);
	pthread_join(thread,NULL);

	return 0;
}
