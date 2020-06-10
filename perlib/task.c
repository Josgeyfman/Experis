#include <stdlib.h>  	/*allocation*/
#include <time.h>	/*nanosleep*/
#include "task.h"
#include "time_funcs.h"
#define MAGIC_NUM 0xfababafa
#define NOT_MAGIC_NUM 0xfffccccf
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)
#define MAX_CLOCKS 11
#define MILLIS 1000
#define NANOS 1000000

typedef enum{FAIL,FAIL_RUN,SUCCESS} Result;

typedef int (*taskFunction)(void *); 

struct Task 
{
	size_t m_magicNum;
	size_t m_perTime;
	void* m_context;
	taskFunction m_taskF;
	struct timespec m_runTime;
	clockid_t m_clkid;
};


Task* Task_Create(int (*_taskFunction)(void *),void* _context,size_t _period_ms,clockid_t _clk_id)
{
	Task* task;
	struct timespec clockTime;
	if(!_taskFunction || _clk_id >= MAX_CLOCKS)
	{
		return NULL;
	}
	task = (Task*)malloc(sizeof(Task));
	if(!task)
	{
		return task;
	}
	task->m_perTime = _period_ms;	
	clockTime = GetClockTime(_clk_id); 				/*get current clock time*/
	task->m_runTime = CalcNextTime(clockTime,task->m_perTime);
	task->m_context = _context;
	task->m_taskF   = _taskFunction;
	task->m_magicNum = MAGIC_NUM;
	task->m_clkid = _clk_id;
	return task;
}

void Task_Destroy(void* _task)
{
	Task* task = (Task*)_task;
	if(!IS_VALID(task))
	{
		return;
	}
	task->m_magicNum = NOT_MAGIC_NUM;
	free(task);
}

int Task_Run(Task* _task)
{
	struct timespec waitTime;
	if(!IS_VALID(_task))
	{
		return FAIL_RUN;
	}
	waitTime = GetClockTime(_task->m_clkid);		   /*get current clock time*/
	waitTime = GetTimeDiff(waitTime,_task->m_runTime);	   /*calc time difference for next run*/
	nanosleep(&waitTime,NULL); 				   /*wait for next run*/
	return _task->m_taskF(_task->m_context);		   /*run task*/
}

int Task_Cmp(const void* _task1,const void* _task2)
{
	Task* task1 = (Task*) _task1;
	Task* task2 = (Task*) _task2;
	if(!IS_VALID(task1) || !IS_VALID(task2))
	{
		return FAIL;
	}
	return Time_Cmp(task1->m_runTime,task2->m_runTime);
}


ERRCODE Task_ResetRunTime(Task* _task)
{
	struct timespec clockTime;
	if(!IS_VALID(_task))
	{
		return ERR_ILLEGAL_INPUT;
	}
	clockTime = GetClockTime(_task->m_clkid);			/*get current clock time*/
	_task->m_runTime = CalcNextTime(clockTime,_task->m_perTime);   /*calc next run time*/
	return ERR_SUCCESS;
}



