#ifndef _FILESHW2_H_
#define _FILESHW2_H_
#define MAX_LINE 50
#include "adt_error.h"

/*
	print word instances of

*/
ERRCODE PrintWordInstances(char _fname[]);

/**/
ERRCODE PrintLetterInstanceNum(char _fname[]);

/**/
ERRCODE CountWordInstancesinFile(char _fname[]);

#endif /*_FILESHW2_H_*/
