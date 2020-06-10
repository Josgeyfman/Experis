#include<stdio.h>
#include "vector.h"

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
		VectorDestroy(vec);
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
		VectorDestroy(vec);
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
	vectorp vec = VectorCreate(rand()/10000,rand()/10000);
	if(vec)
	{
		res = SUCCESS;
		VectorDestroy(vec);
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
	vectorp vec = VectorCreate(rand()/10000,rand()/10000);
	if(vec)
	{
		res = SUCCESS;
		VectorDestroy(vec);
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
	VectorDestroy(vec);
	PrintResult(res ,"TestVectorDoubleDestroy");
}

void TestVectorDoubleDestroy()
{
	Result res = SUCCESS;	
	vectorp vec = VectorCreate(10,5);
	VectorDestroy(vec);
	VectorDestroy(vec);
	PrintResult(res ,"TestVectorDoubleDestroy");
}

void TestVectorDestroyNull()
{
	Result res;	
	vectorp vec = NULL;
	VectorDestroy(vec);
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

void TestVectorAddTail()
{
	#define BLOCK 5
	#define SIZE 10
	int arr[SIZE+(2*BLOCK)],i,data;
	Result res = SUCCESS;
	vectorp vec = VectorCreate(SIZE,BLOCK);

	for(i=0; i < SIZE+(2*BLOCK)-1 ;i++)
	{
		arr[i]=rand();
		VectorAddTail(vec,arr[i]);
	}
	
	for(i=0; i < SIZE+(2*BLOCK)-1; i++)
	{
		VectorGet(vec,i+1,&data);
		if(arr[i] != data)
		{
			printf("%d!=%d i=%d\n",arr[i],data,i);
			res = FAILED;
		}
		
	}	
	VectorDestroy(vec);
	PrintResult(res ,"TestVectorAddTail");
}


int main()
{
	/*create tests*/
	TestVectorCreateSize0Block0();
	TestVectorCreateSizeNBlockN();
	TestVectorCreateSize0BlockN();	
	TestVectorCreateSizeNBlock0();
	/*Destroy tests*/
	TestVectorDestroy();
	TestVectorDoubleDestroy();
	TestVectorDestroyNull();
	
	/*Add Tail tests*/
	TestVectorAddTail();

	return 0;
	
}










