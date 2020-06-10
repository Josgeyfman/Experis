#include <sys/types.h>    /*struct timespec*/
#include <sys/time.h>    /*clockid_t*/
#include <time.h> 	/*clock_gettime*/
#include "time_funcs.h"
#define MAX_CLOCKS 11
#define MILLIS 1000
#define NANOS 1000000
#define NANOSLONG 1000000000L

struct timespec GetClockTime(clockid_t _clk_id)
{
	struct timespec ts ={0,0};
	if( _clk_id >= MAX_CLOCKS)
	{
		return ts;
	}
	clock_gettime(_clk_id,&ts);
	return ts;
}

struct timespec CalcNextTime(struct timespec _clockTime,size_t _perTime)
{
	struct timespec nextTime;
	nextTime.tv_sec = _clockTime.tv_sec +(_perTime / MILLIS);
    	nextTime.tv_nsec = _clockTime.tv_nsec + ((_perTime % MILLIS)* NANOS);
	return nextTime;
}

struct timespec GetTimeDiff(struct timespec _clockTime, struct timespec _runtime)
{
	struct timespec diffTime ={0,0};

	if ((_runtime.tv_nsec - _clockTime.tv_nsec) < 0)
	{
		diffTime.tv_sec =  _runtime.tv_sec - _clockTime.tv_sec - 1;
		diffTime.tv_nsec = _runtime.tv_nsec - _clockTime.tv_nsec + NANOSLONG;
	}
	else 
	{
		diffTime.tv_sec = _runtime.tv_sec - _clockTime.tv_sec;
		diffTime.tv_nsec = _runtime.tv_nsec - _clockTime.tv_nsec;
	}
	if(diffTime.tv_sec < 0 || diffTime.tv_nsec < 0)
	{
		diffTime.tv_sec = 0;
		diffTime.tv_nsec = 0;
	}
	return diffTime;
}

int Time_Cmp(struct timespec _ts1 ,struct timespec _ts2 )
{
	if(_ts1.tv_sec == _ts2.tv_sec)
	{
		return (_ts1.tv_nsec <  _ts2.tv_nsec);
	}
	return (_ts1.tv_sec < _ts2.tv_sec);
}
