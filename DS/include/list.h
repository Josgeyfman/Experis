#ifndef _LIST_H_
#define _LIST_H_

#include "adt_error.h"
#include<stdlib.h>
#include <stdio.h>
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

typedef struct List list;

typedef listp * list;


/*
	Description: allocate a vector with given size and block size
	input: _initialSize - the size of diary to be allocated
	       _blockSize   - block size when resizing diary	 	
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
listp ListCreate(size_t _initialSize,size_t _blockSize);

/*
	Description: free vector
	input: adPtr - pointer to an ad_t
*/
void ListDestroy(listp _list);

/*
	Description: get number of elemnts
	output: number of elements if they exist, 0 otherwise
*/
size_t ListNumOfElements(listp _list);

/*
	Description: insert a new value to the vector tail
	input: _vecp	 - pointer to a vector
	       _data	 - value to be added
	output: ERR_SUCCESS if added, ERRCODE otherwise
*/
ERRCODE ListAdd(listp _list ,int _data);

/*
	Description: remove a value from the vector tail
	input: _vecp	- pointer to an ad_t
	       _data 	- pointer to removed value
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE ListRemove(listp _list,int* _data);

/*
	Description: insert a new value in specific index
	input: _vecp	 - pointer to a vector
	       _data	 - value to be added
	      _index	 - the index 
	output: ERR_SUCCESS if set, ERRCODE otherwise
*/
ERRCODE ListFind(listp _list,int _data);

/*
	Description: retrieve a  value of a specific index
	input: _vecp	 - pointer to a vector
	       _data	 - pointer to value 
	      _index	 - the index 
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE ListGet(listp _list,size_t _index ,int* _data);


/*
	Description: Print Vector data and all it's elements debuging
	input: _vecp	 - pointer to a vector
	output: number of element printed
*/	
int ListPrint(listp _list);

/*
	Description: Print error code string for debuging
	input: _err - error index
	
*/
void PrintERRCODE(ERRCODE _err);

#endif /*end of _LIST_H_*/

