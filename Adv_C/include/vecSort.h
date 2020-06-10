#ifndef _VECTOR_SORT_H_
#define _VECTOR_SORT_H_
#include"adt_error.h" /*ERRCODE*/

typedef bool (*fcp)(void*,void*);

/*
	description: bubble sort vector with given comperator function
	input: 	_vec - a pointer to vector
	   	_compareF- pointer to comperator function
	output: ERR_SUCCESS if succeeded,null otherwise
*/
ERRCODE BubbleSort(vector* _vec , fcp _compareF);


#endif /*_VECTOR_SORT_H_*/
