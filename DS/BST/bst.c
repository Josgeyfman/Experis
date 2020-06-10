#include<stdio.h> 	
#include<stdlib.h>	/*allocation*/
#include"bst.h"
#define MAGIC_NUM 0xdaeddead
#define NOT_MAGIC_NUM 0xdaedbeaf
#define IS_VALID(t) (t && t->magicNum==MAGIC_NUM)

/*-------------------structures---------------------*/

struct Node
{
	int data;
	Node* left;
	Node* right;
	Node* parent;
};

struct Tree
{
	Node* root;
	size_t magicNum;
};

/*-------------------static fuction signatures------------------*/

static ERRCODE NodeInsert(node* _root,node* _leaf);
static void NodeDestroy(node* _root);
static node* CreateLeaf(int _data);
static int IsNodeFound(node* _root,int _data);
static void InPrint(node* _root);
static void PostPrint(node* _root);
static void PrePrint(node* _root);
static int IsFull(node* _root);
static int GetHighet(node* _root);
static int AreNodesSimilar(node* _root1,node* _root2);
static int IsNodePerfect(node* _root);
static node* MirrorNodes(node* _root);
static void PrettyPrint(node* _p, int _indent);

/*-------------------API fuctions--------------------*/

tree* TreeCreate()
{
	tree* _tree = (tree*)malloc(sizeof(tree));
	if(!_tree)
	{
		return NULL;
	}
	_tree->magicNum = MAGIC_NUM;
	return _tree;
}

void TreeDestroy(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return;
	}
	if(!_tree->root)
	{
		_tree->magicNum = NOT_MAGIC_NUM;
		free(_tree);
		_tree = NULL;
		return;
	}
	NodeDestroy(_tree->root);
	_tree->magicNum = NOT_MAGIC_NUM;
	free(_tree);
	_tree =NULL;	
}

ERRCODE TreeInsert(tree* _tree,int _data)
{
	node* leaf=NULL;	
	if(!IS_VALID(_tree))
	{
		return ERR_ILLEGAL_INPUT;
	}
	if(TreeIsDataFound(_tree,_data))
	{
		return ERR_EXISTS;
	}
	leaf = CreateLeaf(_data);
	if(!leaf)
	{
		return ERR_MEM_ALLOC;
	}
	if(!_tree->root)
	{
		_tree->root = leaf;
		leaf->parent = NULL;
		return ERR_SUCCESS;
	}
	return NodeInsert(_tree->root,leaf);
}

int TreeIsDataFound(tree* _tree,int _data)
{
	if(!IS_VALID(_tree))
	{
		return -1;
	}
	return IsNodeFound(_tree->root,_data);		
}

void TreePrint(tree* _tree,TreeTraverse _mode)
{
	if(!IS_VALID(_tree))
	{
		return;
	}
	switch(_mode)
	{
		case IN_ORDER: 	  printf("In oreder:  "); InPrint(_tree->root); break;
		case POST_ORDER:  printf("Post oreder:"); PostPrint(_tree->root); break;
		case PRE_ORDER:   printf("Pre oreder: "); PrePrint(_tree->root); break;
	}
	printf("\n");

}

int TreeIsFull(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return -1;
	}
	if(!_tree->root)
	{
		return 1;
	}
	return IsFull(_tree->root);
}

int TreeLevel(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return -1;
	}
	if(!_tree->root)
	{
		return -1;
	}
	return GetHighet(_tree->root);
}

int TreesAreSimilar(tree* _tree1,tree* _tree2)
{
	if(!IS_VALID(_tree1) || !IS_VALID(_tree2))
	{
		return -1;
	}
	if(!_tree1->root && !_tree2->root)
	{
		return 1;
	}
	if((!_tree1->root && _tree2->root) || (_tree1->root && !_tree2->root))
	{
		return 0;
	}
	return AreNodesSimilar(_tree1->root,_tree2->root);
}

int TreeIsPerfect(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return -1;
	}
	if(!_tree->root)
	{
		return 1;
	}
	return IsNodePerfect(_tree->root);
}

tree* TreeMirror(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return NULL;
	}
	if(!_tree->root)
	{
		return _tree;
	}
	_tree->root = MirrorNodes(_tree->root);
	return _tree;
}

void TreePrettyPrint(tree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return;
	}
	if(!_tree->root)
	{
		return;
	}
	PrettyPrint(_tree->root,0);
}

