#include<stdio.h>
#include "listp.h"
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


void TestListInsertHead_Vaild()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertHead(head,p);
	head=ListInsertHead(head,p1);
	if(head==p1)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "TestListInsertHead_Vaild");
}

void TestListInsertHead_Null()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	head = ListInsertHead(head,p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListInsertHead_Null");
}

void TestListInsertHead_Empty()
{
	Result res;
	person* head = NULL;	
	person* p =  CreateNewPerson(1,"test",1);
	head = ListInsertHead(head,p);
	if(head)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		ListDestroy(p);
	}
	PrintResult(res , "TestListInsertHead_Empty");
}

void TestListInsertHead_DoubleInsert()
{
	Result res;
	person* head = NULL;	
	person* p =  CreateNewPerson(1,"test",1);
	person* p1 =  CreateNewPerson(2,"test",2);
	head = ListInsertHead(head,p);
	head = ListInsertHead(head,p1);
	head = ListRemoveHead(head,&p1);
	if(head==p)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "TestListInsertHead_DoubleInsert");
}

void TestListInsertHead_HugeInsert()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = 0;i<HUGE_LEN;i++)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertHead(head,p);
	}
	i = HUGE_LEN;
	while(i > 0)
	{
		head = ListRemoveHead(head,&p);
		free(p);
		if(!head)
		{
			break;
		}
		i--;
	}
	if(!head && i>0)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "TestListInsertHead_HugeInsert");
}

void TestListRemoveHead_Vaild()
{
	Result res;
	person* head = NULL;	
	person* p =  CreateNewPerson(1,"test",1);
	person* p1 =  CreateNewPerson(2,"test",2);
	head = p;
	head = ListInsertHead(head,p1);
	head = ListRemoveHead(head,&p1);
	if(head)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "TestListRemoveHead_Vaild");
}

void TestListRemoveHead_Null()
{
	Result res;
	person* head = NULL;	
	person* p =  CreateNewPerson(1,"test",1);
	head = p;
	head = ListRemoveHead(head,NULL);
	if(!head)
	{
		res = SUCCESS;
		free(p);
	}
	else
	{
		res = FAILED;
		free(p);
	}
	PrintResult(res , "TestListRemoveHead_Null");
}

void TestListRemoveHead_Empty()
{
	Result res;
	person* head = NULL;	
	person* p;
	head = ListRemoveHead(head,&p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "TestListRemoveHead_Empty");
}

void TestListRemoveHead_DoubleRemove()
{
	Result res;
	person* head = NULL;	
	person* p =  CreateNewPerson(1,"test",1);
	person* p1 =  CreateNewPerson(2,"test",2);
	head=ListInsertHead(head,p);
	head=ListInsertHead(head,p1);
	head=ListRemoveHead(head,&p1);
	head=ListRemoveHead(head,&p);
	if(!head)
	{
		res = SUCCESS;
		free(p);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "TestListRemoveHead_DoubleRemove");
}

void TestListRemoveHead_HugeRemove()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = 0;i<HUGE_LEN;i++)
	{
		p =  CreateNewPerson(i,"test",1);
		head=ListInsertHead(head,p);
	}
	i = HUGE_LEN;
	while(i > 0)
	{
		head=ListRemoveHead(head,&p);
		free(p);
		if(!head)
		{
		  	break;
		}
		i--;
	}
	if(!head && i>0)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "TestListRemoveHead_HugeRemove");
}

void ListInsertByKey_Vaild()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListInsertByKey_Vaild");
}

void ListInsertByKey_Null()
{
	Result res;
	person* head = NULL;
	size_t id=1;
	person* p =  NULL;
	head=ListInsertByKey(head,id,p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListInsertByKey_Null");
}

void ListInsertByKey_Empty()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p1);
	}
	PrintResult(res , "ListInsertByKey_Empty");
}

void ListInsertByKey_Exists()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head = ListRemoveHead(head,&p1);
	if(!head)
	{
		res = SUCCESS;
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p1);
		
	}
	PrintResult(res , "ListInsertByKey_Exists");
}

void ListInsertByKey_First()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	person* p2 =  CreateNewPerson(0,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	if(GetPersonId(head)==0)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKey_First");
}

void ListInsertByKey_Middle()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	person* p2 =  CreateNewPerson(0,name,age);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	head = ListRemoveHead(head,&p2);
	if(GetPersonId(head)==1)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKey_Middle");
}

