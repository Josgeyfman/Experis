#include<stdio.h>
#include<stdlib.h>
#include "max_heap.h"
#define HUGE_LEN 1000
typedef enum{
		SUCCESS,
		FAILED
} Result;

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
	vector* vec = VectorCreate(3,3);
	heap* heapPtr= NULL;
	VectorAddTail(vec,1);
	VectorAddTail(vec,3);
	VectorAddTail(vec,2);
	heapPtr = HeapBuild(vec);
	if(heapPtr)
	{
		res = SUCCESS;
		HeapDestroy(heapPtr);
		VectorDestroy(vec);
	}
	else
	{
		res = FAILED;
		VectorDestroy(vec);
	}
	PrintResult(res , "HeapBuild_Valid");
}

void HeapBuild_Null()
{
	
	heap* heapPtr = HeapBuild(NULL);
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
	heap* heapPtr = HeapBuild(vec);
	Result res; 
	if(heapPtr)
	{
		res = SUCCESS;
		HeapDestroy(heapPtr);
		VectorDestroy(vec);
	}
	else
	{
		res = FAILED;
		VectorDestroy(vec);
	}
	PrintResult(res , "HeapBuild_Empty");
}

void HeapDestroy_Vaild()
{
	
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS;
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapDestroy_Vaild");
}

void HeapDestroy_Null()
{
	
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	HeapDestroy(heapPtr);
	PrintResult(res , "HeapDestroy_Null");
}

void HeapDestroy_DuobleDestroy()
{
	
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	HeapDestroy(heapPtr);
	HeapDestroy(heapPtr);
	PrintResult(res , "HeapDestroy_DuobleDestroy");
}

void HeapDestroy_HugeDestroy()
{
	int i;
	vector* vec = VectorCreate(HUGE_LEN,3);
	heap* heapPtr = NULL;
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		VectorAddTail(vec,rand());
	}
	heapPtr = HeapBuild(vec);
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapDestroy_HugeDestroy");
}

void HeapInsert_Vaild()
{
	Result res;
	vector* vec = VectorCreate(1,3);
	heap* heapPtr= NULL;
	VectorAddTail(vec,rand());
	heapPtr = HeapBuild(vec);
	if(ERR_SUCCESS==HeapInsert(heapPtr,7))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapInsert_Vaild");
}

void HeapInsert_Null()
{
	heap* heapPtr = NULL;
	Result res;
	if(ERR_SUCCESS!=HeapInsert(heapPtr,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	PrintResult(res , "HeapInsert_Null");
}

void HeapInsert_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	if(ERR_SUCCESS==HeapInsert(heapPtr,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapInsert_Empty");
}

void HeapInsert_DoubleInsert()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	if(ERR_SUCCESS!=HeapInsert(heapPtr,rand()))
	{
		res = FAILED;
	}
	else if(ERR_SUCCESS!=HeapInsert(heapPtr,rand()))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapInsert_DoubleInsert");
}

void HeapInsert_HugeInsert()
{
	int i;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		if(HeapInsert(heapPtr,rand())!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapInsert_HugeInsert");
}


void HeapMax_Vaild()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	int data;
	HeapInsert(heapPtr,7);
	HeapInsert(heapPtr,53);
	HeapInsert(heapPtr,-17);
	HeapMax(heapPtr,&data);
	if(53==data)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapMax_Vaild");
}


void HeapMax_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	int data;
	if(0!=HeapMax(heapPtr,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapMax_Empty");
}


void HeapMax_Null()
{
	Result res;
	int data = rand();
	if(0!=HeapMax(NULL,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HeapMax_Null");
}

void HeapMax_Huge()
{
	int i,data;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		HeapInsert(heapPtr,i);
	}
	HeapMax(heapPtr,&data);
	if(HUGE_LEN-1==data)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapMax_Huge");
}

void HeapExtractMax_Vaild()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	int data;
	HeapInsert(heapPtr,7);
	HeapInsert(heapPtr,53);
	HeapInsert(heapPtr,-17);
	HeapExtractMax(heapPtr,&data);
	if(53==data)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapExtractMax_Vaild");
}

void HeapExtractMax_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	int data;
	if(0!=HeapExtractMax(heapPtr,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapExtractMax_Empty");
}


void HeapExtractMax_Null()
{
	Result res;
	int data = rand();
	if(0!=HeapExtractMax(NULL,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HeapExtractMax_Null");
}

void HeapExtractMax_Huge()
{
	int i,data;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		HeapInsert(heapPtr,i);
	}
	HeapExtractMax(heapPtr,&data);
	if(HUGE_LEN-1==data)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapExtractMax_Huge");
}


void HeapItemsNum_Vaild()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	HeapInsert(heapPtr,7);
	HeapInsert(heapPtr,53);
	HeapInsert(heapPtr,-17);
	if(3==HeapItemsNum(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapItemsNum_Vaild");
}

void HeapItemsNum_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res;
	if(0==HeapItemsNum(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapItemsNum_Empty");
}

void HeapItemsNum_Null()
{
	Result res;
	if(0==HeapItemsNum(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "HeapItemsNum_Null");
}

void HeapItemsNum_Huge()
{
	int i;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		HeapInsert(heapPtr,i);
	}
	if(HUGE_LEN==HeapItemsNum(heapPtr))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapItemsNum_Huge");
}




void HeapPrint_Null()
{
	Result res = SUCCESS;
	HeapPrint(NULL);
	PrintResult(res , "HeapPrint_Null");
}

void HeapPrint_Empty()
{
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	Result res = SUCCESS;
	HeapPrint(heapPtr);
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapPrint_Empty");
}

void HeapPrint_Valid()
{
	int i;
	Result res = SUCCESS;
	vector* vec = VectorCreate(0,3);
	heap* heapPtr = HeapBuild(vec);
	for(i=0;i<8;i++)
	{
		HeapInsert(heapPtr,rand());
	}
	
	HeapPrint(heapPtr);
	HeapDestroy(heapPtr);
	VectorDestroy(vec);
	PrintResult(res , "HeapPrint_Valid");
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
	HeapMax_Huge();
 	HeapMax_Empty();
 	HeapMax_Null();
	HeapMax_Vaild(); 
	
	/*Extract Max tests*/
	printf("\nExtract Max tests:\n");
	HeapExtractMax_Empty();
	HeapExtractMax_Null();
	HeapExtractMax_Vaild();
	HeapExtractMax_Huge();
	
	/*HeapItemsNum tests*/
	printf("\nHeap Items Num tests:\n");
	HeapItemsNum_Empty();
	HeapItemsNum_Null();
	HeapItemsNum_Vaild();
	HeapItemsNum_Huge();

	/*print tests*/
	printf("\nprint tests:\n");
	HeapPrint_Empty();
	HeapPrint_Null();
	HeapPrint_Valid();

	return 0;
	
}










