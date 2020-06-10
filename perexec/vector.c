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

static void SetVector(vectorp _vecp, void** _arrPtr, size_t _initialSize , size_t _blockSize );
static ERRCODE VectorResize(vectorp _vecPtr);

/*---------------------------------API function-------------------------------------*/

vectorp VectorCreate(size_t _initialSize,size_t _blockSize)
{
	vectorp vec = NULL;
	void** arrPtr = NULL;

	if(_initialSize == 0 && _blockSize==0 )
	{
		return vec;

	}
	

	vec = (vectorp)malloc(sizeof(vector));
	if(!vec)
	{
		return vec;
	}
	
	arrPtr=(void**)malloc(_initialSize*sizeof(void*));
	if(!arrPtr)
	{
		free(vec);
		return NULL;
	}	
	SetVector(vec,arrPtr,_initialSize,_blockSize);
	
	return vec;
	
}


void VectorDestroy(vectorp _vecPtr,FreeFunction _desElementF)
{
	size_t i;
	if(!IS_VALID(_vecPtr))
	{
		return;
	}
	_vecPtr->m_magicNum = NOT_MAGIC_NUM;
	if(_vecPtr->m_varr)
	{
		if(_desElementF)
		{
			for(i=0;i<_vecPtr->m_elementNum;i++)
			{
				_desElementF(_vecPtr->m_varr[i]);
			}
			
		}
		free(_vecPtr->m_varr);
	}
	free(_vecPtr);
}


ERRCODE VectorAddTail(vectorp _vecPtr ,void* _element)
{
	ERRCODE result = ERR_ILLEGAL_INPUT;
	if(!IS_VALID(_vecPtr) || !_element)
	{
		return result;
	}
	result = VectorResize(_vecPtr);
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
	if(_vecPtr->m_elementNum==0)
	{
		return ERR_EMPTY;
	}

	*_element = _vecPtr->m_varr[_vecPtr->m_elementNum-1];	
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
	if(_index>_vecPtr->m_elementNum-1)	
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
	if(_index>_vecp->m_elementNum-1)	
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

void VectorPrint(const vectorp _vecPtr ,ActionFunction _printF)
{
	if(IS_VALID(_vecPtr))
	{
		if(_printF)
		{
			Vector_ForEach(_vecPtr,_printF,NULL);
		}
	}
}


size_t Vector_ForEach(const vector* _vecp,ActionFunction _act, void* _context)
{
	size_t i;
	if(IS_VALID(_vecp) && _act)
	{
		for(i=0;i<_vecp->m_elementNum && (*_act)(_vecp->m_varr[i],_context) ;i++);
	}
	return i;
}

/*---------------------------------static function -------------------------------------*/

static void SetVector(vectorp _vecp, void** _arrPtr, size_t _initialSize , size_t _blockSize)
{
	_vecp->m_varr       = _arrPtr;
	_vecp->m_blockSize  = _blockSize;
	_vecp->m_size	    = _initialSize; 
	_vecp->m_elementNum =  0; 
	_vecp->m_initSize   = _initialSize;
        _vecp->m_magicNum   = MAGIC_NUM;
}

static ERRCODE VectorResize(vectorp _vecPtr)
{
	void** temp_p =NULL;
	size_t newSize;
	if(_vecPtr->m_elementNum ==_vecPtr->m_size)
	{
		newSize = _vecPtr->m_size + _vecPtr->m_blockSize;
		if(newSize <=_vecPtr->m_size)
		{
			return ERR_FULL;
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
	temp_p = (void**)realloc(_vecPtr->m_varr,newSize*sizeof(void*));
	if(temp_p)
	{
		_vecPtr->m_size = newSize;
		_vecPtr->m_varr = temp_p;
		return ERR_SUCCESS;
	}
	return ERR_MEM_ALLOC;
		
}

