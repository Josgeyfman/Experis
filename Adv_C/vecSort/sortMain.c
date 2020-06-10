#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include"vector.h"
#include"vecSort.h"
#define LEN 10000

bool Bigger(void* _a,void* _b)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	return (*a>*b);
}

bool Smaller(void* _a,void* _b)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	return (*a<*b);
}

void PrintVal(void* _a)
{
	int* a = (int*)_a;
	printf("%d,",*a);
}

int IsSorted(vector* _vec ,bool (*_f)(void*,void*))
{
	register int i,size = VectorNumOfElements(_vec);
	void* curr;
	void* next ;
	for(i=0;i<size-1;i++)
	{
		VectorGet(_vec,i,&curr);
		VectorGet(_vec,i+1,&next);
		if(_f(curr,next))
		{
			printf("not sorted i:%d i+1:%d\n",i,i+1);
			return 0;
		}
	}
	return 1;
}

int main()
{
	
	register int i;
	int* arr[LEN],barr[LEN];
	bool isSorted=false;
	vectorp vec;
	vec = VectorCreate(LEN,0);
	for(i=0;i<LEN;i++)		
	{
		barr[i]=rand()%(2*LEN);
		arr[i]=&barr[i];
		VectorAddTail(vec,arr[i]);
	}
	BubbleSort(vec,&Bigger);
	isSorted = IsSorted(vec,&Bigger);
	/*VectorPrint(vec,&PrintVal);*/
	printf("\nbigger isSorted? %d\n",isSorted);
	BubbleSort(vec,&Smaller);
	isSorted = IsSorted(vec,&Smaller);
	printf("\nsmaller isSorted? %d\n",isSorted);
	/*VectorPrint(vec,&PrintVal);*/
	printf("\n");
	VectorDestroy(vec,NULL);
	return 0;
}




