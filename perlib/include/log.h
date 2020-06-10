#ifndef _LOG_H_
#define _LOG_H_
#include "adt_error.h"
#include "string.h"
#define CLOG(t,m) { Log(__FILE__,__LINE__,__func__,t,m); }


typedef enum {ERROR,INFO} Trace;

ERRCODE OpenLog(const char* _fname);

void Log(const char* _file,int _line,const char* _func,Trace _trace,const char* _message);

ERRCODE CloseLog();

#endif /*_LOG_H_*/
