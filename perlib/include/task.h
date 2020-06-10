#ifndef __TASK_H__
#define __TASK_H__
#include "adt_error.h" /*ERRCODE*/

typedef struct Task Task;

/** 
 * @brief Create a task structure.  
 * @param[in] _taskFunction - a funtction for the task to preform
 * @param[in] _context - Element to for task to be preformed on.
 * @param[in] _period_ms - period time interval to be preformed.
 * @param[in] _clk_id - a clock_t for actual run time calculation.
 * @return a pointer to a Task on success or Null otherwise 
 */
Task* Task_Create(int (*_taskFunction)(void *),void* _context,size_t _period_ms,clockid_t _clk_id);

/**  
 * @brief Destroy a task.  
 * @param[in] _task - a  pointer to the task tobe destroyed
 */
void Task_Destroy(void* _task);

/**  
 * @brief preform a task function on it's context.  
 * @param[in] _task - a  pointer to the task .
 * @return >0 if task is not finshed yet , 0 otherwise
 */
int Task_Run(Task* _task);

/**
 * @brief compare 2 task by their run time  
 * @param[in] _task1 - a  pointer to  task1
 * @param[in] _task1 - a  pointer to  task2
 * @return true if task1 runtime is smaller then task 2 ,false otherwise
*/
int Task_Cmp(const void* _task1,const void* _task2);

/**
 * @brief calculate and set a new run time for a task
 * @param[in] _task - a  pointer to  task1
 * @return ERR_SUCCESS if succeeded ,ERR_ILLEGAL_INPUT otherwise   
*/
ERRCODE Task_ResetRunTime(Task* _task);

#endif /*__TASK_H__*/
