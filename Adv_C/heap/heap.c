#include<stdio.h> 	
#include<stdlib.h>	/*allocation*/
#include"heap.h"
#define MAGIC_NUM 0xfacabeef
#define NOT_MAGIC_NUM 0xfffabeef
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)
#define TOP_INDEX 0
#define LEFT_SON(t) (2*t+1)
#define RIGHT_SON(t) (2*t+2)
#define PARENT(t) ((t-1)/2)

/*------------------------structure---------------------------------------*/

struct Heap
{
	size_t m_magicNum;
	vector* m_vec;
	LessThanComparator m_cmpF;
	size_t m_heapSize;
};

typedef struct Contex
{
	ActionFunction userAct;
	void*  userCon;
	size_t runTimes;
} context;

/*------------------------static function signatures----------------------*/

static void HeapifyUp(Heap* _heap,int _index);
static void HeapifyDown(Heap* _heap,size_t _index);
static void ReplacePosition(vector* _vec,int _pos1,int _pos2,void* _val1,void* _val2);
/*------------------------API functions ----------------------------------*/


Heap* Heap_Build(vector* _vector, LessThanComparator _pfLess)
{
	int i,size;
	Heap* heapPtr;
	if(!_vector || !_pfLess)
	{
		return NULL;
	}
	size = VectorNumOfElements(_vector);	
	heapPtr = (Heap*)malloc(sizeof(Heap));
	if(!heapPtr)
	{
		return NULL;
	}
	heapPtr->m_heapSize=size;
	heapPtr->m_vec=_vector;
	heapPtr->m_cmpF=_pfLess;
	heapPtr->m_magicNum = MAGIC_NUM;
	if(size==0)
	{
		return heapPtr;
	}
	for(i=size/2; i>=0; i--)
	{
 		HeapifyDown(heapPtr,i);
	}
	return heapPtr;
}


vector* Heap_Destroy(Heap** _heap)
{
	vector* vec;
	if(!_heap || !IS_VALID((*_heap)))
	{
		return NULL;
	}
	vec = (*_heap)->m_vec;
	(*_heap)->m_magicNum = NOT_MAGIC_NUM;
	free((*_heap));
	*_heap = NULL;
	return vec;
}

Heap_Result Heap_Insert(Heap* _heap, void* _element)
{
	ERRCODE res;
	if(!IS_VALID(_heap))
	{
		return HEAP_NOT_INITIALIZED;
	}	
	res = VectorAddTail(_heap->m_vec,_element);
	if(ERR_MEM_ALLOC==res)
	{
		return HEAP_REALLOCATION_FAILED;
	}
	if(ERR_FULL==res)
	{
		return HEAP_REALLOCATION_FAILED;
	}
	HeapifyUp(_heap,_heap->m_heapSize);
	_heap->m_heapSize++;
	return HEAP_SUCCESS;
}

const void* Heap_Peek(const Heap* _heap)
{
	void* retElement;
	if(!IS_VALID(_heap) || _heap->m_heapSize==0)
	{
		return NULL;
	}
	VectorGet(_heap->m_vec,TOP_INDEX,&retElement);
	return  retElement;
}

void* Heap_Extract(Heap* _heap)
{
	void* last;
	void* max;
	if(!IS_VALID(_heap) || _heap->m_heapSize==0)
	{
		return NULL;
	}
	VectorGet(_heap->m_vec,TOP_INDEX,&max);
	VectorGet(_heap->m_vec,_heap->m_heapSize-1,&last);
	ReplacePosition(_heap->m_vec,TOP_INDEX,_heap->m_heapSize-1,max,last);
	VectorRemoveTail(_heap->m_vec,&max);
	_heap->m_heapSize--;
	HeapifyDown(_heap,TOP_INDEX);
	return max;
}

size_t Heap_Size(const Heap* _heap)
{
	if(!IS_VALID(_heap))
	{
		return 0;
	}
	return _heap->m_heapSize;
}


