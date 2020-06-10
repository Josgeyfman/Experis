#include<stdio.h>
#include<stdlib.h>
#include"list.h"
#include"iterator.h"
#include"myStruct.h"
#include"adt_error.h"
#include"list_functions.h"
#define HUGE_LEN 10
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

int IsEven(void* _a, void* _context)
{
	return ((*(int*)_a%2) == 0);
}

int IsOdd(void* _a, void* _context)
{
	return ((*(int*)_a%2) != 0);
}

int PrintVal(void* _element , void* _context)
{
	int* el = (int*)_element;
	printf("%d,",*el);
	return 1;
}

int PrintPos(void* _element , void* _context)
{
	int* el = (int*)_element;
	if(*el>0)
	{
		printf("%d,",*el);
		return 1;
	}
	return 0;
}



void Test_ListItr_FindFirst()
{
	int i,arr[HUGE_LEN];
	Result res = FAILED; 
	List* listp = List_Create();
	ListItr begin,found;
	ListItr end = ListItr_End(listp);
	
	for(i=0;i<HUGE_LEN-1;i++)
	{
		arr[i] = 2*i;
		List_PushHead(listp,&arr[i]);
	}
	arr[i] = 13;
	List_PushHead(listp,&arr[i]);

	begin = ListItr_Begin(listp);
	found = ListItr_FindFirst(begin,end,IsOdd,NULL);
	i = (*(int*)ListItr_Get(found));
	if(i==13)
	{
		res = SUCCESS;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "Test_ListItr_FindFirst");
}

void Test_ListItr_CountIf()
{
	int i,arr[HUGE_LEN];
	Result res = FAILED; 
	List* listp = List_Create();
	ListItr begin;
	ListItr end = ListItr_End(listp);
	
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		List_PushHead(listp,&arr[i]);
	}

	begin = ListItr_Begin(listp);
	i = ListItr_CountIf(begin,end,IsEven,NULL);
	if(i==HUGE_LEN/2)
	{
		printf("i %d\n",i);
		res = SUCCESS;
	}
	List_Destroy(&listp,NULL);
	PrintResult(res , "Test_ListItr_CountIf");
}

void Test_ListItr_ForEach()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	ListItr begin;
	ListItr end = ListItr_End(listp);
	
	for(i=0;i<HUGE_LEN-1;i++)
	{
		arr[i] = i+1;
		List_PushHead(listp,&arr[i]);
	}
	arr[i] = -1;
	List_PushTail(listp,&arr[i]);
	begin = ListItr_Begin(listp);
	ListItr_ForEach(begin,end,PrintPos,NULL);
	List_Destroy(&listp,NULL);
	PrintResult(res , "\nTest_ListItr_ForEach");
}

void Test_ListItr_Sort()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	ListItr begin;
	ListItr end = ListItr_End(listp);
	
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = rand()%HUGE_LEN;
		List_PushHead(listp,&arr[i]);
	}
	begin = ListItr_Begin(listp);
	printf("before sort\n");
	ListItr_ForEach(begin,end,PrintVal,NULL);
	ListItr_Sort(begin,end,Smaller);
	printf("\nafter sort\n");
	ListItr_ForEach(begin,end,PrintVal,NULL);
	List_Destroy(&listp,NULL);
	PrintResult(res , "\nTest_ListItr_Sort");
}

void Test_ListItr_Splice()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	ListItr begin;
	ListItr end = ListItr_End(listp);
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		List_PushHead(listp,&arr[i]);
	}
	begin = ListItr_Begin(listp);
	printf("before splice head\n");
	ListItr_ForEach(begin,end,PrintVal,NULL);
	ListItr_Splice(begin,ListItr_Next(begin),end);
	printf("\nafter splice\n");
	end = ListItr_End(listp);
	begin = ListItr_Begin(listp);
	ListItr_ForEach(begin,end,PrintVal,NULL);
	
	List_Destroy(&listp,NULL);
	PrintResult(res , "\nTest_ListItr_Splice");
}

