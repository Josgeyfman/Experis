#ifndef __PER_EXE_H__
#define __PER_EXE_H__
#include <time.h> /*clockid_t*/

typedef struct PeriodicExecutor PeriodicExecutor;

/*
Create a periodic executor that will measure time using given clock.
Clockid_t specify the id of the system clock to be used. CLOCK_REALTIME,
CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s
supported by the underlying system.
*/
PeriodicExecutor* PeriodicExecutor_Create(const char* _name,clockid_t _clk_id);

/*
Destroy previously created executor. Cleaning all allocated memory and resources.
*/
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);

/*
_taskFunction is represented by a user provided function pointer. The task is called with
_context as the only parameter
_period_ms is the period of recurrence in milliseconds.
*/

int PeriodicExecutor_Add(PeriodicExecutor* _executor,int (*_taskFunction)(void *),void* _context,size_t _period_ms);

/*
Start running the tasks previously added to the executor or resume a previously paused
Executor.
This function will return in one of two cases:

1. The tasks were executed to completion.
2. The executor was paused

This function returns the number of execution cycles (user task function calls) performed.
*/
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);

/*
Pause the execution of the executor. If a task is currently being executed then pause after
it has completed the current cycle.
This function returns the number of tasks remaining inside the executor.
The paused executor can be resumed later on by calling PeriodicExecutor_Run API.
*/
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);


#endif /*__PER_EXE_H__*/
