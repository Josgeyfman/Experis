#include<stdio.h>
#include<stdlib.h>
#include "bst.h"
#define HUGE_LEN 10

typedef enum{
		SUCCESS,
		FAILED
} Result;

int Smaller(void* _a, void* _b)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	return ( *a < *b);
}

int Equal(void* _a, void* _b)
{
	int* a = (int*)_a;
	int* b = (int*)_b;
	return ( *a == *b);
}

int PrintVal(void* _element , void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
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

void BSTree_Create_Valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res; 
	if(treep)
	{
		res = SUCCESS;
		BSTree_Destroy(treep,NULL);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "BSTree_Create_Valid");
}

void BSTree_Destroy_Vaild()
{
	
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Destroy_Vaild");
}

void BSTree_Destroy_Null()
{
	
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Destroy_Null");
}

void BSTree_Destroy_DuobleDestroy()
{
	
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	BSTree_Destroy(treep,NULL);
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Destroy_DuobleDestroy");
}

void BSTree_Destroy_HugeDestroy()
{
	int i,arr[HUGE_LEN];
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		BSTree_Insert(treep,&arr[i]);
	}
	/*BSTree_ForEach(treep,BSTREE_TRAVERSAL_INORDER,PrintVal,NULL);*/
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Destroy_HugeDestroy");
}

void BSTree_Insert_Vaild()
{
	Result res;
	int a=7;
	BSTree* treep = BSTree_Create(Smaller);
	if(BSTree_Insert(treep,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Insert_Vaild");
}

void BSTree_Insert_Null()
{
	BSTree* treep = NULL;
	Result res;
	int a=7;
	if(!BSTree_Insert(treep,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "BSTree_Insert_Null");
}

void BSTree_Insert_Empty()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res;
	int a =  rand();
	if(BSTree_Insert(treep,&a))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Insert_Empty");
}

void BSTree_Insert_DoubleInsert()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res;
	int a =  rand() , b = rand();
	if(!BSTree_Insert(treep,&a))
	{
		res = FAILED;
	}
	else if(!BSTree_Insert(treep,&b))
	{
		res = FAILED;
	}
	else
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Insert_DoubleInsert");
}

void BSTree_Insert_HugeInsert()
{
	int i,arr[HUGE_LEN];
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		if(!BSTree_Insert(treep,&arr[i]))
		{
			res = FAILED;		
		}
	}
	/*BSTree_ForEach(treep,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);*/
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_Insert_HugeInsert");
}

void BSTree_FindFirst_Vaild()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res;
	int a = 7;
	int b = 7;
	BSTree_Insert(treep,&a);
	if(BSTree_FindFirst(treep,Equal,&b))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_FindFirst_Vaild");
}

void BSTree_FindFirst_NotVaild()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res;
	int a = 7;
	int b = 8;
	BSTree_Insert(treep,&a);
	if(!BSTree_FindFirst(treep,Equal,&b))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_FindFirst_NotVaild");
}


void BSTree_FindFirst_Null()
{
	Result res;
	int data = 3;
	if(!BSTree_FindFirst(NULL,Equal,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "BSTree_FindFirst_Null");
}


void BSTree_FindFirst_Empty()
{
	Result res;
	BSTree* treep = BSTree_Create(Smaller);
	int data = 7;
	if(!BSTree_FindFirst(treep,Equal,&data))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_FindFirst_Empty");
}

void BSTree_FindFirst_Huge()
{
	int i,arr[HUGE_LEN];
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		BSTree_Insert(treep,&arr[i]);
	}
	i=i%7;
	if(BSTree_FindFirst(treep,Equal,&i))
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_FindFirst_Huge");
}

	/*BSTree_ForEach(treep,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);*/
