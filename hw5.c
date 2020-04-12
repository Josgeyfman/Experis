#include<stdio.h>
#include<stdlib.h>
#include"hw5.h"

int PrintPtrArr(int* _arr,int _size)
{
	int i;
	if(NULL==_arr || _size<0)
	{
		return ERR_ILLEGAL_INPUT;
	}
	printf("array:[");
	for(i=0;i<_size;i++)
	{
		printf("%d",_arr[i]);
		if(i!=_size-1)
		{
			printf(", ");
		}
	}
	printf("]\n");
	return SUCCESS;
}

int * DynamicArrayCreate(int _size)
{
	int *ptr;
	if(_size>0)
	{
		ptr = (int*) malloc(_size*sizeof(int));
		if(ptr==NULL)
		{
			printf("\nmemory allocation error\n");
			return NULL;
		}
		return ptr;
	}
	return NULL;
}

void DynamicArrayDestroy( int  *_DynaminArrayPtr)
{
	if(_DynaminArrayPtr==NULL)
	{
		printf("\nerror nothing to free\n");
		return;
	}
	free(_DynaminArrayPtr);
}

int * ResizeArr(int* _arr,int _newSize)
{
	int* newPtr =_arr;
	if(NULL==_arr || _newSize < 0)
	{
		return NULL;
	}
	newPtr = (int*)realloc(_arr,_newSize*sizeof(int));
	if(newPtr==NULL)
	{
		printf("\nmemory reallocation error\n");
		return _arr; 
	}
	_arr = newPtr;
	return _arr;	
}

int DynamicArrayInsert(int ** _DynaminArrayPtr, int _data, int* _DaSize, int* _DaNumOfElements, int _IncBlockSize)
{
	int* newPtr;
	if(NULL==_DynaminArrayPtr || NULL==_DaSize || NULL==_DaNumOfElements || _IncBlockSize<1)
	{
		return ERR_ILLEGAL_INPUT;
	}
	
	if(*_DaSize==*_DaNumOfElements)
	{
		newPtr = ResizeArr(*_DynaminArrayPtr,_IncBlockSize+(*_DaSize));
		if(newPtr==NULL)
		{
			return ERR_OVERFLOW;
		}
		_DynaminArrayPtr = &newPtr;
		(*_DaSize)+=_IncBlockSize;
	}
	
	(*_DynaminArrayPtr)[(*_DaNumOfElements)++]=_data;
	
	return SUCCESS; 
}



int DynamicArrayDelete(int  *_DynaminArrayPtr, int* _data, int* _DaNumOfElements )
{
	if(NULL==_DaNumOfElements || NULL==_DynaminArrayPtr || NULL== _data) 
		return ERR_ILLEGAL_INPUT;
	}
	if(*_DaNumOfElements>0)	
	{
		(*_data)=_DynaminArrayPtr[*_DaNumOfElements-1];
		_DynaminArrayPtr[--(*_DaNumOfElements)]=0;
		return SUCCESS;
	}
	return ERR_UNDERFLOW;	
	
}





