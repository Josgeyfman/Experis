#ifndef _BST_H_
#define _BST_H_
#include"adt_error.h" /*errors*/

typedef enum{IN_ORDER,POST_ORDER,PRE_ORDER}TreeTraverse;

typedef struct Node Node;
typedef Node node;

typedef struct Tree Tree;
typedef Tree tree;


/*
	description: Create an empty tree and return a pointer to it.
	output: a pointer to a tree if succeeded , NULL otherwise
	complexity: O(1)
*/
tree* TreeCreate();

/*
	description: Destroy a tree structure and all it's nodes.
	input: _tree  - a pointer to a tree 
	complexity: O(n)
*/
void TreeDestroy(tree* _tree);

/*
	description: insert a new value to the tree .
	input: _tree - a pointer to a tree 
	       _data - the value.
	output: ERR_SUCCESS if succeeded, ERR_ILLEGAL_INPUT if the input is not valid,ERR_EXISTS if already exists
	complexity: O(hight) max hight = n    
*/
ERRCODE TreeInsert(tree* _tree,int _data);

/*
	description: check if a value exists in the tree.
	input: _tree - a pointer to a tree 
	       _data - the value.
	output: 1 if exists, 0 if not ,-1 if bad input
	complexity: O(hight) max hight = n 
*/
int TreeIsDataFound(tree* _tree,int _data);

/*
	description: check if the tree is full.
	input: _tree - a pointer to a tree 
	output: 1 if exists, 0 if not ,-1 if bad input
	complexity: O(n) 
*/
int TreeIsFull(tree* _tree);

/*
	description: get the tree hight
	input: _tree - a pointer to a tree 
	output:the tree hight if exists,-1 if bad input 
	complexity: O(n) 
*/
int TreeLevel(tree* _tree);

/*
	description: check if two trees are identical
	input: _tree1 - a pointer to  tree 1
	       _tree2 - a pointer to  tree 2
	output: 1 if tree are similar,0 if not ,-1 if bad input  
	complexity: O(n) 
*/
int TreesAreSimilar(tree* _tree1,tree* _tree2);

/*
	description: check if the tree is perfect.
	input: _tree - a pointer to a tree 
	output: 1 if perfect, 0 if not ,-1 if bad input
	complexity: O(n) 
*/
int TreeIsPerfect(tree* _tree);

/*
	description: mirror  the tree and return a pointer to mirrored tree.
	input: _tree - a pointer to a tree 
	output: a pointer to mirrored tree if succeeded ,NULL otherwise
	complexity: O(n) 
*/
tree* TreeMirror(tree* _tree);

/*
	description: print tree elements in a given order.
	input: _tree - a pointer to a tree 
	       _mode - the order (in order,pre order,post order)
	complexity: O(n)
*/
void TreePrint(tree* _tree,TreeTraverse _mode);
/*
	description: pretty print tree
	input: _tree - a pointer to a tree 
	complexity: O(n)
*/
void TreePrettyPrint(tree* _tree);

#endif /*_BST_H_*/
 
