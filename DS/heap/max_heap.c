#include<stdio.h> 	
#include<stdlib.h>	/*allocation*/
#include<math.h>	/*for pretty print*/
#include"max_heap.h"
#define MAGIC_NUM 0xfacabeef
#define IS_VALID(t) (t && t->magicNum==MAGIC_NUM)
#define MAX_INDEX 1
#define LEFT_SON(t) (2*t)
#define RIGHT_SON(t) (2*t + 1)
#define PARENT(t) (t/2)

/*------------------------structure---------------------------------------*/

struct Heap
{
	vector* vec;
	size_t heapSize;
	size_t magicNum;
};

/*------------------------static function signatures----------------------*/

static void HeapifyUp(Heap* _heap,int _index);
static void HeapifyDown(Heap* _heap,int _index);
static void ReplacePosition(vector* _vec,int _pos1,int _pos2,int _val1,int _val2);
static void PrettyPrint(Heap* _heap); /* for debug */
static void PrintIndt(int _indt);
static int PowerOfTwo(int _t);

/*------------------------API functions ----------------------------------*/

Heap* HeapBuild(vector* _vec)
{
	int i,size;
	heap* heapPtr;
	if(!_vec)
	{
		return NULL;
	}
	size = VectorNumOfElements(_vec);	
	heapPtr = (heap*)malloc(sizeof(heap));
	if(!heapPtr)
	{
		return NULL;
	}
	heapPtr->heapSize=size;
	heapPtr->vec=_vec;
	heapPtr->magicNum = MAGIC_NUM;
	for(i=size/2 ; i>0; i--)
	{
 		HeapifyDown(heapPtr,i);
	}
	return heapPtr;
}


void HeapDestroy(Heap* _heap)
{
	if(!IS_VALID(_heap))
	{
		return;
	}
	_heap->magicNum = 0;
	free(_heap);
}


ERRCODE HeapInsert(Heap* _heap, int _data)
{
	ERRCODE res;
	if(!IS_VALID(_heap))
	{
		return ERR_ILLEGAL_INPUT;
	}
	res = VectorAddTail(_heap->vec,_data);
	if(ERR_SUCCESS==res)
	{
		_heap->heapSize++;
		HeapifyUp(_heap,_heap->heapSize);
	}
	return res;
}

ERRCODE HeapMax(Heap* _heap, int* _data)
{
	if(!IS_VALID(_heap) || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_heap->heapSize==0)
	{
		return ERR_EMPTY;
	}
	return  VectorGet(_heap->vec,MAX_INDEX,_data);
}

ERRCODE HeapExtractMax(Heap* _heap, int* _data)
{
	int last,max;
	if(!IS_VALID(_heap) || !_data)
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(_heap->heapSize==0)
	{
		return ERR_EMPTY;
	}
	VectorGet(_heap->vec,MAX_INDEX,&max);
	VectorGet(_heap->vec,_heap->heapSize,&last);
	VectorSet(_heap->vec,MAX_INDEX,last);
	VectorSet(_heap->vec,_heap->heapSize,max);
	VectorRemoveTail(_heap->vec,_data);
	_heap->heapSize--;
	HeapifyDown(_heap,MAX_INDEX);
	return ERR_SUCCESS;

}

size_t HeapItemsNum(Heap* _heap)
{
	if(IS_VALID(_heap))
	{
		return _heap->heapSize;
	}
	return 0;
}

void HeapPrint(Heap* _heap)
{
	if(IS_VALID(_heap))
	{
		VectorPrint(_heap->vec);
		if(DEBUG) PrettyPrint(_heap);
	}
}

/*------------------------static functions --------------------------*/
static int PowerOfTwo(int _t)
{
	return (_t!=0 && ceil(log(_t)/log(2))==floor(log(_t)/log(2)));
}

static void PrintIndt(int _indt)
{
	int i=0;
	while(i<_indt)
	{
		printf(" ");
		i++;
	}
}

static void PrettyPrint(Heap* _heap)
{
	int data,i,level=_heap->heapSize/2,indt  ;
	indt = level;
	for(i=1;i<=_heap->heapSize;i++)
	{
		if(PowerOfTwo(i))
		{
			printf("\n");
			PrintIndt(indt);
			level--;
			indt-=2;
		}
		VectorGet(_heap->vec,i,&data);
		printf("%d",data);
		PrintIndt(level);
	}
	printf("\n");

}

static void ReplacePosition(vector* _vec,int _pos1,int _pos2,int _val1,int _val2)
{
	VectorSet(_vec,_pos1,_val2);
	VectorSet(_vec,_pos2,_val1);
}

static void HeapifyDown(Heap* _heap,int _index)
{
	int left,right,curr;
	ERRCODE resleft ,resRight,resCurr;
	resCurr = VectorGet(_heap->vec,_index,&curr);
	resleft = VectorGet(_heap->vec,LEFT_SON(_index),&left);
	resRight = VectorGet(_heap->vec,RIGHT_SON(_index),&right);
	if(resRight && !resCurr && !resleft)	/* if index has only left son*/
	{
		if(left > curr)
		{
			/*if(DEBUG) printf("left:%d>%d:curr\n",left,curr);*/
			ReplacePosition(_heap->vec,_index,LEFT_SON(_index),curr,left);
			return;
		}
	}
	else if(!resRight && !resCurr && !resleft) /* if index has 2 children*/
	{	
		if(left > curr && left> right)	
		{
			/*if(DEBUG) printf("left:%d>%d:curr,left:%d>%d:right\n",left,curr,left,right);*/
			ReplacePosition(_heap->vec,_index,LEFT_SON(_index),curr,left);
			HeapifyDown(_heap,LEFT_SON(_index));
		}
		else if(right > curr && right > left)	
		{
			/*if(DEBUG) printf("right:%d>%d:curr,right:%d>%d:left\n",right,curr,right,left);*/
			ReplacePosition(_heap->vec,_index,RIGHT_SON(_index),curr,right);
			HeapifyDown(_heap,RIGHT_SON(_index));
		}
	}
}

static void HeapifyUp(Heap* _heap,int _index)
{
	int parent,curr;
	ERRCODE resParent;
	resParent = VectorGet(_heap->vec,PARENT(_index),&parent);
	/*if(DEBUG) printf("curr ind:%d ,parent ind:%d\n",_index,_index/2);*/
	if(!resParent) /* if index has a parent*/
	{
		VectorGet(_heap->vec,_index,&curr);
		if(curr > parent)	
		{
			/*if(DEBUG) printf("curr:%d>%d:parent\n",curr,parent);*/
			ReplacePosition(_heap->vec,_index,PARENT(_index),curr,parent);
			HeapifyUp(_heap,PARENT(_index));
		}
	}
}




