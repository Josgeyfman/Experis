#include <stdio.h> 
#include"vector.h"
#define IS_VALID(t) (t && t->magicNum == MAGIC_NUM)
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

struct Vector{

	void** varr;
	size_t blockSize;
	size_t elementNum;
	size_t size;
	size_t initSize;  
	size_t magicNum;
}; 

/*---------------------------------static function signatures-------------------------------------*/

static void SetVector(vectorp _vPtr, void** _arrPtr, size_t _initialSize , size_t _blockSize , size_t _elementNum,size_t _initSize);
static ERRCODE VectorResize(vectorp _vecPtr ,size_t _newSize);

/*---------------------------------API function-------------------------------------*/

vectorp VectorCreate(size_t _initialSize,size_t _blockSize)
{
	vectorp vecPtr = NULL;
	void** arrPtr = NULL;
	if(_initialSize == 0 && _blockSize==0 )
	{
		return vecPtr;

	}
	
	vecPtr = (vectorp)malloc(sizeof(vector));
	if(!vecPtr)
	{
		return vecPtr;
	}
	
	arrPtr=(void**)calloc(_initialSize,sizeof(void*));
	if(!arrPtr)
	{
		free(vecPtr);
		return NULL;
	}	

	SetVector(vecPtr,arrPtr,_initialSize,_blockSize,0,_initialSize);
	
	return vecPtr;
	
}


void VectorDestroy(vectorp _vecPtr,void (*_f)(void*))
{
	size_t i;
	if(IS_VALID(_vecPtr))
	{
		if(_vecPtr->varr  && _f)
		{
			for(i=0;i<_vecPtr->elementNum;i++)
			{
				if(_vecPtr->varr[i])
				{
					(*_f)(_vecPtr->varr[i]);
				}
			}
			free(_vecPtr->varr);
		}
		_vecPtr->magicNum = NOT_MAGIC_NUM;
		free(_vecPtr);
	}
}


ERRCODE VectorAddTail(vectorp _vecPtr ,void* _data)
{
	size_t newSize;
	ERRCODE result = ERR_ILLEGAL_INPUT;
	if(!IS_VALID(_vecPtr) || !_data)
	{
		return result;
	}
	if(_vecPtr->elementNum ==_vecPtr->size)
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
	(_vecPtr->varr)[(_vecPtr->elementNum)++] = _data;
	return ERR_SUCCESS;
		
}

ERRCODE VectorRemoveTail(vectorp _vecPtr ,void** _data)
{
	size_t newSize;
	ERRCODE result;
	if(!IS_VALID(_vecPtr) || !*_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_vecPtr->elementNum<0)
	{
		return ERR_UNDERFLOW;
	}
	(*_data) = _vecPtr->varr[(_vecPtr->elementNum)];	
	 _vecPtr->varr[(_vecPtr->elementNum)--] = NULL;	
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

ERRCODE VectorSet(vectorp _vecPtr ,size_t _index ,void* _data)
{
	if(!IS_VALID(_vecPtr) || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecPtr->elementNum)	
	{
		return ERR_OVERFLOW;
	}
	_vecPtr->varr[_index]=_data;
	return ERR_SUCCESS;
}

ERRCODE VectorGet(const vectorp _vecp ,size_t _index ,void** _data)
{
	if(!IS_VALID(_vecp) || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecp->elementNum)	
	{	
		return ERR_OVERFLOW;
	}
	(*_data) = _vecp->varr[_index];
	return ERR_SUCCESS;
}

size_t VectorNumOfElements(const vectorp _vec)
{
	if(!IS_VALID(_vec))	
	{
		return 0;
	}
	return _vec->elementNum;
}

void VectorPrint(vectorp _vecPtr ,void (*_f)(void*))
{
	size_t i;
	if(IS_VALID(_vecPtr))
	{
		if(_vecPtr->varr  && _f)
		{
			for(i=0;i<_vecPtr->elementNum;i++)
			{
				(*_f)(_vecPtr->varr[i]);
			}
		}
	}
}

/*---------------------------------static function -------------------------------------*/

static void SetVector(vectorp _vPtr, void** _arrPtr, size_t _initialSize , size_t _blockSize , size_t _elementNum,size_t _initSize)
{
	_vPtr->varr       = _arrPtr;
	_vPtr->blockSize  = _blockSize;
	_vPtr->size	  = _initialSize; 
	_vPtr->elementNum = _elementNum; 
	_vPtr->initSize   = _initSize;
        _vPtr->magicNum   = MAGIC_NUM;
}

static ERRCODE VectorResize(vectorp _vecPtr ,size_t _newSize)
{
	void** temp_p = _vecPtr->varr;
	if(!_vecPtr || _newSize<1  || _vecPtr->magicNum != MAGIC_NUM)
	{
		return ERR_ILLEGAL_INPUT;	
	}
	temp_p = (void**)realloc((_vecPtr->varr),_newSize*sizeof(void*));
	if(temp_p)
	{
		_vecPtr->size = _newSize;
		_vecPtr->varr = temp_p;
		return ERR_SUCCESS;
	}
	return ERR_MEM_ALLOC;
		
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
		case ERR_NOT_EXISTS: 		printf("ERR_NOT_EXISTS\n"); 	break;
		case ERR_BREAK: 		printf("ERR_BREAK\n"); 		break;
	}
}




