#ifndef _STACK_H_
#define _STACK_H_
#include "vector.h"

typedef struct Stack Stack;

typedef Stack stack;

typedef stack* stackp;


/*
	Description: allocate a stack with given size and block size
	input: _initialSize - the size of diary to be allocated
	       _blockSize   - block size when resizing diary	 	
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
stackp StackCreate(size_t _initialSize,size_t _blockSize);

/*
	Description: free stack and free it's diary
	input: adPtr - pointer to an ad_t
*/
void StackDestroy(stackp _stPtr);
/*
	Description: get number of elements
	output: number of elements if they exist, 0 otherwise
*/
size_t StackNumOfElements(stackp _stPtr);

/*
	Description: push a new value to the stack
	input: _stPtr	 - pointer to a stack
	       _data	 - value to be added
	output: ERR_SUCCESS if added, ERRCODE otherwise
*/
ERRCODE StackPush(stackp _stPtr ,int _data);

/*
	Description: pop a value from the stack
	input: _stPtr	- pointer to an stack
	       _data 	- pointer to removed value
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE StackPop(stackp _stPtr ,int* _data);

/*
	Description: retrieve a a value from the stack top
	input: _stPtr	- pointer to an stack
	       _data 	- pointer to removed value
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE StackTop(stackp _stPtr ,int* _data);

/*
	Description: check if stack is empty
	input: _stPtr	 - pointer to a vector
	output: true if empty, false otherwise
*/
int StackIsEmpty(stackp _stPtr);


/*
	Description: Print stack data and all it's elements for debug 
	input: _stPtr	 - pointer to a vector
	output: number of element printed
*/	
int StackPrint(stackp _stPtr);


#endif /*end of _STACK_H_*/

