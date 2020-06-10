#include<stdio.h>
#include "vector.h"
#include "myStruct.h"
#define LEN 500
#define HUGE_LEN 50000

typedef void (*funcp)(void*);

typedef enum{
		SUCCESS,
		FAILED
} Result;

void PrintResult(Result _res ,char _testName[])
{
	printf("%s ",_testName);	
	switch(_res)
	{
		case SUCCESS:   printf("SUCCESS\n"); break;
		case FAILED: 	printf("FAILED\n"); break;
	}

}

void TestVectorCreateSizeValid()
{
	Result res;
	vectorp vec;	
	mystruct* my = CreateMyStruct();
	vec = VectorCreate(1,1);
	VectorAddTail(vec,my);
	if(vec && VectorNumOfElements(vec)==1)
	{
		res = SUCCESS;
		VectorDestroy(vec,FreeMyStruct);
	}
	else
	{
		res = FAILED;
		
	}
	PrintResult(res , "TestVectorCreateSizeValid");
}

void TestVectorCreateSize0Block0()
{
	Result res;	
	vectorp vec= VectorCreate(0,0);
	if(!vec)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		VectorDestroy(vec,NULL);
	}
	PrintResult(res , "TestVectorCreateSize0Block0");
}

void TestVectorCreateSizeNBlockN()
{
	Result res;	
	vectorp vec= VectorCreate(rand()/10000,rand()/10000);
	if(vec)
	{
		res = SUCCESS;
		VectorDestroy(vec,NULL);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res ,"TestVectorCreateSizeNBlockN");
}

void TestVectorCreateSize0BlockN()
{
	Result res;	
	vectorp vec = VectorCreate(0,rand()/10000);
	if(vec)
	{
		res = SUCCESS;
		VectorDestroy(vec,NULL);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res ,"TestVectorCreateSize0BlockN");
}

void TestVectorCreateSizeNBlock0()
{
	Result res;	
	vectorp vec = VectorCreate(rand()/10000,0);
	if(vec)
	{
		res = SUCCESS;
		VectorDestroy(vec,NULL);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res ,"TestVectorCreateSizeNBlock0");
}


void TestVectorDestroy()
{
	Result res = SUCCESS;	
	vectorp vec = VectorCreate(10,5);
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorDestroy");
}

void TestVectorDoubleDestroy()
{
	Result res = SUCCESS;	
	vectorp vec = VectorCreate(10,5);
	VectorDestroy(vec,FreeMyStruct);
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorDoubleDestroy");
}

void TestVectorDestroyNull()
{
	Result res;	
	vectorp vec = NULL;
	VectorDestroy(vec,FreeMyStruct);
	if(!vec)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res ,"TestVectorDestroyNull");
}

void TestVectorAddTail_Premitive_Type()
{
	#define BLOCK 5
	#define SIZE 10
	int i,arr[SIZE+(2*BLOCK)];
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	
	for(i=0; i < SIZE+(2*BLOCK);i++)
	{
		arr[i] = rand();
		VectorAddTail(vec,&arr[i]);
	}
	
	if(VectorNumOfElements(vec)== SIZE+(2*BLOCK))
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorAddTail_Premitive_Type");
}

void TestVectorAddTail_Valid()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys;
	int i;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	
	for(i=0; i < SIZE+(2*BLOCK);i++)
	{
		mys = CreateMyStruct();
		VectorAddTail(vec,mys);
	}
	
	if(VectorNumOfElements(vec)== SIZE+(2*BLOCK))
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	/*VectorPrint(vec,PrintMyStruct);*/
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorAddTail_Valid");
}

void TestVectorAddTail_NULL()
{
	#define BLOCK 5
	#define SIZE 10
	int *b,a=5;
	Result res = SUCCESS;
	vectorp vec = NULL;
	b=&a;
	if(VectorAddTail(vec,b)== ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
		
	}
	/*VectorPrint(vec,PrintMyStruct);*/
	PrintResult(res ,"TestVectorAddTail_NULL");
}

void TestVectorAddTail_NULL_DATA()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys = NULL;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	if(VectorAddTail(vec,mys)== ERR_SUCCESS)
	{
		VectorDestroy(vec,FreeMyStruct);
		res = FAILED;		
	}
	else
	{
		FreeMyStruct(mys);
		VectorDestroy(vec,NULL);
		res = SUCCESS;
	}
	/*VectorPrint(vec,PrintMyStruct);*/
	
	PrintResult(res ,"TestVectorAddTail_NULL_DATA");
}


