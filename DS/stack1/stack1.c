#include "vector.h"
#include "stack.h"


size_t StackNumOfElements(stackp _stPtr)
{
	
	return VectorNumOfElements((vectorp)_stPtr);
}

stackp StackCreate(size_t _initialSize,size_t _blockSize)
{
	return (stackp) VectorCreate(_initialSize,_blockSize);;
}

void StackDestroy(stackp _stPtr)
{
	VectorDestroy((vectorp)_stPtr);
}

ERRCODE StackPush(stackp _stPtr ,int _data)
{
	return VectorAddTail((vectorp)_stPtr,_data);
}

ERRCODE StackPop(stackp _stPtr ,int* _data)
{
	return VectorRemoveTail((vectorp)_stPtr,_data);
}

ERRCODE StackTop(stackp _stPtr ,int* _data)
{
	return VectorGet((vectorp)_stPtr,StackNumOfElements(_stPtr),_data);
}

int StackIsEmpty(stackp _stPtr)
{
	return (StackNumOfElements(_stPtr)==0);
}

int StackPrint(stackp _stPtr)
{
	return VectorPrint((vectorp)_stPtr);
}





