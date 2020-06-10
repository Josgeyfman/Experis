#include <stdio.h>	
#include "time_funcs.h"

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

void CalcNextTime_Valid()
{
	Result res = FAILED; 
	clockid_t clk = 0;
	struct timespec next,curr;
	curr = GetClockTime(clk);
	next = CalcNextTime(curr,5000);
	if(curr.tv_sec + 5 ==next.tv_sec)
	{
		res = SUCCESS;
	}
	PrintResult(res,"CalcNextTime_Valid");
}

void GetTimeDiff_Valid()
{
	Result res = FAILED; 
	clockid_t clk = 0;
	struct timespec next,curr,ts;
	curr = GetClockTime(clk);
	next = CalcNextTime(curr,5000);
	ts  = GetTimeDiff(curr,next);
	printf("%ld",ts.tv_sec);
	if(ts.tv_sec>=5)
	{
		res = SUCCESS;
	}
	PrintResult(res,"GetTimeDiff_Valid");
}


void Time_Cmp_Valid()
{
	Result res = FAILED; 
	clockid_t clk = 0;
	struct timespec next,curr;
	curr = GetClockTime(clk);
	next = CalcNextTime(curr,5000);
	if(Time_Cmp(curr,next))
	{
		res = SUCCESS;
	}
	PrintResult(res,"Task_Cmp_Valid");
}








int main()
{
	/*GetTimeDiff tests*/
	printf("GetTimeDiff tests:\n");
	GetTimeDiff_Valid();

	/*CalcNextTime tests*/
	printf("\nCalcNextTime tests:\n");
	CalcNextTime_Valid();
	
	/*Time Cmp tests*/
	printf("\nTime Cmp  tests:\n");
	Time_Cmp_Valid();
	return 0;
	
}










