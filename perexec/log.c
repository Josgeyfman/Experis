#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "log.h"

static FILE* logfp;

ERRCODE OpenLog(const char* _fname)
{
	logfp = fopen(_fname,"a+");
	if(!logfp)
	{
		return ERR_FILE_OPEN;
	}
	return ERR_SUCCESS;

}

void Log(const char* _file,int _line,const char* _func,Trace _trace,const char* _message)
{
	time_t ltime; /* calendar time */
	char* trace = (_trace==0) ? "Error" : "Info" ;
	if(!_file || !_func || !_message)
	{
		return;
	}
	ltime=time(NULL); /* get current cal time */
	fprintf(logfp,"current time:%s pid:%ld file:%s line:%d func:%s trace:%s message:%s\n"
					,asctime(localtime(&ltime)),(long)getpid(),_file,_line,_func,trace,_message);
	fflush(logfp);
	
}

ERRCODE CloseLog()
{
	if(!fclose(logfp))
	{
		return ERR_SUCCESS;
	}
	return ERR_FILE_CLOSE;
}
