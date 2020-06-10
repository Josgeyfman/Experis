#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

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


void Test_MyMallocInit_Valid()
{
	Result res =FAILED; 
	void* mem = malloc(1000);
	int* memChunk;
	if(!mem)
	{
		res = FAILED;
		PrintResult(res,"Test_MyMallocInit_Valid");
		return;
	}
	MyMallocInit(mem,1000);
	memChunk = (int*)mem; 
	if(memChunk[0]==1000 && memChunk[1]==988 && memChunk[999]==0)
	{
		res = SUCCESS;
	}
	free(mem);
	PrintResult(res,"Test_MyMallocInit_Valid");
}

void Test_MyMallocInit_Null()
{
	Result res = FAILED; 
	MyMallocInit(NULL,1000);
	res = SUCCESS;
	PrintResult(res,"Test_MyMallocInit_Null");
}

void Test_MyMalloc_Valid()
{
	Result res = FAILED; 
	void* allocated;
	void* mem = malloc(1000);

	if(!mem)
	{
		res = FAILED;
		PrintResult(res,"Test_MyMalloc_Valid");
		return;
	}
	MyMallocInit(mem,1000);
	allocated = MyMalloc(mem,500);
	if(allocated && *((int*)mem+1)==-500)
	{
		res = SUCCESS;
	}
	free(mem);
	PrintResult(res,"Test_MyMalloc_Valid");
}	

void Test_MyMalloc_Null()
{
	Result res = FAILED;
	void* mem = NULL; 
	mem = MyMalloc(mem,500);
	if(!mem)
	{
		res = SUCCESS;
	}
	PrintResult(res,"Test_MyMalloc_Null");
}

void Test_MyMalloc_Oversize()
{
	Result res = FAILED; 
	void* mem = malloc(1000);
	void* allocated;
	if(!mem)
	{
		res = FAILED;
		PrintResult(res,"Test_MyMalloc_Oversize");
		return;
	}
	MyMallocInit(mem,1000);
	allocated = MyMalloc(mem,1500);
	if(!allocated)
	{
		res = SUCCESS;
	}
	free(mem);
	PrintResult(res,"Test_MyMalloc_Oversize");
}

void Test_MyMalloc_Full()
{
	Result res = SUCCESS;
	void* allocated;
	void* allocated1;
	void* allocated2;
	BYTE* mem = (BYTE*)malloc(1000);

	if(!mem)
	{
		res = FAILED;
		PrintResult(res,"Test_MyMalloc_Full");
		return;
	}
	MyMallocInit(mem,1000);
	allocated = MyMalloc(mem,500);
	allocated1 = MyMalloc(mem,484);
	allocated2 = MyMalloc(mem,12);
	if(!allocated || *((int*)mem+1)!=-500)
	{
		res = FAILED;
	}
	if(!allocated1 || *((int*)&mem[513])==-484)
	{
		res = FAILED;
	}
	if(allocated2)
	{
		res = FAILED;
	}
	free(mem);
	PrintResult(res,"Test_MyMalloc_Full");
}

void Test_MyFree_Vallid()
{
	Result res = FAILED; 
	void* allocated;
	void* mem = malloc(1000);

	if(!mem)
	{
		res = FAILED;
		PrintResult(res,"Test_MyFree_Vallid");
		return;
	}
	MyMallocInit(mem,1000);
	allocated = MyMalloc(mem,500);
	MyFree(allocated);
	if(*((int*)mem+1)==988)
	{
		res = SUCCESS;
	}
	free(mem);
	PrintResult(res,"Test_MyFree_Vallid");
}

int main()
{
	/*List Func tests
	void MyMallocInit(void* _memory, size_t _memorySize);
	void* MyMalloc(void* _memory, size_t _requiredBlockSize);	
	void MyFree(void* _myBlock);
	*/
	printf("MyMallocInit tests:\n");
	Test_MyMallocInit_Valid();
	Test_MyMallocInit_Null();

	printf("\nMyMalloc tests:\n");
	Test_MyMalloc_Valid();
	Test_MyMalloc_Null();
	Test_MyMalloc_Oversize();
	Test_MyMalloc_Full();

	printf("\nMyFree tests:\n");
	Test_MyFree_Vallid();

	return 0;
}
