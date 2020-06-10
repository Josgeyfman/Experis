#include<stdio.h>
#include "queue.h"

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

void TestCreateQueue_Nsize()
{
	Result res;	
	queuep qp = QueueCreate(rand()/10);
	if(qp)
	{
		res = SUCCESS;
		QueueDestroy(qp);
	}
	else
	{
		res = FAILED;
		
	}
	PrintResult(res , "TestCreateQueue_Nsize");
}

void TestCreateQueue_size0()
{
	Result res;	
	queuep qp = QueueCreate(0);
	if(!qp)
	{
		res = SUCCESS;
		
	}
	else
	{
		res = FAILED;
		QueueDestroy(qp);
		
	}
	PrintResult(res , "TestCreateQueue_size0");
}

void TestCreateQueue_sizeHUGE()
{
	Result res;	
	queuep qp = QueueCreate(rand()/1000);
	if(qp)
	{
		res = SUCCESS;
		QueueDestroy(qp);
	}
	else
	{
		res = FAILED;
		
	}
	PrintResult(res , "TestCreateQueue_sizeHUGE");
}




void TestDestroyQueue()
{
	Result res = SUCCESS;	
	queuep qp = QueueCreate(rand());
	QueueDestroy(qp);
	PrintResult(res ,"TestDestroyQueue");
}

void TestDoubleDestroyQueue()
{
	Result res = SUCCESS;	
	queuep qp = QueueCreate(rand());
	QueueDestroy(qp);
	QueueDestroy(qp);
	PrintResult(res ,"TestDoubleDestroyQueue");
}

void TestDestroyQueueNull()
{
	Result res;	
	queuep qp = NULL;
	QueueDestroy(qp);
	if(!qp)
	{
		res = SUCCESS;
	}
	else
	{
		res = FAILED;
	}
	PrintResult(res ,"TestDestroyQueueNull");
}

void TestAddValidQueue()
{
	#define SIZE 10
	int arr[SIZE],i,data;
	Result res = SUCCESS;
	queuep qp = QueueCreate(SIZE);

	for(i=0; i < SIZE-1 ;i++)
	{
		arr[i]=rand();
		QueueEnqueue(qp,arr[i]);
	}
	
	for(i=0; i < SIZE-1; i++)
	{
		QueueDequeue(qp,&data);
		if(arr[i] != data)
		{
			printf("%d!=%d i=%d\n",arr[i],data,i);
			res = FAILED;
		}
		
	}	
	QueueDestroy(qp);
	PrintResult(res ,"TestAddValidQueue");
}

void TestAddNotVAlidQueue()
{
	#define SIZE 10
	int i;
	Result res = SUCCESS;
	queuep qp = QueueCreate(SIZE);

	for(i=0; i < 2*SIZE-1 ;i++)
	{
		QueueEnqueue(qp,rand());
	}
	
	if(QueueNumOfElements(qp)!=SIZE)
	{
		res=FAILED;	
	}
	QueueDestroy(qp);
	PrintResult(res ,"TestAddValidQueue");
}

void TestRemoveValidQueue()
{
	#define SIZE 10
	int i,data;
	Result res = SUCCESS;
	queuep qp = QueueCreate(SIZE);

	for(i=0; i < SIZE-1 ;i++)
	{
		QueueEnqueue(qp,rand());
	}
	
	for(i=0; i < SIZE-1; i++)
	{
		QueueDequeue(qp,&data);
		
		
	}
	if(!QueueIsEmpty(qp))
	{
			res = FAILED;
	}	
	QueueDestroy(qp);
	PrintResult(res ,"TestRemoveValidQueue");
}

void TestRemoveNotValidQueue()
{
	#define SIZE 10
	int arr[SIZE],i,data;
	Result res = SUCCESS;
	queuep qp = QueueCreate(SIZE);

	for(i=0; i < SIZE-1 ;i++)
	{
		QueueEnqueue(qp,arr[i]);
	}
	
	for(i=0; i < 2*SIZE-1; i++)
	{
		QueueDequeue(qp,&data);
		
		
	}
	if(!QueueIsEmpty(qp))
	{
			res = FAILED;
	}	
	QueueDestroy(qp);
	PrintResult(res ,"TestRemoveValidQueue");
}

int main()
{

	TestCreateQueue_Nsize();

	TestCreateQueue_size0();

	TestCreateQueue_sizeHUGE();

	TestDestroyQueue();

	TestDoubleDestroyQueue();
	
	TestDestroyQueueNull();

	TestAddValidQueue();

	TestAddNotVAlidQueue();

	TestRemoveValidQueue();

	TestRemoveNotValidQueue();



	return 0;
	
}










