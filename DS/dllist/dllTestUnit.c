#include<stdio.h>
#include<stdlib.h>
#include "dllist.h"
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

void CreateList_Valid()
{
	list* listp = ListCreate();
	Result res; 
	if(listp)
	{
		res = SUCCESS;
		ListDestroy(listp);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "CreateList_Valid");
}

void ListDestroy_Vaild()
{
	
	list* listp = ListCreate();
	Result res = SUCCESS;
	ListDestroy(listp);
	PrintResult(res , "ListDestroy_Vaild");
}

void ListDestroy_Null()
{
	
	list* listp = NULL;
	Result res = SUCCESS;
	ListDestroy(listp);
	PrintResult(res , "ListDestroy_Null");
}

void ListDestroy_DuobleDestroy()
{
	
	list* listp = ListCreate();
	Result res = SUCCESS;
	ListDestroy(listp);
	ListDestroy(listp);
	PrintResult(res , "ListDestroy_DuobleDestroy");
}

void ListDestroy_HugeDestroy()
{
	int i;
	list* listp = ListCreate();
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		ListPushHead(listp,i);
	}
	ListDestroy(listp);
	PrintResult(res , "ListDestroy_HugeDestroy");
}

void TestListPushHead_Vaild()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS==ListPushHead(listp,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushHead_Vaild");
}

void TestListPushHead_Null()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS!=ListPushHead(NULL,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushHead_Null");
}


void TestListPushHead_DoubleInsert()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS!=ListPushHead(listp,rand()))
	{
		res = FAILED;
	}
	else if(ERR_SUCCESS!=ListPushHead(listp,rand()))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushHead_DoubleInsert");
}

