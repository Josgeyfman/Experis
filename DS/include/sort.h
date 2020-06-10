#ifndef _SORT_H_
#define _SORT_H_
#include"adt_error.h" /*errors*/
#include"vector.h"
#include"stack.h"
#define DEBUG 1


/*
	description : build a Max heap from a given vector
	input: _vec - a pointer to a vector
	output: a pointer to Max heap if succeeded , null otherwise
	complexity: O(n)
*/
void BubbleSort(vector* _vec); 

/*
	description : destroy the heap
	input: _heap - a pointer to a heap
	complexity: O(1)
*/
void ShakeSort(vector* _vec); 

/**/
void QuickSortRec(vector* _vec,int _low,int _high); 

void QuickSort(vector* _vec,int _low,int _high); 

void InsertionSort(vector* _vec,int _start,int _gap);

void ShellSort(vector* _vec);

void SelectionSort(vector* _vec);

#endif /*_SORT_H_*/
 
