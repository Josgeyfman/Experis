#include <stdlib.h>    /*allocation*/
#include <stdbool.h>    /*bool*/
#include "task.h"      
#include "heap.h"
#include "log.h"
#include "per_exe.h"
#include "time_funcs.h"
#define MAGIC_NUM 0xfabafafa
#define NOT_MAGIC_NUM 0xfcfcfccf
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)
#define VEC_INIT_SIZE 10
#define MAX_CLOCKS 11

typedef enum{FAIL,SUCCESS} Result;

/*---------------------------------------------------Structure-----------------------------------------------*/

struct PeriodicExecutor
{
	size_t m_magicNum; 
	bool m_pause;
	size_t m_cycles;
	clockid_t m_clkid;
	Heap* m_heap;
};

/*---------------------------------------------------API functions-----------------------------------------------*/

PeriodicExecutor* PeriodicExecutor_Create(const char* _name,clockid_t _clk_id)
{
	PeriodicExecutor* pe;
	vector* vec;
	if(!_name || _clk_id >= MAX_CLOCKS)
	{
		return NULL;	
	}
	OpenLog(_name);
	pe = (PeriodicExecutor*)malloc(sizeof(PeriodicExecutor));
	if(!pe)
	{
		CLOG(ERROR,"Periodic Executor alloation fail");
		CloseLog();
		return pe;
	}
	vec = VectorCreate(VEC_INIT_SIZE,VEC_INIT_SIZE);
	if(!vec)
	{
		free(pe);
		CLOG(ERROR,"Vector allocation fail");
		CloseLog();
		return NULL;
	}
	pe->m_heap = Heap_Build(vec,Task_Cmp);
	if(!pe->m_heap)
	{
		free(pe);
		VectorDestroy(vec,NULL);
		CLOG(ERROR,"Heap bulid fail");
		CloseLog();
		return NULL;
	}
	pe->m_clkid = _clk_id;
	pe->m_cycles = 0;
	pe->m_pause = 0;
	pe->m_magicNum = MAGIC_NUM;
	CLOG(INFO,"Create success");
	return pe;
}

void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
	vector* vec;
	if(!IS_VALID(_executor))
	{
		return;
	}
	_executor->m_magicNum = NOT_MAGIC_NUM;
	vec = Heap_Destroy(&_executor->m_heap);
	VectorDestroy(vec,Task_Destroy);
	free(_executor);
	CLOG(INFO,"Destroy success");
	CloseLog();
}

int PeriodicExecutor_Add(PeriodicExecutor* _executor,int (*_taskFunction)(void *),void* _context,size_t _period_ms)
{
	
	Task* newTask = NULL;
	if(!IS_VALID(_executor))
	{
		return FAIL;
	}
	if(!_taskFunction)
	{
		CLOG(ERROR,"Illegal input");
		return FAIL;
	}
	newTask = Task_Create(_taskFunction,_context,_period_ms,_executor->m_clkid);
	if(!newTask)
	{
		CLOG(ERROR,"Task allocation error");
		return FAIL;
	}
	if(HEAP_SUCCESS != Heap_Insert(_executor->m_heap,(void*)newTask))
	{
		CLOG(ERROR,"Task insert error");
		Task_Destroy(&newTask);
		return FAIL;
	}
	CLOG(INFO,"Add task success");
	return SUCCESS;
}

size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
	Task* currTask = NULL;
	if(!IS_VALID(_executor))
	{
		return FAIL;
	}

	_executor->m_pause = 0; 		/*set pause flag to 0 if previously was paused*/
	_executor->m_cycles = 0;		/*set cycles count to 0 if previously was paused*/

	while(Heap_Size(_executor->m_heap)>0 && !_executor->m_pause)
	{
		currTask = (Task*) Heap_Extract(_executor->m_heap); /*get Top task*/
		
		if(!Task_Run(currTask))   			   	/*run task*/
		{
			Task_ResetRunTime(currTask);			 /*reset next run time*/
			Heap_Insert(_executor->m_heap,(void*)currTask);  /*insert back to heap*/
		}
		else
		{
			Task_Destroy(currTask);		/*task completed destroy task*/
		}
		_executor->m_cycles++;			/*count cycles*/
	}
	return _executor->m_cycles;
}

size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{
	if(!IS_VALID(_executor))
	{
		return FAIL;
	}
	_executor->m_pause = 1;
	CLOG(INFO,"pause success");
	return Heap_Size(_executor->m_heap);
}



