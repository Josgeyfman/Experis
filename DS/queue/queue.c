#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "vector.h"
struct Queue
{
	size_t head;
	size_t tail;
	size_t max;
	size_t magicNum;
	size_t elementNum;
	vectorp vec;
};

Bool QueueIsEmpty(queuep _quep)
{
	if (_quep && _quep->elementNum == 0)
	{
		return 1;
	}
	return 0;	
}

static Bool isFull(queuep _quep)
{ 
	if(_quep)
	{
		return (QueueNumOfElements(_quep) == _quep->max) ;
	}
	return false;
}

static void InitVector(vectorp _vec,size_t _size)
{
	int i=0;
	while(i<_size)
	{
		VectorAddTail(_vec,0);
		i++;
	}


}

queuep QueueCreate(size_t _initsize){
	
	vectorp _vec;	
	queuep _quep = (queuep)malloc(sizeof(queue));
	if(!_quep){
		return NULL;
	}
	_vec = VectorCreate(_initsize,0);
	if(!_vec){
		return NULL;
	}	
	_quep->vec=_vec;
	_quep->head=1;
	_quep->tail=1;
	_quep->max=_initsize;
	_quep->elementNum = 0;
	_quep->magicNum=MAGIC_NUM;
	InitVector(_quep->vec,_initsize);
	return _quep;
}

void QueueDestroy(queuep _quep)
{
	if(!_quep || _quep->magicNum != NOT_MAGIC_NUM)
	{
		return;
	}
	VectorDestroy(_quep->vec);
	_quep->magicNum=NOT_MAGIC_NUM;
	free(_quep);
	
}

ERRCODE QueueEnqueue(queuep _quep ,int _data)
{
	if(_quep && !isFull(_quep))
	{
		VectorSet(_quep->vec,_quep->tail,_data);
		_quep->elementNum++;
		_quep->tail = (_quep->tail % _quep->max) + 1 ;	
		return ERR_SUCCESS;
	}
	return ERR_FULL;
}

ERRCODE QueueDequeue(queuep _quep ,int* _data)
{
	if(!_quep || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(QueueIsEmpty(_quep))
	{
		return ERR_EMPTY;
	}
	VectorGet(_quep->vec,_quep->head,_data);
	_quep->head = (_quep->head % _quep->max) + 1  ;
	_quep->elementNum--;
	return ERR_SUCCESS;
}

size_t QueueNumOfElements(queuep _quep )
{
	if(!_quep)
	{
		return 0;
	}
	
	return _quep->elementNum ;

}

int QueuePrint(queuep _quep)
{
	int i,data;
	if(!_quep)
	{
		return -1;
	}
	VectorGet(_quep->vec,1,&data);
	printf("QUEUE data: head:%lu tail:%lu max:%lu\n" ,_quep->head ,_quep->tail ,_quep->max);
	if(QueueIsEmpty(_quep))
	{
		printf("empty Queue\n");
		return 0;
	}
	
	if(_quep->head>_quep->tail)
	{
		for(i=_quep->head;i<_quep->max;i++)
		{
			VectorGet(_quep->vec,i,&data);
			printf("[%d]" ,data);
		}
		for(i=1;i<=_quep->tail;i++)
		{	
			VectorGet(_quep->vec,i+1,&data);
			printf("[%d]" ,data);
		}
	}
	else
	{
		for(i = _quep->head; i < _quep->tail ; i++)
		{
			VectorGet(_quep->vec,i,&data);
			printf("[%d]" ,data);
		}
	}
	printf("\n");
	return i;
}


