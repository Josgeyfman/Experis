#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "adt_error.h"
#include<stdlib.h>
#include <stdio.h>


typedef struct Vector vector;

typedef vector * vectorp;


/*
	Description: allocate a vector with given size and block size
	input: _initialSize - the size of diary to be allocated
	       _blockSize   - block size when resizing diary	 	
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
vectorp VectorCreate(size_t _initialSize,size_t _blockSize);

/*
	Description: free vector
	input: adPtr - pointer to an ad_t
*/
void VectorDestroy(vectorp _vecPtr);

/*
	Description: get number of elemnts
	output: number of elements if they exist, 0 otherwise
*/
size_t VectorNumOfElements(vectorp _vec);

/*
	Description: insert a new value to the vector tail
	input: _vecp	 - pointer to a vector
	       _data	 - value to be added
	output: ERR_SUCCESS if added, ERRCODE otherwise
*/
ERRCODE VectorAddTail(vectorp _vecp ,int _data);

/*
	Description: remove a value from the vector tail
	input: _vecp	- pointer to an ad_t
	       _data 	- pointer to removed value
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE VectorRemoveTail(vectorp _vecp ,int* _data);

/*
	Description: insert a new value in specific index
	input: _vecp	 - pointer to a vector
	       _data	 - value to be added
	      _index	 - the index 
	output: ERR_SUCCESS if set, ERRCODE otherwise
*/
ERRCODE VectorSet(vectorp _vecp ,size_t _index ,int _data);

/*
	Description: retrieve a  value of a specific index
	input: _vecp	 - pointer to a vector
	       _data	 - pointer to value 
	      _index	 - the index 
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE VectorGet(vectorp _vecp ,size_t _index ,int* _data);


/*
	Description: Print Vector data and all it's elements debuging
	input: _vecp	 - pointer to a vector
	output: number of element printed
*/	
int VectorPrint(vectorp _vecPtr);

/*
	Description: Print error code string for debuging
	input: _err - error index
	
*/
void PrintERRCODE(ERRCODE _err);

#endif /*end of _VECTOR_H_*/