void Test_ListItr_Merge()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp1 = List_Create();
	List* listp2 = List_Create();
	List* listpDst = List_Create();
	ListItr begin1 , begin2 ,beginDst;
	ListItr end1 = ListItr_End(listp1);
	ListItr end2 = ListItr_End(listp2);
	ListItr endDst = ListItr_End(listpDst);

	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		if(i%2==0)
		{
			List_PushHead(listp1,&arr[i]);
		}
		else
		{
			List_PushHead(listp2,&arr[i]);
		}
	}
	printf("before merge \n list 1\n");
	begin1 = ListItr_Begin(listp1);
	ListItr_ForEach(begin1,end1,PrintVal,NULL);
	printf("\nlist 2 \n");
	begin2	= ListItr_Begin(listp2);
	ListItr_ForEach(begin2,end2,PrintVal,NULL);

	ListItr_Merge(endDst,begin1,end1,begin2,end2,Smaller);
	printf("\nafter merge\n");
	beginDst = ListItr_Begin(listpDst);
	ListItr_ForEach(beginDst,endDst,PrintVal,NULL);
	
	
	List_Destroy(&listp1,NULL);
	List_Destroy(&listp2,NULL);
	List_Destroy(&listpDst,NULL);
	PrintResult(res , "Test_ListItr_Merge");
}

void Test_ListItr_Cut()
{
	int i,arr[HUGE_LEN];
	Result res = SUCCESS; 
	List* listp = List_Create();
	List* listDst = NULL;
	ListItr begin;
	ListItr end = ListItr_End(listp);
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = i;
		List_PushHead(listp,&arr[i]);
	}
	begin = ListItr_Begin(listp);
	printf("before Cut head\n");
	ListItr_ForEach(begin,end,PrintVal,NULL);
	listDst = ListItr_Cut(ListItr_Next(begin),end);
	printf("\nafter Cut\n listp:\n");
	end = ListItr_End(listp);
	begin = ListItr_Begin(listp);
	ListItr_ForEach(begin,end,PrintVal,NULL);
	printf("\n listDst:\n");
	end = ListItr_End(listDst);
	begin = ListItr_Begin(listDst);
	ListItr_ForEach(begin,end,PrintVal,NULL);
	List_Destroy(&listp,NULL);
	List_Destroy(&listDst,NULL);
	PrintResult(res , "Test_ListItr_Cut");
}

void Test_ListItr_Unique()
{
	int i,j=0,arr[HUGE_LEN];
	Result res = SUCCESS; 
	ListItr begin,end;
	List* listp = List_Create();
	List* listDst;
	
	end = ListItr_End(listp);
	for(i=0;i<HUGE_LEN;i++)
	{
		arr[i] = j;
		if(i%3==0)
		{
			j++;
		}
		List_PushTail(listp,&arr[i]);
	}
	begin = ListItr_Begin(listp);
	printf("\nbefore unique head\n");
	ListItr_ForEach(begin,end,PrintVal,NULL);
	listDst = ListItr_Unique(begin,end,Equal);
	printf("\nafter unique listp\n");
	end = ListItr_End(listp);
	begin = ListItr_Begin(listp);
	ListItr_ForEach(begin,end,PrintVal,NULL);
	printf("\nafter unique listdst\n");
	end = ListItr_End(listDst);
	begin = ListItr_Begin(listDst);
	ListItr_ForEach(begin,end,PrintVal,NULL);
	List_Destroy(&listp,NULL);
	List_Destroy(&listDst,NULL);
	PrintResult(res , "\nTest_ListItr_Unique");
}

int main()
{
				

	/*List Func tests*/
	printf("List Func tests:\n");
	Test_ListItr_FindFirst();
	Test_ListItr_CountIf();
	Test_ListItr_ForEach();
	Test_ListItr_Sort();
	Test_ListItr_Splice();
	Test_ListItr_Merge();
	Test_ListItr_Cut();
	Test_ListItr_Unique();

	return 0;
	
}










