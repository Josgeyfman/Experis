#include<stdbool.h> /*bool*/
#include"vector.h"
#include"vecSort.h"


static void Swap(vector* _vec,size_t _index1 , size_t _index2,void* _val1,void* _val2)
{
	VectorSet(_vec,_index1,_val2);
	VectorSet(_vec,_index2,_val1);
}

static bool BubbleUp(vector* _vec,size_t _size,fcp _compareF)
{
	register int j ,swapped =0;
	void* curr;
	void* next;
	for(j=0;j<_size;j++)		
	{
		VectorGet(_vec,j,&curr);
		VectorGet(_vec,j+1,&next);
		if((*_compareF)(curr,next))
		{
			Swap(_vec,j,j+1,next,curr);
			swapped=1;
		}
		
	
	}
	return swapped;
}

ERRCODE BubbleSort(vector* _vec , fcp _compareF)
{
	register int i,size;
	if(!_vec || !_compareF)
	{
		return ERR_ILLEGAL_INPUT;
	}
	size = VectorNumOfElements(_vec);
	for(i=0;i<size;i++)		
	{
		if(!BubbleUp(_vec,size-i-1, _compareF))
		{
			return ERR_SUCCESS;
		}
	}
	return ERR_SUCCESS;
}
