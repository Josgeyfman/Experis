#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/time.h> 
#include "task.h"
#include "time_funcs.h"
#include "adt_error.h"

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

int countDown(void* _num)
{
	return (*(int*)_num)-- ;
}  

void Task_Create_Valid()
{
	Result res = SUCCESS; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	if(!task)
	{
		res = FAILED;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Create_Valid");
}

void Task_Create_Null_Func()
{
	Result res = SUCCESS; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(NULL,(void*)&num,5,clk);
	if(task)
	{
		res = FAILED;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Create_Null_Func");
}

void Task_Destroy_Valid()
{
	Result res = SUCCESS; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Destroy_Valid");
}

void Task_Destroy_Double()
{
	Result res = SUCCESS; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	Task_Destroy((void*)task);
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Destroy_Double");
}

void Task_Destroy_Null()
{
	Result res = SUCCESS; 
	Task_Destroy(NULL);
	PrintResult(res,"Task_Destroy_Null");
}

void Task_Run_Valid()
{
	Result res = SUCCESS; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	if(!Task_Run(task))
	{
		res = FAILED;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Run_Valid");
}

void Task_Run_Null()
{
	Result res = SUCCESS; 
	if(Task_Run(NULL))
	{
		res = FAILED;
	}
	PrintResult(res,"Task_Run_Null");
}

void Task_Cmp_Valid()
{
	Result res = FAILED; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	Task* task1 =  Task_Create(countDown,(void*)&num,6,clk);
	if(Task_Cmp(task,task1))
	{
		res = SUCCESS;
	}
	Task_Destroy((void*)task);
	Task_Destroy((void*)task1);
	PrintResult(res,"Task_Cmp_Valid");
}

void Task_Cmp_Null_Left()
{
	Result res = FAILED; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	if(!Task_Cmp(NULL,task))
	{
		res = SUCCESS;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Cmp_Null_Left");
}

void Task_Cmp_Null_Right()
{
	Result res = FAILED; 
	int num =5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	if(!Task_Cmp(task,NULL))
	{
		res = SUCCESS;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_Cmp_Null_Right");
}

void Task_Cmp_Null()
{
	Result res = FAILED; 
	if(!Task_Cmp(NULL,NULL))
	{
		res = SUCCESS;
	}
	PrintResult(res,"Task_Cmp_Null");
}

void Task_ResetRunTime_Valid()
{
	Result res = FAILED; 
	int num = 5;
	clockid_t clk = 0;
	Task* task =  Task_Create(countDown,(void*)&num,5,clk);
	if(Task_ResetRunTime(task)==ERR_SUCCESS)
	{
		res = SUCCESS;
	}
	Task_Destroy((void*)task);
	PrintResult(res,"Task_ResetRunTime_Valid");
}

void Task_ResetRunTime_Null()
{
	Result res = FAILED; 
	if(Task_ResetRunTime(NULL)==ERR_ILLEGAL_INPUT)
	{
		res = SUCCESS;
	}
	PrintResult(res,"Task_ResetRunTime_Null");
}

int main()
{
	/*Task Create tests*/
	printf("Create tests:\n");
	Task_Create_Valid();
	Task_Create_Null_Func();

	printf("\nDestroy tests:\n");
	Task_Destroy_Valid();
	Task_Destroy_Null();
	Task_Destroy_Double();

	/*Task Run tests*/
	printf("\nRun  tests:\n");
	Task_Run_Valid();
	Task_Run_Null();

	/*Task Cmp tests*/
	printf("\nCmp  tests:\n");
	Task_Cmp_Valid();
	Task_Cmp_Null_Left();
	Task_Cmp_Null_Right();
	Task_Cmp_Null();


	/*SetRunTime*/
	printf("\nSetRunTime  tests:\n");
	Task_ResetRunTime_Valid();
	Task_ResetRunTime_Null();

	return 0;
	
}










