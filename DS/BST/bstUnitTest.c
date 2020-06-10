#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
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

void TreeCreate_Valid()
{
	tree* treep = TreeCreate();
	Result res; 
	if(treep)
	{
		res = SUCCESS;
		TreeDestroy(treep);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TreeCreate_Valid");
}

void TreeDestroy_Vaild()
{
	
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreeDestroy(treep);
	PrintResult(res , "TreeDestroy_Vaild");
}

void TreeDestroy_Null()
{
	
	tree* treep = NULL;
	Result res = SUCCESS;
	TreeDestroy(treep);
	PrintResult(res , "TreeDestroy_Null");
}

void TreeDestroy_DuobleDestroy()
{
	
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreeDestroy(treep);
	TreeDestroy(treep);
	PrintResult(res , "TreeDestroy_DuobleDestroy");
}

void TreeDestroy_HugeDestroy()
{
	int i;
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		TreeInsert(treep,i);
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeDestroy_HugeDestroy");
}

void TreeInsert_Vaild()
{
	Result res;
	tree* treep = TreeCreate();
	if(ERR_SUCCESS==TreeInsert(treep,7))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeInsert_Vaild");
}

void TreeInsert_Null()
{
	tree* treep = NULL;
	Result res;
	if(ERR_SUCCESS!=TreeInsert(treep,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeInsert_Null");
}

void TreeInsert_Empty()
{
	tree* treep = TreeCreate();
	Result res;
	if(ERR_SUCCESS==TreeInsert(treep,rand()))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeInsert_Empty");
}

void TreeInsert_DoubleInsert()
{
	tree* treep = TreeCreate();
	Result res;
	if(ERR_SUCCESS!=TreeInsert(treep,rand()))
	{
		res = FAILED;
	}
	else if(ERR_SUCCESS!=TreeInsert(treep,rand()))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeInsert_DoubleInsert");
}

void TreeInsert_HugeInsert()
{
	int i;
	tree* treep = TreeCreate();
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		if(TreeInsert(treep,i)!=ERR_SUCCESS)
		{
			res = FAILED;
			break;
		}
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeInsert_HugeInsert");
}

void TreeIsFound_Vaild()
{
	tree* treep = TreeCreate();
	Result res;
	TreeInsert(treep,7);
	if(0<TreeIsDataFound(treep,7))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeIsFound_Vaild");
}

void TreeIsNotFound_Vaild()
{
	tree* treep = TreeCreate();
	Result res;
	TreeInsert(treep,7);
	if(0==TreeIsDataFound(treep,8))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeIsNotFound_Vaild");
}
void TreeIsFound_Null()
{
	Result res;
	int data = rand();
	if(0>TreeIsDataFound(NULL,data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListPopHead_Null");
}

void TreeIsFound_Empty()
{
	Result res;
	tree* treep = TreeCreate();
	int data = 7;
	if(0==TreeIsDataFound(treep,data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeIsFound_Empty");
}

void TreeIsFound_Huge()
{
	int i;
	tree* treep = TreeCreate();
	Result res = SUCCESS; 
	for(i=0;i<HUGE_LEN;i++)
	{
		TreeInsert(treep,i);
	}
	if(TreeIsDataFound(treep,i%7))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	TreeDestroy(treep);
	PrintResult(res , "TreeIsFound_Huge");
}

void TreePrintInOrder_Vaild()
{
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreePrint(treep,IN_ORDER);
	TreeDestroy(treep);
	PrintResult(res , "TreePrintInOrder_Vaild");
}

void TreePrintPostOrder_Vaild()
{
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreePrint(treep,POST_ORDER);
	TreeDestroy(treep);
	PrintResult(res , "TreePrintPostOrder_Vaild");
}

void TreePrintPreOrder_Vaild()
{
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreeInsert(treep,rand());
	TreePrint(treep,PRE_ORDER);
	TreeDestroy(treep);
	PrintResult(res , "TreePrintPreOrder_Vaild");
}

void TreePrint_Null()
{
	Result res = SUCCESS;
	TreePrint(NULL,PRE_ORDER);
	PrintResult(res , "TreePrintPreOrder_Null");
}

void TreePrint_Empty()
{
	tree* treep = TreeCreate();
	Result res = SUCCESS;
	TreePrint(treep,PRE_ORDER);
	TreeDestroy(treep);
	PrintResult(res , "TreePrint_Empty");
}

int main()
{

	printf("\nCreate & destroy tests:\n");
	/*destroy & create tests*/
	TreeDestroy_HugeDestroy();
	TreeDestroy_DuobleDestroy();
	TreeDestroy_Null();
	TreeDestroy_Vaild();
	TreeCreate_Valid();
	/*insert tests*/
	printf("\nInsert tests:\n");
 	TreeInsert_Vaild();
	TreeInsert_Empty();
	TreeInsert_Null();
	TreeInsert_DoubleInsert();
	TreeInsert_HugeInsert();
	/*is found head tests*/
	printf("\nIs Found tests:\n");
	TreeIsFound_Huge();
 	TreeIsFound_Empty();
 	TreeIsFound_Null();
	TreeIsFound_Vaild();
	TreeIsNotFound_Vaild();
	/*print tail tests*/
	printf("\nPrint tests:\n");
	TreePrint_Empty();
	TreePrint_Null();
	TreePrintPreOrder_Vaild();
	TreePrintPostOrder_Vaild();
	TreePrintInOrder_Vaild();

	return 0;
	
}










