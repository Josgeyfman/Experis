#include <stdio.h>
#include "per_exe.h"
#define MILLIS 1000

int countDown(void* _num)
{
	printf("counting down %d\n",(*(int*)_num));
	return !((*(int*)_num)--) ;
}  

int countUp(void* _num)
{
	printf("counting up %d\n",(*(int*)_num));
	return !((*(int*)_num)++);
}

int PrintId(void* _num)
{
	printf("task id %d\n",(*(int*)_num));
	return !(*(int*)_num);
}

int TestPause(void* _exe)
{
	PeriodicExecutor* pexec  = (PeriodicExecutor*)_exe;
	PeriodicExecutor_Pause(pexec);
	return 1;
}


int main()
{
	int i,num1 =10 ,num2 =-16;
	clockid_t clk_id =  CLOCK_REALTIME;
	int arr[10]  = {1,2,3,4,5,6,7,8,9,10};
	PeriodicExecutor* pexec = PeriodicExecutor_Create("perexec.log",clk_id);
	for(i=0;i<10;i++)
	{
		PeriodicExecutor_Add(pexec,PrintId,(void*)&arr[i],(i+1)*MILLIS);
	}
	PeriodicExecutor_Add(pexec,countDown,(void*)&num1,3*MILLIS);
	PeriodicExecutor_Add(pexec,countUp,(void*)&num2,4*MILLIS);
	PeriodicExecutor_Add(pexec,TestPause,(void*)pexec,20*MILLIS);
	PeriodicExecutor_Run(pexec);
	printf("paused after 20 seconds\n");
	PeriodicExecutor_Destroy(pexec);
	
	return 0;
}