void BSTree_ForEach_InOrder_Vaild()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	int arr[3]={17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	BSTree_ForEach(treep,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_ForEach_InOrder_Vaild");
}

void BSTree_ForEach_PostOrder_Vaild()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	int arr[3]={17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	BSTree_ForEach(treep,BSTREE_TRAVERSAL_POSTORDER,PrintVal,NULL);
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_ForEach_PostOrder_Vaild");
}

void BSTree_ForEach_PreOrder_Vaild()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	int arr[3]={17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	BSTree_ForEach(treep,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_ForEach_PreOrder_Vaild");
}

void BSTree_ForEach_Null()
{
	Result res = SUCCESS;
	BSTree_ForEach(NULL,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);
	PrintResult(res , "BSTree_ForEach_Null");
}

void BSTree_ForEach_Empty()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = SUCCESS;
	BSTree_ForEach(NULL,BSTREE_TRAVERSAL_PREORDER,PrintVal,NULL);
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTree_ForEach_Empty");
}

void BSTreeItr_Begin_valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = FAILED;
	int arr[3] = {17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	if(BSTreeItr_Get(BSTreeItr_Begin(treep))==(BSTreeItr)&arr[1])
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTreeItr_Begin_valid");
}

void BSTreeItr_End_valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	Result res = FAILED;
	int arr[3] = {17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	if(BSTreeItr_Get(BSTreeItr_End(treep))==NULL)
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTreeItr_End_valid");
}

void BSTreeItr_Next_valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	BSTreeItr next;
	Result res = FAILED;
	int arr[3] = {17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	next = BSTreeItr_Begin(treep);
	next = BSTreeItr_Next(next);
	if(BSTreeItr_Get(next)==(BSTreeItr)&arr[0])
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTreeItr_Next_valid");
}

void BSTreeItr_Prev_valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	BSTreeItr prev;
	Result res = FAILED;
	int arr[3] = {17,-50,19};
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	prev = BSTreeItr_End(treep);
	prev = BSTreeItr_Prev(prev);
	if(BSTreeItr_Get(prev)==(BSTreeItr)&arr[2])
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTreeItr_Prev_valid");
}

void BSTreeItr_Remove_valid()
{
	BSTree* treep = BSTree_Create(Smaller);
	BSTreeItr prev;
	Result res = FAILED;
	int arr[3] = {17,-50,19};
	void* remData;
	BSTree_Insert(treep,&arr[0]);
	BSTree_Insert(treep,&arr[1]);
	BSTree_Insert(treep,&arr[2]);
	prev = BSTreeItr_End(treep);
	remData = BSTreeItr_Remove(prev);
	if(BSTreeItr_Get(prev)==(BSTreeItr)&arr[2])
	{
		res = SUCCESS;
	}
	BSTree_Destroy(treep,NULL);
	PrintResult(res , "BSTreeItr_Remove_valid");
}

int main()
{
	/*destroy & create tests*/
	printf("\nCreate & destroy tests:\n");
	BSTree_Destroy_HugeDestroy();
	BSTree_Destroy_DuobleDestroy();
	BSTree_Destroy_Null();
	BSTree_Destroy_Vaild();
	BSTree_Create_Valid();

	/*insert tests*/
	printf("\nInsert tests:\n");
 	BSTree_Insert_Vaild();
	BSTree_Insert_Empty();
	BSTree_Insert_Null();
	BSTree_Insert_DoubleInsert();
	BSTree_Insert_HugeInsert();

	/*find first tests*/
	printf("\nfind first tests:\n");
	BSTree_FindFirst_Huge();
 	BSTree_FindFirst_Empty();
 	BSTree_FindFirst_Null();
	BSTree_FindFirst_NotVaild();
	BSTree_FindFirst_Vaild();

	/*for each  tests*/
	printf("\nfor each tests:\n");
	BSTree_ForEach_Empty();
	BSTree_ForEach_Null();
	BSTree_ForEach_PreOrder_Vaild();
	BSTree_ForEach_PostOrder_Vaild();
	BSTree_ForEach_InOrder_Vaild();

	/*Bst iter  tests*/
	printf("\nbst iter tests:\n");
	BSTreeItr_Begin_valid();
	BSTreeItr_End_valid();
	BSTreeItr_Next_valid();
	BSTreeItr_Prev_valid();
	BSTreeItr_Remove_valid();
	return 0;
	
}










