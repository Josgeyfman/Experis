#include <pthread.h>
#include <stdio.h>
#define THREAD_NUM 10
int globalVar;

void* PrintFunc(void* tid)
{
	int i;
	for(i=0;i<1000;i++)
	{
		printf("Thread %d global var %d \n",*(int*)tid,globalVar++);
	}
	pthread_exit(NULL);
}


 
int main()
{

	int i;
	int status;
	pthread_t threads[THREAD_NUM];

	for(i=0;i<THREAD_NUM;i++)
	{
		status = pthread_create(&threads[i],NULL,PrintFunc,(void*)&i);
		if(status)
		{
			printf("create \n");
		}

	}
	for(i=0;i<THREAD_NUM ;i++)
	{
		pthread_join(threads[i],NULL);

	}
	return 0;
}