size_t Heap_ForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
	size_t retVal;
	context* userCon;
	
	if(!IS_VALID(_heap) || !_act)
	{
		return 0;
	}
	
	userCon = (context*)malloc(sizeof(context));
	if(!userCon)
	{
		return 0;
	}
	userCon->userAct=_act;
	userCon->userCon=_context;
	userCon->runTimes=_heap->m_heapSize;
	retVal = Vector_ForEach(_heap->m_vec,&Heap_ActionElement,userCon);
	free(userCon);
	return retVal;
}

int Heap_ActionElement(const 	void* _element, void* _context)
{
	context* con = (context*) _context;
	if(!_element || !_context)
	{
		return 0;
	}
	con->userAct(_element,con->userCon);
	con->runTimes--;
	return con->runTimes;
}

/*------------------------static functions --------------------------*/
static void ReplacePosition(vector* _vec,int _pos1,int _pos2,void* _val1,void* _val2)
{
	VectorSet(_vec,_pos1,_val2);
	VectorSet(_vec,_pos2,_val1);
}

int PrintVal1(const void* _element ,void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
	return *el;
}

static void HeapifyDown(Heap* _heap,size_t _index)
{
	void* left;
	void* right;
	void* curr;
	ERRCODE resleft = ERR_ILLEGAL_INPUT;
	ERRCODE resRight = ERR_ILLEGAL_INPUT;
	ERRCODE resCurr = ERR_ILLEGAL_INPUT;
	if(_heap->m_heapSize >= _index)
	{
		resCurr = VectorGet(_heap->m_vec,_index,&curr);
	}
	if(_heap->m_heapSize >= LEFT_SON(_index))
	{
		resleft = VectorGet(_heap->m_vec,LEFT_SON(_index),&left);
	}
	if(_heap->m_heapSize >= RIGHT_SON(_index))
	{
		resRight = VectorGet(_heap->m_vec,RIGHT_SON(_index),&right);
	}
	if(resRight && !resCurr && !resleft)	/* if index has only left son*/
	{
		if((*_heap->m_cmpF)(left,curr))
		{
			ReplacePosition(_heap->m_vec,_index,LEFT_SON(_index),curr,left);
		}
		return;
	}
	else if(!resRight && !resCurr && !resleft) /* if index has 2 children*/
	{	
		if((*_heap->m_cmpF)(left,right) && (*_heap->m_cmpF)(left,curr))
		{
			ReplacePosition(_heap->m_vec,_index,LEFT_SON(_index),curr,left);
			HeapifyDown(_heap,LEFT_SON(_index));
		}
		else if((*_heap->m_cmpF)(right,curr))
		{
			
			ReplacePosition(_heap->m_vec,_index,RIGHT_SON(_index),curr,right);
			HeapifyDown(_heap,RIGHT_SON(_index));

		}
	
	}
}

static void HeapifyUp(Heap* _heap,int _index)
{
	void * parent = NULL;
	void* curr = NULL;
	if(PARENT(_index)<TOP_INDEX)
	{
		return;
	}
	VectorGet(_heap->m_vec,PARENT(_index),&parent);
	VectorGet(_heap->m_vec,_index,&curr);
	if((*_heap->m_cmpF)(curr,parent))	
	{
		ReplacePosition(_heap->m_vec,_index,PARENT(_index),curr,parent);
		HeapifyUp(_heap,PARENT(_index));
	}
}


int IsValidHeap(Heap* _heap)
{
	void* left;
	void* right;
	void* curr;
	ERRCODE resleft ,resRight,resCurr;
	int i,size = VectorNumOfElements(_heap->m_vec);
	for(i=0;i<=size/2;i++)
	{
		resCurr = VectorGet(_heap->m_vec,i,&curr);
		resleft = VectorGet(_heap->m_vec,LEFT_SON(i),&left);
		resRight = VectorGet(_heap->m_vec,RIGHT_SON(i),&right);
		if(!resCurr && !resRight && (*(int*)curr > *(int*)right))
		{
			return 0;

		}
		if(!resCurr && !resleft && (*(int*)curr > *(int*)left))
		{
			return 0;

		}
	}
	return 1;
}

