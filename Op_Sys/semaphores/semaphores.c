#include <stdio.h> 
#include <pthread.h> 
#include <semaphore.h> 
#include <unistd.h> 
#include <stdlib.h>
#define LEN 10

int item = 0;

sem_t mutex,empty,full; 
  
void* Consume(void* tid) 
{ 
   	while(1)
	{
		 sem_wait(&full); 
		 sem_wait(&mutex); 
		 item--;
		 printf("item consumed %d tpid %lu\n",item,(size_t)tid);	
	         sem_post(&mutex);
		 sem_post(&empty);
		
	}
	exit(0);
} 
  
void* Produce(void* tid)
{
	while(1)
	{
		sem_wait(&empty); 
		sem_wait(&mutex); 
		item++;
		printf("item produced %d tid %lu\n",item,(size_t)tid);
		sem_post(&full);
		sem_post(&mutex); 
		
	}
	exit(0);
}  

int main() 
{  
    size_t i;
    pthread_t threads[LEN]; 
    sem_init(&mutex, 0, 1); 
    sem_init(&empty, 0, 100); 
    sem_init(&full, 0, 0);
    for(i=0;i<LEN-1;i+=2)
    { 
	    pthread_create(&threads[i],NULL,Produce,(void*)i); 
	    pthread_create(&threads[i+1],NULL,Consume,(void*)(i+1)); 
    }
    for(i=0;i<LEN-1;i+=2)
    { 
	    pthread_join(threads[i],NULL); 
	    pthread_join(threads[i+1],NULL); 
    }
    sem_destroy(&mutex); 
    sem_destroy(&empty);
    sem_destroy(&full);
    return 0; 
} 
