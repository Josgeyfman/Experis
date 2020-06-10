#ifndef _LIST_P_
#define _LIST_P_
#include<stdio.h>
#define MAX_LEN 50

typedef enum{START,MID,END} Place;

typedef struct Person person;

/*
	Description: allocate a List Person node with given id,name,age/
	input: _id   - the id of person (PK)
	       _name - the name of person 	
	       _age - the name of _age 
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
person* CreateNewPerson(size_t _id,char*  _name,size_t _age);

/*
	Description: allocate a List Person node with given id,name,age/
	input: _id   - the id of person (PK)
	       _name - the name of person 	
	       _age - the name of _age 
	output: pointer to allocted ad_t ,NULL otherwise
*/ 
void GetPersonData(size_t* _id,char*  _name,size_t* _age);

/*
	Description: insert a Person to the list head/
	input: _head   - List head Pointer
	       _toInsert - pointer to person node to  be iserted	
	output: pointer to list head
*/ 
person*  ListInsertHead(person* _head,person* _toInsert);

/*
	Description: Remove a Person node from the list head/
	input: _head   - List head Pointer
	       _item - pointer to person node to  be removed	
	output: pointer to list head
*/ 
person*  ListRemoveHead(person* _head,person** _item);

/*
	Description: insert a Person node to a specific index if it not exists yet
	input: _head   - List head Pointer
	       _p - pointer to person node to  be iserted	
	      _key - the index to place to indert
	output: pointer to list head with the new node if succeeded , pointer to regular list  otherwisee
*/
person* ListInsertByKey(person* _head, size_t _key, person* _p);

/*
	Description: insert a Person node to a specific index if it not exists yet recursivly
	input: _head   - List head Pointer
	       _p - pointer to person node to  be iserted	
	      _key - the index to place to indert
	output: pointer to list head with the new node if succeeded , pointer to regular list  otherwisee
*/
person* ListInsertByKeyRec(person* _head, size_t _key, person* _p);

/*
	Description: remove a Person node from the list if it  exists 
	input: _head   - List head Pointer
	       _p - pointer to person node to  be iserted	
	      _key - the index to place to indert
	output: pointer to list head without the node if succeeded , pointer to regular list  otherwisee
*/
person* ListRemoveByKey(person* _head, size_t _key, person* *_p);

/*
	Description: remove a Person node from the list if it  exists recursivly
	input: _head   - List head Pointer
	       _p - pointer to person node to  be iserted	
	      _key - the index to place to indert
	output: pointer to list head without the node if succeeded , pointer to regular list  otherwisee
*/
person* ListRemoveByKeyRec(person* _head, size_t _key, person**_p);

/*print functions for debug*/

void PrintPerson(person* _curr);

void ListPrint(person* _head);

/*
	for user debug & testing
	retrieve person id (PK)
	input: _head   - List head Pointer
	output: the person id if exists, 0 otherwise
*/
size_t GetPersonId(person* _curr);

/*
	for user debug & testing
	check if list is sorted by id (PK)
	input: _head  - List head Pointer
	output: the person id if exists, 0 otherwise
*/
int IsListSorted(person* _head);

/*
	Description: destroy all list nodes
	input: _head   - List head Pointer
	output: 1 if sorted, 0 if not ,-1 if no list is found
*/
void ListDestroy(person* _head);

/*
	Description: destroy all list nodes
	input: _head   - List head Pointer
	output: 1 if sorted, 0 if not ,-1 if no list is found
*/
void ListDestroyRec(person* _head);

#endif