/*-------------------static fuctions------------------*/

static void PrettyPrint(node* _p, int _indent)
{
	int i;
	if(_p != NULL) 
	{
	 	PrettyPrint(_p->right, _indent+4);
		for(i=0;i<_indent;i++)
		{
			printf(" ");
		}
		printf("%d\n",_p->data);
		PrettyPrint(_p->left, _indent+4);
	}
}

static node* MirrorNodes(node* _root)
{
	node* tmp ;
	if(!_root)
	{
		return NULL;
	}
	tmp = _root->left;
	_root->left = _root->right;
	_root->right = tmp;
	MirrorNodes(_root->left);
	MirrorNodes(_root->right);
	return _root;
}

static int IsNodePerfect(node* _root)
{
	int left,right,diff;
	if(!_root || (_root->left && !_root->right))
	{
		return 1;
	}
	if(!_root->left && _root->right)
	{
		return 0;
	}

	left = GetHighet(_root->left);
	right = GetHighet(_root->right);
	diff = left-right;
	printf("data%d diif:%d left%d right%d\n",_root->data,diff,left,right);
	if(diff<0 || diff>2)
	{
		return 0;
	}
	if(IsNodePerfect(_root->left))
	{
		return IsNodePerfect(_root->right);
	}
	return 0;
}

static int AreNodesSimilar(node* _root1,node* _root2)
{
	if(!_root1 && !_root2)
	{
		return 1;
	}
	if((_root1 && !_root2) || (!_root1 && _root2))
	{
		return 0;
	}
	if(_root1->data!=_root2->data)
	{
		return 0;
	}
	if(AreNodesSimilar(_root1->left,_root2->left))
	{
		return AreNodesSimilar(_root1->right,_root2->right);
	}
	return 0;
}

static int GetHighet(node* _root)
{
	int left,right;	
	if(!_root)
	{
		return -1;
	}
	left = GetHighet(_root->left);
	right = GetHighet(_root->right);
	return (left>right) ? left + 1 : right + 1 ;

}

static int IsFull(node* _root)
{
	if((!_root->left && _root->right) || (!_root->right && _root->left))
	{
		return 0;
	}
	else if (!_root->left && !_root->right)
	{
		return 1;
	}
	if(IsFull(_root->left))
	{
		return IsFull(_root->right);
	}
	return 0;
}

static void NodeDestroy(node* _root)
{
	if(!_root)
	{
		return;
	}
	NodeDestroy(_root->left);
	NodeDestroy(_root->right);
	free(_root);
	_root=NULL;
}

static node* CreateLeaf(int _data)
{
	node* leaf = (node*)malloc(sizeof(node));
	if(!leaf)
	{
		return leaf;
	}
	leaf->data = _data;
	leaf->left = NULL;
	leaf->right = NULL;
	return leaf;
}

static ERRCODE NodeInsert(node* _root,node* _leaf)
{
	if(!_root->left && _root->data>_leaf->data)
	{
		_root->left = _leaf;
		_leaf->parent =_root;
		return ERR_SUCCESS;
	}
	else if(!_root->right && _root->data<_leaf->data)
	{
		_root->right=_leaf;
		_leaf->parent=_root;
		return ERR_SUCCESS;
	}
	if(_root->data>_leaf->data)
	{
		return  NodeInsert(_root->left,_leaf);
	}
	return NodeInsert(_root->right,_leaf);
}

static int IsNodeFound(node* _root,int _data)
{
	if(!_root)
	{
		return 0;
	}
	if(_root->data==_data)
	{
		return 1;
	}
	
	if(_root->data>_data)
	{
		return IsNodeFound(_root->left,_data);	
	}
	return IsNodeFound(_root->right,_data);
}

static void InPrint(node* _root)
{
	if(!_root)
	{
		return;
	}
	InPrint(_root->left);
	printf("%d " ,_root->data);
	InPrint(_root->right);

}

static void PostPrint(node* _root)
{
	if(!_root)
	{
		return;
	}
	PostPrint(_root->left);
	PostPrint(_root->right);
	printf("%d " ,_root->data);

}

static void PrePrint(node* _root)
{
	if(!_root)
	{
		return;
	}
	printf("%d " ,_root->data);
	PrePrint(_root->left);
	PrePrint(_root->right);
}