void ListInsertByKey_Last()
{
	Result res;
	person* head = NULL;
	size_t age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(0,name,age++);
	person* p1 =  CreateNewPerson(1,name,age);
	person* p2 =  CreateNewPerson(2,name,age);
	
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);

	head = ListRemoveHead(head,&p);
	head = ListRemoveHead(head,&p1);
	if(GetPersonId(head)==2)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKey_Last");
}

void ListInsertByKey_HugeInsert()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKey(head,i,p);
	}

	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListInsertByKey_HugeInsert");
}

void ListInsertByKeyRec_Vaild()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKeyRec(head,GetPersonId(p),p);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListInsertByKeyRec_Vaild");
}

void ListInsertByKeyRec_Null()
{
	Result res;
	person* head = NULL;
	size_t id=1;
	person* p =  NULL;
	head=ListInsertByKeyRec(head,id,p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListInsertByKeyRec_Null");
}

void ListInsertByKeyRec_Empty()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p1);
	}
	PrintResult(res , "ListInsertByKeyRec_Empty");
}

void ListInsertByKeyRec_Exists()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	head = ListRemoveHead(head,&p1);
	if(!head)
	{
		res = SUCCESS;
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p1);
		
	}
	PrintResult(res , "ListInsertByKeyRec_Exists");
}

void ListInsertByKeyRec_First()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	person* p2 =  CreateNewPerson(0,name,age);
	head=ListInsertByKeyRec(head,GetPersonId(p),p);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	head=ListInsertByKeyRec(head,GetPersonId(p2),p2);
	if(GetPersonId(head)==0)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKeyRec_First");
}

void ListInsertByKeyRec_Middle()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p  =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	person* p2 =  CreateNewPerson(0,name,age);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	head=ListInsertByKeyRec(head,GetPersonId(p),p);
	head=ListInsertByKeyRec(head,GetPersonId(p2),p2);
	head = ListRemoveHead(head,&p2);
	if(GetPersonId(head)==1)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKeyRec_Middle");
}



void ListInsertByKeyRec_Last()
{
	Result res;
	person* head = NULL;
	size_t age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(0,name,age++);
	person* p1 =  CreateNewPerson(1,name,age);
	person* p2 =  CreateNewPerson(2,name,age);
	
	head=ListInsertByKeyRec(head,GetPersonId(p),p);
	head=ListInsertByKeyRec(head,GetPersonId(p1),p1);
	head=ListInsertByKeyRec(head,GetPersonId(p2),p2);

	head = ListRemoveHead(head,&p);
	head = ListRemoveHead(head,&p1);
	if(GetPersonId(head)==2)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListInsertByKeyRec_Last");
}

void ListInsertByKeyRec_HugeInsert()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKeyRec(head,i,p);
	}

	if(IsListSorted(head))
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListInsertByKeyRec_HugeInsert");
}

void ListRemoveByKey_Vaild()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListRemoveByKey(head,2,&p);
	head=ListRemoveByKey(head,1,&p1);
	if(!head && GetPersonId(p1) == 1 && GetPersonId(p) == 2)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListRemoveByKey_Vaild");
}

void ListRemoveByKeyRec_Vaild()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListRemoveByKeyRec(head,2,&p);
	head=ListRemoveByKeyRec(head,1,&p1);
	if(!head && GetPersonId(p1) == 1 && GetPersonId(p) == 2)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListRemoveByKeyRec_Vaild");
}

