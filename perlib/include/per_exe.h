#ifndef __PER_EXE_H__
#define __PER_EXE_H__
#include <time.h> /*clockid_t*/

typedef struct PeriodicExecutor PeriodicExecutor;


/** 
 * @brief Create a periodic executor that will measure time using given clock.
 * @param[in] _name - name of log file.
 * @param[in] _clk_id - Clockid_t specify the id of the system clock to be used. CLOCK_REALTIME,
 *			CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s supported by the underlying system.
 * @return a pointer to a Task on success or Null otherwise 
 */
PeriodicExecutor* PeriodicExecutor_Create(const char* _name,clockid_t _clk_id);


/** 
 * @brief Destroy previously created executor. Cleaning all allocated memory and resources.
 * @param[in] _executor - a pointer to PeriodicExecutor to be destriyed
 */
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);


/** 
 * @brief Create and add a task to executor.
 * @param[in] _executor - a pointer to PeriodicExecutor
 * @param[in] _taskFunction - a funtction for the task to preform
 * @param[in] _context - Element to for task to be preformed on.
 * @param[in] _period_ms - period time interval to be preformed. 
 * @return true on success ,false otherwise
 */
int PeriodicExecutor_Add(PeriodicExecutor* _executor,int (*_taskFunction)(void *),void* _context,size_t _period_ms);


/** 
 * @brief Start running the tasks previously added to the executor or resume a previously paused Executor.
 * @param[in] _executor - a pointer to PeriodicExecutor
 *  
 * @return This function returns the number of execution cycles (user task function calls) performed.
 */
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);


/** 
 * @brief Pause the execution of the executor. If a task is currently being executed then pause after
 *  	it has completed the current cycle.
 * @param[in] _executor - a pointer to PeriodicExecutor
 *  
 * @return This function returns the number of tasks remaining inside the executor.
 *		The paused executor can be resumed later on by calling PeriodicExecutor_Run API.
 */
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);

#endif /*__PER_EXE_H__*/
