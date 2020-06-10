#ifndef _VECTOR_H_
#define _VECTOR_H_
#include"adt_error.h" /*ERRCODE*/
#include<stdlib.h> /*size_t*/

typedef struct Vector vector;

typedef vector * vectorp;

typedef void (*FreeFunction)( void *_elem );

typedef int (*ActionFunction)(const void *_elem, void * _context);

/*
	Description: allocate a vector with given size and block size
	input: _initialSize - the size of diary to be allocated
	       _blockSize   - block size when resizing diary	 	
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
vectorp VectorCreate(size_t _initialSize,size_t _blockSize);

/*
	Description: free vector
	input: _vecPtr - pointer to an adt vector
	      _printF  - pointer to destroy function of element
*/
void VectorDestroy(vectorp _vecPtr,FreeFunction _desF);

/*
	Description: get number of elemnts
	output: number of elements if they exist, 0 otherwise
*/
size_t VectorNumOfElements(const vectorp _vec);

/*
	Description: insert a new value to the vector tail
	input: _vecp	 - pointer to a vector
	       _element	 - a pointer to data to be added ,data can't be NULL
	output: ERR_SUCCESS if added, ERR_ILLEGAL_INPUT or ERR_MEM_ALLOC otherwise.
*/
ERRCODE VectorAddTail(vectorp _vecp ,void* _element);

/*
	Description: remove a value from the vector tail
	input: _vecp	- pointer to an ad_t
	       _element	 - a pointer to a pointer of data to be removed
	output: ERR_SUCCESS if removed, ERR_ILLEGAL_INPUT otherwise.
*/
ERRCODE VectorRemoveTail(vectorp _vecp ,void** _element);

/*
	Description: insert a new value in specific index
	input: _vecp	 - pointer to a vector
	        _element	 - a pointer to data to be added
	      _index	 - the index 
	output: ERR_SUCCESS if set, ERR_ILLEGAL_INPUT or ERR_WRONG_INDEX otherwise.
*/
ERRCODE VectorSet(vectorp _vecp ,size_t _index ,void* _element);

/*
	Description: retrieve a  value of a specific index
	input: _vecp	 - pointer to a vector
	       _element	 - a pointer to a pointer of data to be retrieved ,data can't be NULL
	      _index	 - the index 
	output: ERR_SUCCESS if succeeded, ERR_ILLEGAL_INPUT or ERR_WRONG_INDEX otherwise.
*/
ERRCODE VectorGet(const vectorp _vecp ,size_t _index ,void** _element);


/**  
 * @brief Iterate over all elements  in the heap from top to bottom.
 * @details The user provided ActionFunction _act will be called for each element.  
 * @param[in] _heap - Heap to iterate over.
 * @param[in] _act - User provided function pointer to be onvoked for each element
 * @returns number of times the user functions was invoked
 */
size_t Vector_ForEach(const vector* _vecp, ActionFunction _act, void* _context);

/*
	Description: Print Vector data and all it's elements debuging
	input: _vecp	 - pointer to a vector
	       _printF  - pointer to print function
	output: number of element printed
*/	
void VectorPrint(const vectorp _vecPtr ,ActionFunction _printF);

/*
	Description: Print error code string for debuging
	input: _err - error index
	
*/
void PrintERRCODE(ERRCODE _err);

#endif /*end of _VECTOR_H_*/

