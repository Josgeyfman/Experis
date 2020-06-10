#define SUCCESS 0
#define ERR_OVERFLOW -1
#define ERR_UNDERFLOW -2
#define ERR_ILLEGAL_INPUT -3

/*
	Description: print _arr elements up to size
	input: size - num of elements	, _arr  -pointer to array
*/
int PrintPtrArr(int* _arr,int _size);

/*
	Description: allocate an array with given size
	input: size - num of elements	
	output: pointer to allocted array ,NULL otherwise
*/
int * DynamicArrayCreate(int _size);

/*
	Description: frees allocated array
	input: _DynaminArrayPtr  - pointer to array
*/
void DynamicArrayDestroy( int  *_DynaminArrayPtr);

/*
	Description:  reallocates given array
	input: _newSize - the new size to reallocte,
	       _arr     - pointer to array
	output: pointer to reallocted array ,NULL otherwise
*/
int * ResizeArr(int* _arr,int _newSize);

/*
	Description:  inserts new element to  the array, increases array size if needed
	input: _DynaminArrayPtr - pointer to array
	       _data            - value to be added
	       _DaSize          - size of array
	       _DaNumOfElements - num of elements in array
	       _IncBlockSize    - the size to increase by
	output: SUCCESS if succeeded ,ERR_OVERFLOW otherwise
*/
int DynamicArrayInsert(int ** _DynaminArrayPtr, int _data, int* _DaSize, int* _DaNumOfElements, int _IncBlockSize);

/*
	Description:  deletes the last element from the given array.
	input: _DynaminArrayPtr - pointer to array
	       _data            - pointer to stored deleted data
	       _DaNumOfElements - num of elements in array
	output: SUCCESS if succeeded ,ERR_UNDERFLOW otherwise
*/
int DynamicArrayDelete(int  *_DynaminArrayPtr, int* data, int* _DaNumOfElements);
