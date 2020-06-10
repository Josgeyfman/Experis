#include <stdio.h> 
#include"vector.h"
#define IS_VALID(t) (t && t->m_magicNum == MAGIC_NUM)
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

struct Vector{
	
	size_t m_magicNum;
	void** m_varr;
	size_t m_blockSize;
	size_t m_elementNum;
	size_t m_size;
	size_t m_initSize;  
	
}; 

/*---------------------------------static function signatures-------------------------------------*/

static void SetVector(vectorp _vPtr, void** _arrPtr, size_t _initialSize , size_t _m_blockSize );
static ERRCODE VectorResize(vectorp _vecPtr);
static void RunFuncOnElements(vectorp _vecPtr ,fp _func);

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

	SetVector(vecPtr,arrPtr,_initialSize,_blockSize);
	
	return vecPtr;
	
}


void VectorDestroy(vectorp _vecPtr,fp _desF)
{
	if(!IS_VALID(_vecPtr))
	{
		return;
	}
	_vecPtr->m_magicNum = NOT_MAGIC_NUM;
	if(_desF)
	{
		RunFuncOnElements(_vecPtr,_desF);
	}
	free(_vecPtr->m_varr);
	free(_vecPtr);
}


ERRCODE VectorAddTail(vectorp _vecPtr ,void* _element)
{
	ERRCODE result = ERR_ILLEGAL_INPUT;
	if(!IS_VALID(_vecPtr) || !_element)
	{
		return result;
	}
	VectorResize(_vecPtr);
	if(result==ERR_SUCCESS)
	{
		_vecPtr->m_varr[(_vecPtr->m_elementNum)++] = _element;
	}
	return result;
		
}

ERRCODE VectorRemoveTail(vectorp _vecPtr ,void** _element)
{
	if(!IS_VALID(_vecPtr) || !_element)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_vecPtr->m_elementNum<=0)
	{
		return ERR_UNDERFLOW;
	}

	*_element = _vecPtr->m_varr[_vecPtr->m_elementNum];	
	 _vecPtr->m_elementNum--;	

	VectorResize(_vecPtr);

	return ERR_SUCCESS;	
}

ERRCODE VectorSet(vectorp _vecPtr ,size_t _index ,void* _element)
{
	if(!IS_VALID(_vecPtr) || !_element)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecPtr->m_elementNum)	
	{
		return ERR_WRONG_INDEX;
	}
	_vecPtr->m_varr[_index]=_element;
	return ERR_SUCCESS;
}

ERRCODE VectorGet(const vectorp _vecp ,size_t _index ,void** _element)
{
	if(!IS_VALID(_vecp) || !_element)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_index>_vecp->m_elementNum)	
	{	
		return ERR_WRONG_INDEX;
	}
	*_element = _vecp->m_varr[_index];
	return ERR_SUCCESS;
}

size_t VectorNumOfElements(const vectorp _vec)
{
	if(!IS_VALID(_vec))	
	{
		return 0;
	}
	return _vec->m_elementNum;
}

void VectorPrint(const vectorp _vecPtr ,fp _printF)
{
	if(IS_VALID(_vecPtr))
	{
		if(_printF)
		{
			RunFuncOnElements(_vecPtr,_printF);
		}
	}
}

/*---------------------------------static function -------------------------------------*/

static void RunFuncOnElements(vectorp _vecPtr ,fp _func)
{
	size_t i;
	{
		for(i=0;i<_vecPtr->m_elementNum;i++)
		{
			(*_func)(_vecPtr->m_varr[i]);
		}
	}
}



static void SetVector(vectorp _vPtr, void** _arrPtr, size_t _initialSize , size_t _m_blockSize)
{
	_vPtr->m_varr       = _arrPtr;
	_vPtr->m_blockSize  = _m_blockSize;
	_vPtr->m_size	    = _initialSize; 
	_vPtr->m_elementNum =  0; 
	_vPtr->m_initSize   = _initialSize;
        _vPtr->m_magicNum   = MAGIC_NUM;
}

static ERRCODE VectorResize(vectorp _vecPtr)
{
	void** temp_p = _vecPtr->m_varr;
	size_t newSize;
	if(_vecPtr->m_elementNum ==_vecPtr->m_size)
	{
		newSize = _vecPtr->m_size + _vecPtr->m_blockSize;
		if(newSize <=_vecPtr->m_size)
		{
			return ERR_SUCCESS;
		}
		
	}
	else if(_vecPtr->m_elementNum ==_vecPtr->m_size-(2*_vecPtr->m_blockSize))
	{
		newSize =  _vecPtr->m_size - _vecPtr->m_blockSize;
		if(newSize <_vecPtr->m_initSize)
		{
			return ERR_SUCCESS;
		}
		
	}
	else
	{
		return ERR_SUCCESS;
	}
	temp_p = (void**)realloc((_vecPtr->m_varr),newSize*sizeof(void*));
	if(temp_p)
	{
		_vecPtr->m_size = newSize;
		_vecPtr->m_varr = temp_p;
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
		case ERR_WRONG_INDEX: 		printf("ERR_WRONG_INDEX\n"); 	break;
	}
}




