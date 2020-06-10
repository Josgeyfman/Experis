#include"vector.h"
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

struct Vector{

	int * varr;
	size_t blockSize;
	size_t elementNum;
	size_t size;
	size_t initSize;  
	size_t magicNum;
}; 

size_t VectorNumOfElements(vectorp _vec)
{
	if(!_vec)	
	{
		return 0;
	}

	return _vec->elementNum;
}

ERRCODE SetVector(vectorp _vPtr, int* _arrPtr, size_t _initialSize , size_t _blockSize , size_t _elementNum,size_t _initSize)
{
	if(!_vPtr)
	{
		return ERR_ILLEGAL_INPUT;
	}
	_vPtr->varr       = _arrPtr;
	_vPtr->blockSize  = _blockSize;
	_vPtr->size	  = _initialSize; 
	_vPtr->elementNum = _elementNum; 
	_vPtr->initSize   = _initSize;
        _vPtr->magicNum   = MAGIC_NUM;
	return ERR_SUCCESS;
}

vectorp VectorCreate(size_t _initialSize,size_t _blockSize)
{
	vectorp vecPtr = NULL;
	int* arrPtr = NULL;
	ERRCODE result;
	if(_initialSize == 0 && _blockSize==0 )
	{
		return vecPtr;

	}
	
	vecPtr = (vectorp)malloc(sizeof(vector));
	if(!vecPtr)
	{
		return vecPtr;
	}
	
	arrPtr=(int*)malloc((_initialSize+1)*sizeof(int));
	if(!arrPtr)
	{
		free(vecPtr);
		return NULL;
	}	

	result = SetVector(vecPtr,arrPtr,_initialSize,_blockSize,0,_initialSize);
	if(result != ERR_SUCCESS)
	{
		free(arrPtr);
		arrPtr=NULL;
		free(vecPtr);
		vecPtr=NULL;
	}
	return vecPtr;
	
}


void VectorDestroy(vectorp _vecPtr)
{
	if(!_vecPtr ||  _vecPtr->magicNum != MAGIC_NUM)
	{
		return;
	}
	if(_vecPtr->varr)
	{
		free(_vecPtr->varr);
	}
	_vecPtr->magicNum = NOT_MAGIC_NUM;
	free(_vecPtr);
	
}

static ERRCODE VectorResize(vectorp _vecPtr ,size_t _newSize)
{
	int* temp_p = _vecPtr->varr;
	if(!_vecPtr || _newSize<1  || _vecPtr->magicNum != MAGIC_NUM)
	{
		return ERR_ILLEGAL_INPUT;	
	}
	temp_p = (int*)realloc((_vecPtr->varr),(_newSize+1)*sizeof(int));
	if(temp_p)
	{
		_vecPtr->size = _newSize;
		_vecPtr->varr = temp_p;
		return ERR_SUCCESS;
	}
	return ERR_MEM_ALLOC;
		
}

ERRCODE VectorAddTail(vectorp _vecPtr ,int _data)
{
	size_t newSize;
	ERRCODE result = ERR_ILLEGAL_INPUT;
	if(!_vecPtr || _vecPtr->magicNum != MAGIC_NUM)
	{
		return result;
	}
	if(_vecPtr->elementNum==_vecPtr->size)
	{
		newSize = _vecPtr->size + _vecPtr->blockSize;
		if(newSize <=_vecPtr->size)
		{
			return ERR_UNDERFLOW;
		}
		result = VectorResize(_vecPtr,newSize);
		if(ERR_SUCCESS!=result)
		{
			return result;
		}
		
	}
	(_vecPtr->varr)[++(_vecPtr->elementNum)] = _data;
	return ERR_SUCCESS;
		
}

ERRCODE VectorRemoveTail(vectorp _vecPtr ,int* _data)
{
	size_t newSize;
	ERRCODE result;
	if(!_vecPtr || !_data ||  _vecPtr->magicNum != MAGIC_NUM)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_vecPtr->elementNum<0)
	{
		return ERR_UNDERFLOW;
	}
	(*_data) = _vecPtr->varr[(_vecPtr->elementNum)--];	
			
	if(_vecPtr->elementNum ==_vecPtr->size-(2*_vecPtr->blockSize))
	{
		newSize =  _vecPtr->size - _vecPtr->blockSize;
		if(newSize >=_vecPtr->initSize)
		{
			result = VectorResize(_vecPtr,newSize);
			if(ERR_SUCCESS!=result)
			{
				return result;
			}
		}
	}
	return ERR_SUCCESS;	
	
		
			
				
	
}

ERRCODE VectorSet(vectorp _vecPtr ,size_t _index ,int _data)
{
	if(!_vecPtr ||  _vecPtr->magicNum != MAGIC_NUM)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecPtr->elementNum)	
	{
		return ERR_OVERFLOW;
	}
	if(_index<=0)
	{
		return ERR_UNDERFLOW;
	}
	_vecPtr->varr[_index]=_data;
	return ERR_SUCCESS;
}

ERRCODE VectorGet(vectorp _vecPtr ,size_t _index ,int* _data)
{
	
	if(!_vecPtr || !_data ||  _vecPtr->magicNum != MAGIC_NUM)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecPtr->elementNum)	
	{	
		return ERR_OVERFLOW;
	}
	if(_index<=0)
	{
		return ERR_UNDERFLOW;
	}
	(*_data) = _vecPtr->varr[_index];
	return ERR_SUCCESS;
}


int VectorPrint(vectorp _vecPtr)
{
	int i = 0;
	if(!_vecPtr || !_vecPtr->varr ||  _vecPtr->magicNum != MAGIC_NUM)
	{
		return i;
	}
	printf("size:%lu blockSize:%lu element num:%ld\n" ,_vecPtr->size,_vecPtr->blockSize,_vecPtr->elementNum);
	for(i=0;i<_vecPtr->elementNum;i++)
	{
		printf("[%d]",_vecPtr->varr[i+1]);
		if(i==20)
		{
			printf("\n");
		}
	}
	printf("\n");
	return i;
}

void PrintERRCODE(ERRCODE _err)
{
	switch(_err)
	{
		case ERR_SUCCESS: 		printf("ERR_SUCCESS\n"); 	break;
		case ERR_ILLEGAL_INPUT: 	printf("ERR_ILLEGAL_INPUT\n");  break;
		case ERR_UNDERFLOW: 		printf("ERR_UNDERFLOW\n"); 	break;
		case ERR_OVERFLOW: 		printf("ERR_OVERFLOW\n"); 	break;
		case ERR_MEM_ALLOC: 		printf("ERR_MEM_ALLOC\n"); 	break;
		case ERR_INDEX:			printf("ERR_INDEX\n"); 		break;
		case ERR_FULL:			printf("ERR_FULL\n"); 		break;
		case ERR_EMPTY:			printf("ERR_EMPTY\n"); 		break;
		case ERR_EXISTS: 		printf("ERR_EXISTS\n"); 	break;
	}
}




