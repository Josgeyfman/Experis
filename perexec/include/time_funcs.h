#ifndef __TIME_FUNCS_H__
#define __TIME_FUNCS_H__
#include <sys/time.h>   /*clockid_t*/
#include <sys/types.h>  /*struct timespec*/

/**
 * @brief retreive a timspec of a given clock
 * @param[in] _clk_id - a given clockid_t 
 * @return timespec of currnet clock
*/
struct timespec GetClockTime(clockid_t _clk_id);

/**
 * @brief calculate time difference between a given clock and a given timespec
 * @param[in] _clockTime - a given timespec of current clocktime
 * @param[in] _time - a  given timespec 
 * @return timespec of calculated time difference
*/
struct timespec GetTimeDiff(struct timespec _clockTime, struct timespec _runtime);

/**
 * @brief calculate next time by adding time interval to a current clock 
 * @param[in] _clockTime - a given timespec of current clocktime
 * @param[in] _perTime - a  given periodictime in milliseconds
 * @return timespec of the calculated time.
*/
struct timespec CalcNextTime(struct timespec _clockTime,size_t _perTime);


/**
 * @brief compare 2 timespecs  
 * @param[in] _task1 - a  pointer to  task1
 * @param[in] _task1 - a  pointer to  task2
 * @return true if ts  is smaller then ts 2 ,false otherwise
*/
int Time_Cmp(struct timespec _ts1 ,struct timespec _ts2 );

#endif /*__TIME_FUNCS_H__*/