void ListRemoveByKey_Null()
{
	Result res;
	person* head = NULL;
	person* p =  NULL;
	head=ListRemoveByKey(head,1,&p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListRemoveByKey_Null");
}

void ListRemoveByKeyRec_Null()
{
	Result res;
	person* head = NULL;
	person* p =  NULL;
	head=ListRemoveByKeyRec(head,1,&p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListRemoveByKeyRec_Null");
}

void ListRemoveByKey_Empty()
{
	Result res;
	person* head = NULL;
	person* p =  NULL;
	head=ListRemoveByKey(head,1,&p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListRemoveByKey_Empty");
}

void ListRemoveByKeyRec_Empty()
{
	Result res;
	person* head = NULL;
	person* p =  NULL;
	head=ListRemoveByKeyRec(head,1,&p);
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "ListRemoveByKeyRec_Empty");
}

void ListRemoveByKey_NotExists()
{
	Result res;
	person* head = CreateNewPerson(2,"test",2);
	person* p =  NULL;
	head=ListRemoveByKey(head,1,&p);
	if(head && !p)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListRemoveByKey_NotExists");
}

void ListRemoveByKeyRec_NotExists()
{
	Result res;
	person* head = CreateNewPerson(2,"test",2);
	person* p =  NULL;
	head=ListRemoveByKeyRec(head,1,&p);
	if(head && !p)
	{
		res = SUCCESS;
		ListDestroy(head);
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListRemoveByKeyRec_NotExists");
}

void ListRemoveByKey_First()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListRemoveByKey(head,1,&p1);
	if(GetPersonId(head)==2 && GetPersonId(p1) == 1)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListRemoveByKey_First");
}

void ListRemoveByKeyRec_First()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListRemoveByKeyRec(head,1,&p1);
	if(GetPersonId(head)==2 && GetPersonId(p1) == 1)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
	}
	PrintResult(res , "ListRemoveByKeyRec_First");
}

void ListRemoveByKey_Middle()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id++,name,age++);
	person* p2 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	head=ListRemoveByKey(head,2,&p1);
	if(head && GetPersonId(p1) == 2)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListRemoveByKey_Middle");
}

void ListRemoveByKeyRec_Middle()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id++,name,age++);
	person* p2 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	head=ListRemoveByKeyRec(head,2,&p1);
	if(head && GetPersonId(p1) == 2)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p1);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListRemoveByKeyRec_Middle");
}

void ListRemoveByKey_Last()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id++,name,age++);
	person* p2 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	head=ListRemoveByKey(head,3,&p1);
	if(head && GetPersonId(p1) == 3)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p2);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListRemoveByKey_Last");
}

void ListRemoveByKeyRec_Last()
{
	Result res;
	person* head = NULL;
	size_t id=1,age=1;
	char name[] = "test";	
	person* p =  CreateNewPerson(id++,name,age++);
	person* p1 =  CreateNewPerson(id++,name,age++);
	person* p2 =  CreateNewPerson(id,name,age);
	head=ListInsertByKey(head,GetPersonId(p),p);
	head=ListInsertByKey(head,GetPersonId(p1),p1);
	head=ListInsertByKey(head,GetPersonId(p2),p2);
	head=ListRemoveByKeyRec(head,3,&p1);
	if(head && GetPersonId(p1) == 3)
	{
		res = SUCCESS;
		ListDestroy(head);
		free(p2);
	}
	else
	{
		res = FAILED;
		free(p);
		free(p1);
		free(p2);
	}
	PrintResult(res , "ListRemoveByKeyRec_Last");
}

void ListRemoveByKey_HugeRemove()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKey(head,i,p);
	}
	for(i = HUGE_LEN;i>0;i--)
	{
		head = ListRemoveByKey(head,i,&p);
		free(p);
	}
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListRemoveByKey_HugeRemove");
}

void ListRemoveByKeyRec_HugeRemove()
{
	Result res;
	person* head = NULL;	
	person* p = NULL;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKey(head,i,p);
	}
	for(i = HUGE_LEN;i>0;i--)
	{
		head = ListRemoveByKeyRec(head,i,&p);
		free(p);
	}
	if(!head)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		ListDestroy(head);
	}
	PrintResult(res , "ListRemoveByKeyRec_HugeRemove");
}

void CreateNewPerson_Valid()
{
	Result res;
	person* p =  CreateNewPerson(1,"test",1);
	if(p)
	{
		res = SUCCESS;
		free(p);
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res , "CreateNewPerson_Valid");
}

void CreateNewPerson_NullName()
{
	Result res;
	person* p =  CreateNewPerson(1,NULL,1);
	if(!p)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
		free(p);
	}
	PrintResult(res , "CreateNewPerson_NullName");
}

void ListDestroy_Vaild()
{
	Result res = SUCCESS;
	person* head =  CreateNewPerson(1,"test",1);
	ListDestroy(head);
	PrintResult(res , "ListDestroy_Vaild");
}

void ListDestroy_Null()
{
	Result res = SUCCESS;
	person* head =  NULL;
	ListDestroy(head);
	PrintResult(res , "ListDestroy_Null");
}