void TestVectorAddTail_HUGE_LEN()
{
	mystruct* mys;
	int i;
	Result res ;
	vectorp vec = VectorCreate(100,50);
	
	for(i=0; i < HUGE_LEN;i++)
	{
		mys = CreateMyStruct();
		VectorAddTail(vec,mys);
	}
	
	if(VectorNumOfElements(vec)== HUGE_LEN)
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	/*VectorPrint(vec,PrintMyStruct);*/
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorAddTail_HUGE_LEN");
}

void TestVectorRemoveTail_Premitive_Type()
{
	#define BLOCK 5
	#define SIZE 10
	int *b,a=5;
	Result res ;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	VectorAddTail(vec,&a);

	if(VectorRemoveTail(vec,(void**)&b)==ERR_SUCCESS)
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorRemoveTail_Premitive_Type");
}

void TestVectorRemoveTail_Valid()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys;
	vectorp vec;
	Result res;
	mys = CreateMyStruct();
	vec = VectorCreate(SIZE,BLOCK);
	VectorAddTail(vec,mys);
	if(VectorRemoveTail(vec,(void*)&mys)==ERR_SUCCESS)
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	/*VectorPrint(vec,PrintMyStruct);*/
	VectorDestroy(vec,FreeMyStruct);
	FreeMyStruct(mys);
	PrintResult(res ,"TestVectorRemoveTail_Valid");
}

void TestVectorRemoveTail_NULL()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys;
	vectorp vec =  NULL;
	Result res;
	mys = CreateMyStruct();
	if(VectorRemoveTail(vec,(void*)&mys)==ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
	}
	FreeMyStruct(mys);
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorRemoveTail_NULL");
}

void TestVectorRemoveTail_NULL_DATA()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys = NULL;
	vectorp vec;
	Result res;
	vec = VectorCreate(SIZE,BLOCK);
	if(VectorRemoveTail(vec,(void*)&mys)==ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
	}
	FreeMyStruct(mys);
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorRemoveTail_NULL_DATA");
}

void TestVectorRemoveTail_HUGE_LEN()
{
	mystruct* mys;
	mystruct* rem;
	int i;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(100,50);
	
	for(i=0; i < HUGE_LEN;i++)
	{
		mys = CreateMyStruct();
		VectorAddTail(vec,mys);
	}
	
	for(i=0; i < HUGE_LEN;i++)
	{
		if(VectorRemoveTail(vec,(void**)&rem)!=ERR_SUCCESS)
		{
			res = FAILED;
		}
		FreeMyStruct(rem);
	}

	/*VectorPrint(vec,PrintMyStruct);*/
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorRemoveTail_HUGE_LEN");
}

void TestVectorGet_Valid()
{
	#define BLOCK 5
	#define SIZE 10
	mystruct* mys;
	mystruct* tmp = NULL;
	int i;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	
	for(i=0; i < SIZE+(2*BLOCK);i++)
	{
		mys = CreateMyStruct();
		VectorAddTail(vec,mys);
		if(VectorGet(vec,i,(void*)&tmp)!=ERR_SUCCESS && tmp==mys)
		{
			res = FAILED;
		}
	}
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorGet_Valid");
}

void TestVectorGet_NULL()
{
	#define BLOCK 5
	#define SIZE 10
	int *b;
	Result res = SUCCESS;
	vectorp vec = NULL;
	if(VectorGet(vec,0,(void*)&b)== ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
		
	}
	PrintResult(res ,"TestVectorGet_NULL");
}

void TestVectorGet_NULL_DATA()
{
	#define BLOCK 5
	#define SIZE 10
	int a =5;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	VectorAddTail(vec,&a);
	if(VectorGet(vec,0,NULL)== ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
		
	}
	PrintResult(res ,"TestVectorGet_NULL_DATA");
	VectorDestroy(vec,NULL);
}


void TestVectorGet_HUGE_LEN()
{
	mystruct* mys;
	mystruct* tmp;
	int i;
	Result res ;
	vectorp vec = VectorCreate(100,50);
	
	for(i=0; i < HUGE_LEN;i++)
	{
		mys = CreateMyStruct();
		VectorAddTail(vec,mys);
		if(VectorGet(vec,i,(void*)&tmp)!=ERR_SUCCESS && tmp==mys)
		{
			res = FAILED;
		}
	}
	if(VectorNumOfElements(vec)== HUGE_LEN)
	{
		res = SUCCESS;		
	}
	else
	{
		res = FAILED;
	}
	VectorDestroy(vec,FreeMyStruct);
	PrintResult(res ,"TestVectorGet_HUGE_LEN");
}

