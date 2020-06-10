#ifndef __TASK_H__
#define __TASK_H__

typedef struct Task Task;


/*
	Create a task
*/
Task* Task_Create(int (*_taskFunction)(void *),void* _context,long _period_ms);

void Task_Destroy(Task** _task);

int Task_Run(Task* _task);

int Task_Cmp(const void* _task1,const void* _task2);

#endif /*__TASK_H__*/
