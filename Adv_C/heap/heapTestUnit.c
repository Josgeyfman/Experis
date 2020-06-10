#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "heap.h"
#include "vector.h"
#define HUGE_LEN 30

int IsValidHeap(Heap* _heap);

typedef enum{
		SUCCESS,
		FAILED
} Result;

int Smaller(const void* _a,const void* _b)
{
	const int* a = (int*)_a;
	const int* b = (int*)_b;
	return (*a < *b);
}

int PrintVal(const void* _element ,void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
	return *el;
}

int AssertVal(const void* _element ,void* _context)
{
	int* element = (int*)_element;
	int* index = (int*)_context;
	assert(*element==*index);
	return 1;
}

void PrintResult(Result _res ,char _testName[] )
{
	printf("%s ",_testName);	
	switch(_res)
	{
		case SUCCESS:   printf("SUCCESS\n"); break;
		case FAILED: 	printf("FAILED\n"); break;
	}

}

void HeapBuild_Valid()
{
	Result res;
	heap* heapPtr = NULL; 
	int arr[3] ={3,2,1};
	vector* vec = VectorCreate(3,0);
	
	VectorAddTail(vec,&arr[0]);
	VectorAddTail(vec,&arr[1]);
	VectorAddTail(vec,&arr[2]);
	heapPtr = Heap_Build(vec,Smaller);
	if(heapPtr)
	{
		res = SUCCESS;
		Heap_Destroy(&heapPtr);
		VectorDestroy(vec,NULL);
	}
	else
	{
		res = FAILED;
		VectorDestroy(vec,NULL);
	}
	PrintResult(res , "HeapBuild_Valid");
}

void HeapBuild_Null()
{
	
	heap* heapPtr = Heap_Build(NULL,&Smaller);
	Result res; 
	if(!heapPtr)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HeapBuild_Null");
}

void HeapBuild_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,&Smaller);
	Result res; 
	if(heapPtr)
	{
		res = SUCCESS;
		Heap_Destroy(&heapPtr);
		VectorDestroy(vec,NULL);
	}
	else
	{
		res = FAILED;
		VectorDestroy(vec,NULL);
	}
	PrintResult(res , "HeapBuild_Empty");
}

void HeapDestroy_Vaild()
{
	
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,&Smaller);
	Result res = SUCCESS;
	
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapDestroy_Vaild");
}

void HeapDestroy_Null()
{
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	Heap_Destroy(&heapPtr);
	PrintResult(res , "HeapDestroy_Null");
}

void HeapDestroy_DuobleDestroy()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,&Smaller);
	Result res = SUCCESS;
	Heap_Destroy(&heapPtr);
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapDestroy_DuobleDestroy");
}

void HeapDestroy_HugeDestroy()
{
	int i,arr[HUGE_LEN];
	vector* vec = VectorCreate(HUGE_LEN,3);
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] =rand()%HUGE_LEN;	
		VectorAddTail(vec,&arr[i]);
	}
	heapPtr = Heap_Build(vec,Smaller);
	/*Heap_ForEach(heapPtr,PrintVal,NULL);
	printf("\nis valid? %d\n",IsValidHeap(heapPtr));*/
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "\nHeapDestroy_HugeDestroy");
}




void HeapInsert_Vaild()
{
	Result res= SUCCESS;
	int arr[3] ={3,2,1};
	int b = 6;
	heap* heapPtr= NULL;
	vector* vec = VectorCreate(3,1);
	VectorAddTail(vec,&arr[0]);
	VectorAddTail(vec,&arr[1]);
	VectorAddTail(vec,&arr[2]);
	heapPtr = Heap_Build(vec,Smaller);
	if(HEAP_SUCCESS==Heap_Insert(heapPtr,&b))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	/*Heap_ForEach(heapPtr,PrintVal,NULL);*/
	/*Heap_ForEach(heapPtr,PrintVal,NULL);*/
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapInsert_Vaild");
}

void HeapInsert_Null()
{
	heap* heapPtr = NULL;
	Result res;
	int b = rand();
	if(HEAP_SUCCESS!=Heap_Insert(heapPtr,&b))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HeapInsert_Null");
}

void HeapInsert_Empty()
{
	Result res;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	int b = rand();
	if(HEAP_SUCCESS==Heap_Insert(heapPtr,&b))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapInsert_Empty");
}

void HeapInsert_DoubleInsert()
{
	Result res;
	int a = 7,b=8;
	int* peek;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	
	if(HEAP_SUCCESS!=Heap_Insert(heapPtr,&a))
	{
		res = FAILED;
	}
	else if(HEAP_SUCCESS!=Heap_Insert(heapPtr,&b))
	{
		res = FAILED;
	}
	peek = (int*)Heap_Peek(heapPtr);
	if(*peek!=7)
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapInsert_DoubleInsert");
}

void HeapInsert_HugeInsert()
{
	int i,arr[HUGE_LEN];
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	heapPtr = Heap_Build(vec,Smaller);
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] =rand()%HUGE_LEN;	
		if(Heap_Insert(heapPtr,&arr[i])!=HEAP_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "HeapInsert_HugeInsert");
}


void Heap_Peek_Vaild()
{
	Result res;
	int *data =NULL,a=7,b=53,c=-17;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	VectorAddTail(vec,&a);
	VectorAddTail(vec,&b);
	VectorAddTail(vec,&c);
	heapPtr = Heap_Build(vec,Smaller);
	/*Heap_ForEach(heapPtr,PrintVal,NULL);*/
	data = (int*)Heap_Peek(heapPtr);
	if(-17==*data)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Peek_Vaild");
}