void ListDestroy_DuobleDestroy()
{
	Result res = SUCCESS;
	person* head =  CreateNewPerson(1,"test",1);
	ListDestroy(head);
	ListDestroy(head);
	PrintResult(res , "ListDestroy_DuobleDestroy");
}

void ListDestroy_HugeDestroy()
{
	Result res = SUCCESS;
	person* head;
	person* p;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKey(head,i,p);
	}
	ListDestroy(head);
	PrintResult(res , "ListDestroy_HugeDestroy");
}	

void ListDestroyRec_Vaild()
{
	Result res = SUCCESS;
	person* head =  CreateNewPerson(1,"test",1);
	ListDestroyRec(head);
	PrintResult(res , "ListDestroyRec_Vaild");
}

void ListDestroyRec_Null()
{
	Result res = SUCCESS;
	person* head =  NULL;
	ListDestroyRec(head);
	PrintResult(res , "ListDestroyRec");
}

void ListDestroyRec_DuobleDestroy()
{
	Result res = SUCCESS;
	person* head =  CreateNewPerson(1,"test",1);
	ListDestroyRec(head);
	ListDestroyRec(head);
	PrintResult(res , "ListDestroyRec_DuobleDestroy");
}

void ListDestroyRec_HugeDestroy()
{
	Result res = SUCCESS;
	person* head;
	person* p;
	size_t i;
	for(i = HUGE_LEN;i>0;i--)
	{
		p =  CreateNewPerson(i,"test",1);
		head = ListInsertByKey(head,i,p);
	}
	ListDestroyRec(head);
	PrintResult(res , "ListDestroyRec_HugeDestroy");
}

int main()
{
	/*insert head tests*/
	printf("Insert head tests:\n");
	TestListInsertHead_Vaild();
	TestListInsertHead_Null();
	TestListInsertHead_Empty();
	TestListInsertHead_DoubleInsert();
	TestListInsertHead_HugeInsert();
	
	/*remove head tests*/
	printf("\nRemove head tests:\n");
	TestListRemoveHead_Vaild();
	TestListRemoveHead_Null();
	TestListRemoveHead_Empty();
	TestListRemoveHead_DoubleRemove();
	TestListRemoveHead_HugeRemove();

	/*insert by key tests*/
	printf("\nInsert by key tests:\n");
	ListInsertByKey_Vaild();
	ListInsertByKey_Null();
	ListInsertByKey_Empty();
	ListInsertByKey_Exists();
	ListInsertByKey_First();
	ListInsertByKey_Middle();
	ListInsertByKey_Last();
	ListInsertByKey_HugeInsert();   

	/*insert by key tests rec*/
	printf("\nInsert by key rec tests:\n");
	ListInsertByKeyRec_Vaild();
	ListInsertByKeyRec_Null();
	ListInsertByKeyRec_Empty();
	ListInsertByKeyRec_Exists();
	ListInsertByKeyRec_First();
	ListInsertByKeyRec_Middle();
	ListInsertByKeyRec_Last();
	ListInsertByKeyRec_HugeInsert(); 

	/*remove by key tests*/
	printf("\nRemove by key tests:\n");
	ListRemoveByKey_Vaild();
	ListRemoveByKey_Null();
	ListRemoveByKey_Empty();
	ListRemoveByKey_NotExists();
	ListRemoveByKey_First();
	ListRemoveByKey_Middle();
	ListRemoveByKey_Last();
	ListRemoveByKey_HugeRemove();     

	/*remove by key tests rec*/
	printf("\nRemove by key rec tests:\n");
	ListRemoveByKeyRec_Vaild();
	ListRemoveByKeyRec_Null();
	ListRemoveByKeyRec_Empty();
	ListRemoveByKeyRec_NotExists();
	ListRemoveByKeyRec_First();
	ListRemoveByKeyRec_Middle();
	ListRemoveByKeyRec_Last();
	ListRemoveByKeyRec_HugeRemove();   

	printf("\nCreate & destroy tests:\n");
	/*destroy & create tests*/
	CreateNewPerson_Valid();
	CreateNewPerson_NullName();
	ListDestroy_Vaild();
	ListDestroy_Null();
	ListDestroy_DuobleDestroy();
	ListDestroy_HugeDestroy();				
	ListDestroyRec_Vaild();
	ListDestroyRec_Null();
	ListDestroyRec_DuobleDestroy();
	ListDestroyRec_HugeDestroy();

	return 0;
	
}










