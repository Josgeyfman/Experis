#include <stdio.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/time.h> 
#include "per_exe.h"
#define MILLIS 1000
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
	/*printf("counting down %d\n",(*(int*)_num));*/
	return !((*(int*)_num)--);
}  

int countUp(void* _num)
{
	/*printf("counting up %d\n",(*(int*)_num));*/
	return !((*(int*)_num)++);
}

int TestPause(void* _exe)
{
	PeriodicExecutor* pexec  = (PeriodicExecutor*)_exe;
	PeriodicExecutor_Pause(pexec);
	return 1 ;
}

void PeriodicExecutor_Create_Valid()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	if(!pexec)
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Create_Valid");
}

void PeriodicExecutor_Create_NotValid()
{
	Result res = FAILED; 
	clockid_t clk_id = CLOCK_REALTIME;
	PeriodicExecutor* pexec = PeriodicExecutor_Create(NULL,clk_id);
	if(!pexec)
	{
		res = SUCCESS;
	}
	PrintResult(res,"PeriodicExecutor_Create_NotValid");
}

void PeriodicExecutor_Destroy_Valid()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Destroy_Valid");
}

void PeriodicExecutor_Destroy_Null()
{
	Result res = SUCCESS; 
	PeriodicExecutor* pexec = NULL;
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Destroy_Null");
}

void PeriodicExecutor_Destroy_Double()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	PeriodicExecutor_Destroy(pexec);
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Destroy_Double");
}

void PeriodicExecutor_Add_Valid()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	int num = 10 ,num2 = -16;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	if(!PeriodicExecutor_Add(pexec,countDown,(void*)&num,3*MILLIS))
	{
		res = FAILED;
	}
	if(!PeriodicExecutor_Add(pexec,countUp,(void*)&num2,5*MILLIS))
	{
		res = FAILED;
	}
	if(!PeriodicExecutor_Add(pexec,TestPause,(void*)&pexec,7*MILLIS))
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Add_Valid");
}

void PeriodicExecutor_Add_Null()
{
	Result res = SUCCESS; 
	int num = 10;
	if(PeriodicExecutor_Add(NULL,countDown,(void*)&num,3))
	{
		res = FAILED;
	}
	
	PrintResult(res,"PeriodicExecutor_Add_Null");
}

void PeriodicExecutor_Add_Null_Func()
{
	Result res = SUCCESS; 
	int num = 10;
	clockid_t clk_id = CLOCK_REALTIME;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	if(PeriodicExecutor_Add(pexec,NULL,(void*)&num,3))
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Add_Null_Func");
}

void PeriodicExecutor_Run_Valid()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	int num = 1 ,num2 = -2;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	PeriodicExecutor_Add(pexec,countDown,(void*)&num,1*MILLIS);
	PeriodicExecutor_Add(pexec,countUp,(void*)&num2,2*MILLIS);
	if(PeriodicExecutor_Run(pexec)!=5)
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Run_Valid");
}

void PeriodicExecutor_Run_Null()
{
	Result res = SUCCESS; 
	if(PeriodicExecutor_Run(NULL))
	{
		res = FAILED;
	}
	PrintResult(res,"PeriodicExecutor_Run_Null");
}

void PeriodicExecutor_Pause_Valid()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	int num = 1 ,num2 = -2;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	PeriodicExecutor_Add(pexec,countDown,(void*)&num,1*MILLIS);
	PeriodicExecutor_Add(pexec,countUp,(void*)&num2,2*MILLIS);
	PeriodicExecutor_Add(pexec,TestPause,(void*)pexec,3*MILLIS);
	if(PeriodicExecutor_Run(pexec)!=4)
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Pause_Valid");
}

void PeriodicExecutor_Pause_Resume()
{
	Result res = SUCCESS; 
	clockid_t clk_id = CLOCK_REALTIME;
	int num = 1 ,num2 = -2;
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexecTestUnit.log",clk_id);
	PeriodicExecutor_Add(pexec,countDown,(void*)&num,1*MILLIS);
	PeriodicExecutor_Add(pexec,countUp,(void*)&num2,2*MILLIS);
	PeriodicExecutor_Add(pexec,TestPause,(void*)pexec,3*MILLIS);
	PeriodicExecutor_Run(pexec);
	if(PeriodicExecutor_Run(pexec)!=2)  /*resumed*/
	{
		res = FAILED;
	}
	PeriodicExecutor_Destroy(pexec);
	PrintResult(res,"PeriodicExecutor_Pause_Resume");
}

void PeriodicExecutor_Pause_Null()
{
	Result res = SUCCESS; 
	if(PeriodicExecutor_Pause(NULL))
	{
		res = FAILED;
	}
	PrintResult(res,"PeriodicExecutor_Pause_Null");
}

int main()
{
				

	/*Periodic executer  Create & Destroy  tests*/
	printf("Create & Destroy tests:\n");
	PeriodicExecutor_Create_Valid();
	PeriodicExecutor_Create_NotValid();

	printf("\nDestroy tests:\n");
	PeriodicExecutor_Destroy_Valid();
	PeriodicExecutor_Destroy_Null();
	PeriodicExecutor_Destroy_Double();

	/*Periodic executer Add tests*/
	printf("\nAdd  tests:\n");
	PeriodicExecutor_Add_Valid();
	PeriodicExecutor_Add_Null();
	PeriodicExecutor_Add_Null_Func();

	/*Periodic executer Run tests*/
	printf("\nRun  tests:\n");
	PeriodicExecutor_Run_Valid();
	PeriodicExecutor_Run_Null();

	/*Periodic executer Run tests*/
	printf("\nPause  tests:\n");
	PeriodicExecutor_Pause_Valid();
	PeriodicExecutor_Pause_Null();
	PeriodicExecutor_Pause_Resume();

	return 0;
	
}