void Heap_Peek_Empty()
{
	Result res;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	if(NULL==Heap_Peek(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res,"Heap_Peek_Empty");
}


void Heap_Peek_Null()
{
	Result res;
	if(NULL==Heap_Peek(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res,"Heap_Peek_Null");
}

void Heap_Peek_Huge()
{
	int i,arr[HUGE_LEN];
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		VectorAddTail(vec,&arr[i]);
	}
	heapPtr = Heap_Build(vec,Smaller);
	if(0==*(int*)Heap_Peek(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Peek_Huge");
}

void Heap_Extract_Vaild()
{
	Result res;
	int a=7,b=53;/*,c=-17;*/
	int* min;
	int* exmin;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	VectorAddTail(vec,&a);
	VectorAddTail(vec,&b);
	/*VectorAddTail(vec,&c);*/
	heapPtr = Heap_Build(vec,Smaller);
	/*Heap_ForEach(heapPtr,PrintVal,NULL);*/
	exmin = Heap_Extract(heapPtr);
	min = (int*)Heap_Peek(heapPtr);
	if(7==*exmin && 53 == *min)
	{
		res = SUCCESS;
	}
	exmin= Heap_Extract(heapPtr);
	min = (int*)Heap_Peek(heapPtr);
	if(NULL==min && 53 == *exmin)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res ,"Heap_Extract_Vaild");
}

void Heap_Extract_Empty()
{
	Result res;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	if(NULL==Heap_Extract(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Extract_Empty");
}


void Heap_Extract_Null()
{
	Result res;
	if(NULL==Heap_Extract(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "Heap_Extract_Null");
}

void Heap_Extract_Huge()
{
	int i,arr[HUGE_LEN];
	int* min;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		VectorAddTail(vec,&arr[i]);
	}
	heapPtr = Heap_Build(vec,Smaller);
	min = (int*)Heap_Extract(heapPtr);
	if(0==*min && Heap_Size(heapPtr)==HUGE_LEN-1)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Extract_Huge");
}


void Heap_Size_Vaild()
{
	Result res;
	int a = 7 ,b=53, c=17;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	Heap_Insert(heapPtr,&a);
	Heap_Insert(heapPtr,&b);
	Heap_Insert(heapPtr,&c);
	if(3==Heap_Size(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Size_Vaild");
}

void Heap_Size_Empty()
{
	Result res;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	if(0==Heap_Size(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Size_Empty");
}

void Heap_Size_Null()
{
	Result res;
	if(0==Heap_Size(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "Heap_Size_Null");
}

void Heap_Size_Huge()
{
	int i,arr[HUGE_LEN];
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		VectorAddTail(vec,&arr[i]);
	}
	heapPtr = Heap_Build(vec,Smaller);
	if(HUGE_LEN==Heap_Size(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_Size_Huge");
}

void Heap_ForEach_Null()
{
	Result res = SUCCESS;
	Heap_ForEach(NULL,PrintVal,NULL);
	PrintResult(res , "Heap_ForEach_Null");
}

void Heap_ForEach_Null_Func()
{
	Result res = SUCCESS;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	Heap_ForEach(heapPtr,NULL,NULL);
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_ForEach_Null_Func");
}

void Heap_ForEach_Empty()
{
	Result res = SUCCESS;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = Heap_Build(vec,Smaller);
	Heap_ForEach(heapPtr,PrintVal,NULL);
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_ForEach_Empty");
}

void Heap_ForEach_Valid_Print()
{
	int i,arr[HUGE_LEN];
	vector* vec = VectorCreate(0,3);
	heap* heapPtr;
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = rand()%HUGE_LEN;
		VectorAddTail(vec,&arr[i]);
	}
	heapPtr = Heap_Build(vec,Smaller);
	Heap_ForEach(heapPtr,PrintVal,NULL);
	printf("heap valid? %d\n",IsValidHeap(heapPtr));
	Heap_Destroy(&heapPtr);
	VectorDestroy(vec,NULL);
	PrintResult(res , "Heap_ForEach_Valid_Print");
}

int main()
{
	printf("\nCreate & destroy tests:\n");
	/*destroy & create tests*/
	HeapBuild_Valid();
	HeapBuild_Null();
	HeapBuild_Empty();
	HeapDestroy_HugeDestroy();
	HeapDestroy_DuobleDestroy();
	HeapDestroy_Null();
	HeapDestroy_Vaild();
	
	/*insert tests*/
	printf("\nInsert tests:\n");
	HeapInsert_Vaild();
	HeapInsert_Empty();
	HeapInsert_Null();
	HeapInsert_DoubleInsert();
	HeapInsert_HugeInsert();
	
	/*Heap Max tests*/
	printf("\nHeap Max tests:\n");
	Heap_Peek_Vaild();
	Heap_Peek_Empty();
 	Heap_Peek_Null();
	Heap_Peek_Huge(); 
	
	/*Extract Max tests*/
	printf("\nExtract Max tests:\n");
	Heap_Extract_Vaild();
	Heap_Extract_Empty();
	Heap_Extract_Null();
	Heap_Extract_Huge();
	
	/*HeapItemsNum tests*/
	printf("\nHeap Items Num tests:\n");
	Heap_Size_Vaild();
	Heap_Size_Empty();
	Heap_Size_Null();
	Heap_Size_Huge();

	/*for each tests*/
	printf("\nFor each tests:\n");
	Heap_ForEach_Empty();
	Heap_ForEach_Null();
	Heap_ForEach_Valid_Print();
	Heap_ForEach_Null_Func();

	return 0;
	
}