void TestListPushHead_HugeInsert()
{
	int i;
	list* listp = ListCreate();
	Result res = SUCCESS; ;
	for(i=0;i<HUGE_LEN;i++)
	{
		if(ListPushHead(listp,i)!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushHead_HugeInsert");
}

void TestListPopHead_Vaild()
{
	list* listp = ListCreate();
	Result res;
	int data;
	ListPushHead(listp,rand());
	if(ERR_SUCCESS==ListPopHead(listp,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopHead_Vaild");
}

void TestListPopHead_Null()
{
	Result res;
	int data;
	if(ERR_SUCCESS!=ListPopHead(NULL,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListPopHead_Null");
}

void TestListPopHead_Empty()
{
	list* listp = ListCreate();
	Result res;
	int data;
	if(ERR_SUCCESS!=ListPopHead(listp,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopHead_Empty");
}

void TestListPopHead_DoubleRemove()
{
	int data;
	Result res;
	list* listp = ListCreate();
	ListPushHead(listp,rand());
	ListPushHead(listp,rand());
	if(ERR_SUCCESS!=ListPopHead(listp,&data))
	{
		res = FAILED;
	}
	if(ERR_SUCCESS!=ListPopHead(listp,&data))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopHead_DoubleRemove");
}

void TestListPopHead_HugeRemove()
{
	int i,data;
	list* listp = ListCreate();
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		ListPushHead(listp,i);
	}
	for(i=0;i<HUGE_LEN;i++)
	{
		if(ListPopHead(listp,&data)!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopHead_HugeRemove");
}

void TestListPushTail_Vaild()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS==ListPushTail(listp,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushTail_Vaild");
}


void TestListPushTail_Null()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS!=ListPushTail(NULL,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushTail_Null");
}


void TestListPushTail_DoubleInsert()
{
	list* listp = ListCreate();
	Result res;
	if(ERR_SUCCESS!=ListPushTail(listp,rand()))
	{
		res = FAILED;
	}
	else if(ERR_SUCCESS!=ListPushTail(listp,rand()))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushTail_DoubleInsert");
}

void TestListPushTail_HugeInsert()
{
	int i;
	list* listp = ListCreate();
	Result res = SUCCESS; ;
	for(i=0;i<HUGE_LEN;i++)
	{
		if(ListPushTail(listp,i)!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPushTail_HugeInsert");
}

void TestListPopTail_Vaild()
{
	list* listp = ListCreate();
	Result res;
	int data;
	ListPushTail(listp,rand());
	if(ERR_SUCCESS==ListPopTail(listp,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopTail_Vaild");
}

void TestListPopTail_Null()
{
	Result res;
	int data;
	if(ERR_SUCCESS!=ListPopTail(NULL,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListPopTail_Null");
}

void TestListPopTail_Empty()
{
	list* listp = ListCreate();
	Result res;
	int data;
	if(ERR_SUCCESS!=ListPopTail(listp,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopTail_Empty");
}

void TestListPopTail_DoubleRemove()
{
	int data;
	Result res;
	list* listp = ListCreate();
	ListPushTail(listp,rand());
	ListPushTail(listp,rand());
	if(ERR_SUCCESS!=ListPopTail(listp,&data))
	{
		res = FAILED;
	}
	if(ERR_SUCCESS!=ListPopTail(listp,&data))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopTail_DoubleRemove");
}

void TestListPopTail_HugeRemove()
{
	int i,data;
	list* listp = ListCreate();
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		ListPushTail(listp,i);
	}
	for(i=0;i<HUGE_LEN;i++)
	{
		if(ListPopTail(listp,&data)!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	ListDestroy(listp);
	PrintResult(res , "TestListPopTail_HugeRemove");
}

void TestListCount_Valid()
{
	list* listp = ListCreate();
	Result res;
	int i,size = rand()/10000;
	for(i=0;i<size;i++)
	{
		ListPushTail(listp,i);
	}
	if(size==ListCountItems(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListCount_Valid");
}

void TestListCount_Null()
{
	Result res;
	if(0==ListCountItems(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListCount_Null");
}

void TestListCount_Empty()
{
	list* listp = ListCreate();
	Result res;
	if(0==ListCountItems(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListCount_Empty");
}

void TestListCount_Huge()
{
	list* listp = ListCreate();
	Result res;
	int i;
	for(i=0;i<HUGE_LEN;i++)
	{
		ListPushTail(listp,i);
	}
	if(HUGE_LEN==ListCountItems(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListCount_Huge");
}

void TestListisEmpty_NotEmpty()
{
	list* listp = ListCreate();
	Result res;
	ListPushTail(listp,rand());
	if(0==ListIsEmpty(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListisEmpty_NotEmpty");
}

void TestListisEmpty_Empty()
{
	list* listp = ListCreate();
	Result res;
	if(1==ListIsEmpty(listp))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	ListDestroy(listp);
	PrintResult(res , "TestListisEmpty_Empty");
}

void TestListisEmpty_Null()
{
	Result res;
	if(0==ListIsEmpty(NULL))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListisEmpty_Null");
}

int main()
{

	printf("\nCreate & destroy tests:\n");
	/*destroy & create tests*/
	CreateList_Valid();
	ListDestroy_Vaild();
	ListDestroy_Null();
	ListDestroy_DuobleDestroy();
	ListDestroy_HugeDestroy();				

	/*insert head tests*/
	printf("\nPush head tests:\n");
	TestListPushHead_Vaild();
	TestListPushHead_Null();
	TestListPushHead_DoubleInsert();
	TestListPushHead_HugeInsert();
	
	/*remove head tests*/
	printf("\nPop head tests:\n");
	TestListPopHead_Vaild();
	TestListPopHead_Null();
	TestListPopHead_Empty();
	TestListPopHead_DoubleRemove();
	TestListPopHead_HugeRemove();

	/*insert tail tests*/
	printf("\nPush tail tests:\n");
	TestListPushTail_Vaild();
	TestListPushTail_Null();
	TestListPushTail_DoubleInsert();
	TestListPushTail_HugeInsert();
	
	/*remove tail tests*/
	printf("\nPop head tests:\n");
	TestListPopTail_Vaild();
	TestListPopTail_Null();
	TestListPopTail_Empty();
	TestListPopTail_DoubleRemove();
	TestListPopTail_HugeRemove();

	/*Count tests*/
	printf("\nCount tests:\n");
	TestListCount_Valid();
	TestListCount_Null();	
	TestListCount_Empty();	
	TestListCount_Huge();

	/*Empty tests*/
	printf("\nIs Empty tests:\n");
	TestListisEmpty_NotEmpty();
	TestListisEmpty_Null();	
	TestListisEmpty_Empty();	

	return 0;
	
}










