#ifndef _DLL_H_
#define _DLL_H_

#include<stdio.h>  /*for size_t*/
#include"adt_error.h"

typedef struct Node Node;

typedef struct Node node;

typedef struct List List;

typedef struct List list;

/*
	Description: allocate a List structure/
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
list*	 ListCreate(void);

/*
	Description: destroy all list nodes and List struct
	input: _list - List  Pointer
*/
void     ListDestroy(list* _list);

/*
	Description: Push new node to head of the list
	input: _list - List  Pointer
	       _data - the data of the new node
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE  ListPushHead(list* _list, int _data);

/*
	Description: Push new node to tail of the list
	input: _list - List  Pointer
	       _data - the data of the new node
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE  ListPushTail(list* _list, int _data);


/*
	Description: Pop  node from head of the list
	input: _list - List  Pointer
	       _data - Pointer to the data of the removed node
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE  ListPopHead(List* _list, int* _data);

/*
	Description: Pop  node from tail of the list
	input: _list - List  Pointer
	       _data - Pointer to the data of the removed node
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE  ListPopTail(List* _list, int* _data);

/*
	Description: Count number of nodes in the list
	input: _list - List  Pointer
	output: number of nodes if succeeded, 0 otherwise
*/
size_t   ListCountItems(List* _list);

/*
	Description: check if list is empty
	input: _list - List  Pointer
	output: 1 if empty, 0 otherwise
*/
int      ListIsEmpty(List* _list);

/* ListPrint is only for debug */
void     ListPrint(List* _list);

#endif /*_DLL_H_*/
