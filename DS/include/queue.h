#ifndef _QUEUE_H_
#define _QUEUE_H_

#include<stdlib.h>
#include <stdio.h>

#include "adt_error.h"


#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

typedef enum{true=1,false=0} Bool;

typedef struct Queue queue;

typedef queue* queuep;


/*
	Description: allocate Queue with given size 
	input: _initialSize - the size of diary to be allocated
	output: pointer to allocted Queue ,NULL otherwise
*/ 
queuep QueueCreate(size_t _initsize);

/*
	Description: free Queue 
	input: adPtr - pointer to an ad_t
*/
void QueueDestroy(queuep _quep);

/*
	Description: get number of elemnts in Queue
	output: number of elements if Queue exists, 0 otherwise
*/
size_t QueueNumOfElements(queuep _quep);

/*
	Description: insert a new value to the queue tail
	input: _quep	 - pointer to a queue
	       _data	 - value to be added
	output: ERR_SUCCESS if added, ERRCODE otherwise
*/
ERRCODE QueueEnqueue(queuep _quep ,int data);

/*
	Description: remove a value from the queue head
	input: _quep	- pointer to an ad_t
	       _data 	- pointer to removed value
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE QueueDequeue(queuep _quep ,int* _data);

/*
	Description: check if queue is empty
	output: true if queue empty, false otherwise
*/
Bool QueueIsEmpty(queuep _quep);

/*
	Description: Print Vector data and all it's elements
	input: _vecp	 - pointer to a vector
	output: number of element printed
*/	
int QueuePrint(queuep _quep);



#endif /*end of _QUEUE_H_*/