void TestVectorSet_Valid()
{
	#define BLOCK 5
	#define SIZE 10
	
	int i,arr[SIZE];
	int a =0 ;
	int *b;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	for(i=0; i < SIZE;i++)
	{
		arr[i] =rand()%LEN;
		VectorAddTail(vec,&arr[i]);
	
	}
	for(i=0; i < SIZE;i++)
	{
		if(VectorSet(vec,i,&a)!=ERR_SUCCESS)
		{
			res = FAILED;
		}
		if(VectorGet(vec,i,(void*)&b)!=ERR_SUCCESS && b!=0)
		{
			res = FAILED;
		}
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorSet_Valid");
}

void TestVectorSet_NULL()
{
	#define BLOCK 5
	#define SIZE 10
	int b =5;
	Result res = SUCCESS;
	vectorp vec = NULL;
	if(VectorSet(vec,0,&b)== ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
		
	}
	PrintResult(res ,"TestVectorSet_NULL");
}

/*	
	TestVectorSet_HUGE_LEN();*/
void TestVectorSet_NULL_DATA()
{
	#define BLOCK 5
	#define SIZE 10
	int a =5;
	int *b =NULL;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);
	VectorAddTail(vec,&a);
	if(VectorSet(vec,0,(void*)b)== ERR_SUCCESS)
	{
		res = FAILED;		
	}
	else
	{
		res = SUCCESS;
		
	}
	PrintResult(res ,"TestVectorSet_NULL_DATA");
	VectorDestroy(vec,NULL);
}


void TestVectorSet_HUGE_LEN()
{
	int i,arr[HUGE_LEN],barr[HUGE_LEN];
	int a =0 ;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(100,50);
	for(i=0; i < HUGE_LEN;i++)
	{
		arr[i] =rand()%LEN;
		VectorAddTail(vec,&arr[i]);
	
	}
	for(i=0; i < HUGE_LEN;i++)
	{
		if(VectorSet(vec,i,&a)!=ERR_SUCCESS)
		{
			res = FAILED;
		}
		if(VectorGet(vec,i,(void*)&barr[i])!=ERR_SUCCESS && barr[i]!=0)
		{
			res = FAILED;
		}
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorSet_HUGE_LEN");
}

void TestVectorNumOfElements_Valid()
{
	int i,arr[HUGE_LEN];
	Result res = FAILED;
	vectorp vec = VectorCreate(100,50);
	for(i=0; i < HUGE_LEN;i++)
	{
		arr[i] =rand()%LEN;
		VectorAddTail(vec,&arr[i]);
	
	}
	if(VectorNumOfElements(vec)==HUGE_LEN)
	{
		res = SUCCESS;
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorNumOfElements_Valid");
}

void TestVectorNumOfElements_Null()
{
	vector* vec =NULL;
	Result res = FAILED;
	if(VectorNumOfElements(vec)==0)
	{
		res = SUCCESS;
	}
	VectorDestroy(vec,NULL);
	PrintResult(res ,"TestVectorNumOfElements_Null");
}

int main()
{
	/*create tests*/
	printf("create tests\n");
	TestVectorCreateSizeValid();
	TestVectorCreateSize0Block0();
	TestVectorCreateSizeNBlockN();
	TestVectorCreateSize0BlockN();	
	TestVectorCreateSizeNBlock0();

	/*Destroy tests*/
	printf("\nDestroy tests\n");
	TestVectorDestroy();
	TestVectorDoubleDestroy();
	TestVectorDestroyNull();
	
	/*Add Tail tests*/
	printf("\nAdd Tail tests\n");
	TestVectorAddTail_Premitive_Type();
	TestVectorAddTail_Valid();
	TestVectorAddTail_NULL();
	TestVectorAddTail_NULL_DATA();
	TestVectorAddTail_HUGE_LEN();

	/*Remove Tail tests*/
	printf("\nRemove Tail tests\n");
	TestVectorRemoveTail_Premitive_Type();
	TestVectorRemoveTail_Valid();
	TestVectorRemoveTail_NULL();
	TestVectorRemoveTail_NULL_DATA();
	TestVectorRemoveTail_HUGE_LEN();

	/*Get tests*/
	printf("\nGet tests\n");
	TestVectorGet_Valid();
	TestVectorGet_NULL();
	TestVectorGet_NULL_DATA();
	TestVectorGet_HUGE_LEN();	

	/*Set tests*/
	printf("\nSet tests\n");
	TestVectorSet_Valid();
	TestVectorSet_NULL();
	TestVectorSet_NULL_DATA();
	TestVectorSet_HUGE_LEN();

	/*Num of elements tests*/
	printf("\nNum of elements tests\n");
	TestVectorNumOfElements_Valid();
	TestVectorNumOfElements_Null();
	return 0;
	
}










