#include "mymalloc.h"


void MyMallocInit(void* _memory, size_t _memorySize)
{
	int *memory;
	if(!_memory || _memorySize==0)
	{
		return;
	}
	memory = (int*) _memory;
	memory[0]=_memorySize;
	memory[1]=_memorySize-3*sizeof(int);
	memory[_memorySize-1] = 0;
}

void* MyMalloc(void* _memory, size_t _requiredBlockSize)
{
	register int i = 1;
	int* metadata;
	int* nextBlock;
	BYTE* mem;
	if(!_memory || _requiredBlockSize==0)
	{
		return NULL;
	}
	mem = (BYTE*)_memory;
	nextBlock = ((int*)mem+i);
	while(*nextBlock<0 && *nextBlock<(int)_requiredBlockSize)	/*find next available block*/
	{
		if(*nextBlock<0)
		{
			i += (*nextBlock * -1) + 1;
		}	
		else
		{
			i += *nextBlock + 1;
		}
		nextBlock = ((int*)mem+i);
	}
	if(*nextBlock==0 || *nextBlock<_requiredBlockSize) 	/*if not found or not enough space return Null */
	{
		return NULL;
	}
	metadata = nextBlock +_requiredBlockSize+1; 			/*point metadata to next available block */
	*metadata = *nextBlock-_requiredBlockSize; 		/*update metadata of next available block */
	metadata = nextBlock;					/*point metadata to current metadata block */
	*metadata = -1*(_requiredBlockSize); 			/*occupy current block*/
	return metadata+1; 					/*return pointer to allocted block*/
}

void MyFree(void* _myBlock)
{
	int freeSize;
	BYTE* mem;
	if(!_myBlock)
	{
		return ;
	}
	mem = (BYTE*)_myBlock;
	freeSize = *((int*)mem-1)*(-1); /*release memory*/
	*((int*)mem-1) = freeSize;
	if(*((int*)mem+freeSize)>0) 	/*if next block is available merge two blocks*/
	{
		*((int*)mem-1) += *((int*)mem+freeSize);
	}
}
