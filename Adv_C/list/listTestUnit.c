#include<stdio.h>
#include<stdlib.h>
#include"list.h"
#include"iterator.h"
#include"myStruct.h"
#include"adt_error.h"
#define HUGE_LEN 10

typedef enum{
		SUCCESS,
		FAILED
} Result;

void PrintVal(const void* _element ,void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
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

void List_Create_Valid()
{
	Result res; 
	List* listp = List_Create();
	if(listp)
	{
		res = SUCCESS;
		List_Destroy(&listp,NULL);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_Create_Valid");
}

void List_Destroy_Vaild()
{
	
	List* listp = List_Create();
	Result res = SUCCESS;
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_Destroy_Vaild");
}

void List_Destroy_Null()
{
	
	List* listp = NULL;
	Result res = SUCCESS;
	List_Destroy(&listp ,NULL);
	PrintResult(res , "ListDestroy_Null");
}

void List_Destroy_Valid_Func()
{
	Result res = SUCCESS;
	mystruct* mys = CreateMyStruct(1);
	List* listp = List_Create();
	List_PushHead(listp,mys);
	List_Destroy(&listp,FreeMyStruct);
	PrintResult(res , "List_Destroy_Valid_Func");
}

void List_Destroy_DuobleDestroy()
{
	
	List* listp = List_Create();
	Result res = SUCCESS;
	List_Destroy(&listp,NULL);
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_Destroy_DuobleDestroy");
}

void List_Destroy_HugeDestroy()
{
	int i;
	Result res = SUCCESS;
	mystruct* mys;
	List* listp = List_Create();
	for(i=0;i<HUGE_LEN;i++)
	{
		mys = CreateMyStruct(i);
		List_PushHead(listp,mys);
	}
	/*List_ForEach(listp,PrintMyStruct,NULL);*/
	List_Destroy(&listp,FreeMyStruct);
	PrintResult(res , "List_Destroy_HugeDestroy");
}

void List_PushHead_Vaild()
{
	List* listp = List_Create();
	Result res;
	int a = rand();
	if(LIST_SUCCESS==List_PushHead(listp,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushHead_Vaild");
}

void List_PushHead_Null()
{
	Result res;
	int a = rand();
	if(LIST_SUCCESS!=List_PushHead(NULL,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_PushHead_Null");
}

void List_PushHead_Null_Element()
{
	Result res;
	List* listp = List_Create();
	if(LIST_SUCCESS!=List_PushHead(listp,NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushHead_Null_Element");
}


void List_PushHead_DoubleInsert()
{
	List* listp = List_Create();
	Result res;
	int a=5,b=7;
	if(LIST_SUCCESS!=List_PushHead(listp,&a))
	{
		res = FAILED;
	}
	else if(LIST_SUCCESS!=List_PushHead(listp,&b))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushHead_DoubleInsert");
}


void List_PushHead_HugeInsert()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		if(List_PushHead(listp,&arr[i])!=LIST_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushHead_HugeInsert");
}

void List_PopHead_Vaild()
{
	Result res;
	int data = 5;
	int* a = &data;
	List* listp = List_Create();
	List_PushHead(listp,a);
	if(LIST_SUCCESS==List_PopHead(listp,(void**)&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopHead_Vaild");
}

void List_PopHead_Null()
{
	Result res;
	int* data;
	if(LIST_SUCCESS!=List_PopHead(NULL,(void**)&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_PopHead_Null");
}

void List_PopHead_Empty()
{
	int* data;
	List* listp = List_Create();
	Result res;
	if(LIST_SUCCESS!=List_PopHead(listp,(void**)&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopHead_Empty");
}

void List_PopHead_DoubleRemove()
{
	int val1,val2;
	int * poped;
	Result res;
	List* listp = List_Create();
	val1 = rand();
	val2 = rand();
	List_PushHead(listp,&val1);
	List_PushHead(listp,&val2);
	if(LIST_SUCCESS!=List_PopHead(listp,(void**)&poped) && *poped == val1)
	{
		res = FAILED;
	}
	if(LIST_SUCCESS!=List_PopHead(listp,(void**)&poped) && *poped == val2)
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopHead_DoubleRemove");
}

void List_PopHead_HugeRemove()
{
	int i,arr[HUGE_LEN];
	int * barr[HUGE_LEN];
	List* listp ;
	Result res = SUCCESS; 
	listp = List_Create();
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		List_PushHead(listp,&arr[i]);
	}
	for(i=HUGE_LEN-1;i>=0;i--)
	{
		if(List_PopHead(listp,(void**)&barr[i])!=LIST_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopHead_HugeRemove");
}

void List_PushTail_Vaild()
{
	List* listp = List_Create();
	Result res;
	int a = rand()%HUGE_LEN;
	if(LIST_SUCCESS==List_PushTail(listp,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushTail_Vaild");
}



void List_PushTail_Null()
{
	Result res;
	int a = rand()%HUGE_LEN;
	if(LIST_SUCCESS!=List_PushTail(NULL,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_PushTail_Null");
}

void List_PushTail_Null_Element()
{
	Result res;
	List* listp = List_Create();
	if(LIST_SUCCESS!=List_PushTail(listp,NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushTail_Null_Element");
}


void List_PushTail_DoubleInsert()
{
	List* listp = List_Create();
	Result res;
	int a=5,b=7;
	if(LIST_SUCCESS!=List_PushTail(listp,&a))
	{
		res = FAILED;
	}
	/*printf("\n");
	List_ForEach(listp,PrintVal,NULL);
	printf("\n");*/
	if(LIST_SUCCESS!=List_PushTail(listp,&b))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	/*List_ForEach(listp,PrintVal,NULL);
	printf("\n");*/
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushTail_DoubleInsert");
}


void List_PushTail_HugeInsert()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		if(List_PushTail(listp,&arr[i])!=LIST_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PushTail_HugeInsert");
}


void List_PopTail_Vaild()
{
	Result res;
	int data = 5;
	int* a = &data;
	List* listp = List_Create();
	List_PushHead(listp,a);
	if(LIST_SUCCESS==List_PopTail(listp,(void**)&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopTail_Vaild");
}

void List_PopTail_Null()
{
	Result res;
	int* data;
	if(LIST_SUCCESS!=List_PopTail(NULL,(void**)&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_PopTail_Null");
}

void List_PopTail_Empty()
{
	int* data;
	List* listp = List_Create();
	Result res;
	if(LIST_SUCCESS!=List_PopTail(listp,(void**)&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopTail_Empty");
}

void List_PopTail_DoubleRemove()
{
	int val1,val2;
	int * ret;
	Result res;
	List* listp = List_Create();
	val1 = rand();
	val2 = rand();
	List_PushHead(listp,&val1);
	List_PushHead(listp,&val2);
	if(LIST_SUCCESS!=List_PopTail(listp,(void**)&ret))
	{
		res = FAILED;
	}
	if(LIST_SUCCESS!=List_PopTail(listp,(void**)&ret))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopTail_DoubleRemove");
}

void List_PopTail_HugeRemove()
{
	int i,arr[HUGE_LEN];
	int * barr[HUGE_LEN];
	List* listp ;
	Result res = SUCCESS; 
	listp = List_Create();
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		List_PushHead(listp,&arr[i]);
	}
	for(i=HUGE_LEN-1;i>=0;i--)
	{
		if(List_PopTail(listp,(void**)&barr[i])!=LIST_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_PopTail_HugeRemove");
}


void List_Size_Valid()
{
	int i,arr[50],size = 50;
	List* listp = List_Create();
	Result res;
	for(i=0;i<size;i++)
	{
		arr[i] = i;
		List_PushTail(listp,&arr[i]);
	}
	if(size==List_Size(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_Size_Valid");
}

void List_Size_Null()
{
	Result res;
	if(0==List_Size(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "List_Size_Null");
}

void List_Size_Empty()
{
	List* listp = List_Create();
	Result res;
	if(0==List_Size(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_Size_Empty");
}

void List_Size_Huge()
{
	List* listp = List_Create();
	Result res;
	int i,arr[HUGE_LEN],size = HUGE_LEN;
	for(i=0;i<size;i++)
	{
		arr[i] = i;
		List_PushTail(listp,&arr[i]);
	}
	if(size==List_Size(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "List_Size_Valid");
}


int main()
{
	printf("Create & destroy tests:\n");
	/*destroy & create tests*/
	List_Create_Valid();
	List_Destroy_Vaild();
	List_Destroy_Null();
	List_Destroy_Valid_Func();
	List_Destroy_DuobleDestroy();
	List_Destroy_HugeDestroy();			

	/*insert head tests*/
	printf("\nPush head tests:\n");
	List_PushHead_Vaild();
	List_PushHead_Null();
	List_PushHead_Null_Element();
	List_PushHead_DoubleInsert();
	List_PushHead_HugeInsert();
	
	/*remove head tests*/
	printf("\nPop head tests:\n");
	List_PopHead_Vaild();
	List_PopHead_Null();
	List_PopHead_Empty();
	List_PopHead_DoubleRemove();
	List_PopHead_HugeRemove();

	/*insert tail tests*/
	printf("\nPush tail tests:\n");
	List_PushTail_Vaild();
	List_PushTail_Null();
	List_PushTail_Null_Element();
	List_PushTail_DoubleInsert();
	List_PushTail_HugeInsert();
	
	/*remove tail tests*/
	printf("\nPop head tests:\n");
	List_PopTail_Vaild();
	List_PopTail_Null();
	List_PopTail_Empty();
	List_PopTail_DoubleRemove();
	List_PopTail_HugeRemove();

	/*Size tests*/
	printf("\nSize tests:\n");
	List_Size_Valid();
	List_Size_Null();	
	List_Size_Empty();	
	List_Size_Huge();

	return 0;
	
}










