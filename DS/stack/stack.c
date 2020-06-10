
#include "vector.h"
#include "stack.h"

struct Stack {
	
 	vectorp  vec;

}; 



size_t StackNumOfElements(stackp _stPtr)
{
	if(!_stPtr)	
	{
		return 0;
	}

	return VectorNumOfElements(_stPtr->vec);
}


stackp StackCreate(size_t _initialSize,size_t _blockSize)
{
	stackp stPtr = (stackp)malloc(sizeof(stack));
	if(!stPtr)
	{
		return NULL;
	}
	stPtr->vec = VectorCreate(_initialSize,_blockSize);
	if(!stPtr->vec)
	{
		free(stPtr);
		return NULL;
	}
	return stPtr;
}


void StackDestroy(stackp _stPtr)
{
	if(_stPtr!=NULL)
	{
		if(_stPtr->vec!=NULL)
		{
			VectorDestroy(_stPtr->vec);
		}
		free(_stPtr);
	}
}

ERRCODE StackPush(stackp _stPtr ,int _data)
{
	if(!_stPtr)
	{
		return ERR_ILLEGAL_INPUT;
	}
	return VectorAddTail(_stPtr->vec,_data);

}

ERRCODE StackPop(stackp _stPtr ,int* _data)
{
	if(!_stPtr)
	{
		return ERR_ILLEGAL_INPUT;
	}
	return VectorRemoveTail(_stPtr->vec,_data);

}

ERRCODE StackTop(stackp _stPtr ,int* _data)
{
	if(!_stPtr || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	return VectorGet(_stPtr->vec,StackNumOfElements(_stPtr),_data);
}

int StackIsEmpty(stackp _stPtr)
{
	if(!_stPtr)
	{
		return 0;
	}
	return (StackNumOfElements(_stPtr)==0);
}

int StackPrint(stackp _stPtr)
{
	if(!_stPtr)
	{
		return ERR_ILLEGAL_INPUT;
	}
	return VectorPrint(_stPtr->vec);
}





