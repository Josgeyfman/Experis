#ifndef _MAX_HEAP_H_
#define _MAX_HEAP_H_
#include"adt_error.h" /*errors*/
#include"vector.h"   /*container*/

#define DEBUG 1

typedef struct Heap Heap;

typedef Heap heap;

/*
	description : build a Max heap from a given vector
	input: _vec - a pointer to a vector
	output: a pointer to Max heap if succeeded , null otherwise
	complexity: O(n)
*/
Heap* HeapBuild(vector* _vec); 

/*
	description : destroy the heap
	input: _heap - a pointer to a heap
	complexity: O(1)
*/
void HeapDestroy(Heap* _heap);

/*
	description : insert a new value to the heap
	input: _heap - a pointer to a heap
	      _data - the new value
	output: ERR_SUCCESS succeeded , ERRCODE otherwise
	complexity: O(log n)
*/
ERRCODE HeapInsert(Heap* _heap, int _data); /* O(log n) */

/*
	description : retrieve the max from the heap
	input: _heap - a pointer to a heap
	      _data - a pointer to max value value
	output: ERR_SUCCESS succeeded , ERRCODE otherwise
	complexity: O(1)
*/
ERRCODE HeapMax(Heap* _heap, int* _data);

/*
	description : remove the max from the heap
	input: _heap - a pointer to a heap
	      _data - a pointer to max value value
	output: ERR_SUCCESS if succeeded , ERRCODE otherwise
	complexity: O(log n)
*/
ERRCODE HeapExtractMax(Heap* _heap, int* _data); 

/*
	description : retrieve the number of items from the heap
	input: _heap - a pointer to a heap
	output: the number of items if succeeded , 0 otherwise
	complexity: O(1)
*/
size_t HeapItemsNum(Heap* _heap);

/*
	description : print the heap for debug (DEBUG = 1 will pretty print)
	input: _heap - a pointer to a heap
	complexity: O(n)
*/
void HeapPrint(Heap* _heap); 

#endif /*_HEAP_H_*/
 
