#include<stdlib.h> 	/*allocation*/
#include<assert.h> 	/*assert*/
#include"adt_error.h"
#include"bst.h"

#define MAGIC_NUM 0xfefebebe
#define NOT_MAGIC_NUM 0xdaefdead

#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)
#define IS_LEFT_CHILD(t)  (t == t->m_parent->m_left)
#define IS_RIGHT_CHILD(t)  (t == t->m_parent->m_right)

typedef struct Node Node;

struct Node
{
	void*     m_element;
	Node*     m_left;
	Node*     m_right;
	Node*     m_parent;
};

struct BSTree
{
	size_t m_magicNum;
	Node m_root;
	LessComparator m_cmp;
};

/*---------------------------------------static fuction signatures----------------------------------------------*/

static void NodeDestroy(Node* _root,void (*_destroyer)(void*));
static void* FreeNode(Node* _node);
static Node* CreateLeaf(void* _element);
static BSTreeItr NodeInsert(Node* _root,void* _item ,LessComparator _less);
static BSTreeItr Node_FindFirst(Node* _root, PredicateFunction _predicate, void* _context);
static BSTreeItr Node_Begin(Node* _root);
static BSTreeItr Node_End(Node* _root);
static void* ReplaceNode(Node* _old,Node* _new);
static BSTreeItr GetLeftParent(Node* _node);
static BSTreeItr GetRightParent(Node* _node);
static BSTreeItr Node_ForEach_Post(Node* _root ,ActionFunction _action, void* _context);
static BSTreeItr Node_ForEach_In(Node* _root ,ActionFunction _action, void* _context);
static BSTreeItr Node_ForEach_Pre(Node* _root ,ActionFunction _action, void* _context);

/*-----------------------------------------------API fuctions------------------------------------------------*/

BSTree* BSTree_Create(LessComparator _less)
{
	BSTree* tree=NULL;
	
	if(!_less)
	{	
		return tree;
	}
	
	tree = (BSTree*)malloc(sizeof(BSTree));
	if(!tree)
	{	
		return tree;
	}
	tree->m_root.m_left 	= NULL;
	tree->m_root.m_right	= NULL;
	tree->m_root.m_parent	= &tree->m_root;
	tree->m_root.m_element	= NULL;
	
	tree->m_cmp = _less;
	tree->m_magicNum = MAGIC_NUM;
	
	return tree;
}


void  BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void*))
{
	if(!IS_VALID(_tree))
	{
		return;
	}
	if(!_tree->m_root.m_left)
	{
		_tree->m_magicNum = NOT_MAGIC_NUM;
		free(_tree);
		_tree = NULL;
		return;
	}
	NodeDestroy(_tree->m_root.m_left,_destroyer);
	_tree->m_magicNum = NOT_MAGIC_NUM;
	free(_tree);

}

BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	Node* leaf=NULL;	
	if(!IS_VALID(_tree))
	{
		return NULL;
	}
	
	if(!_tree->m_root.m_left)
	{
		leaf = CreateLeaf(_item);
		if(!leaf)
		{
			return NULL;
		}
		_tree->m_root.m_left = leaf;
		leaf->m_parent = &_tree->m_root;
		return _tree->m_root.m_left;
	}
	return NodeInsert(_tree->m_root.m_left,_item,_tree->m_cmp);
}

BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{
	if(!IS_VALID(_tree) || !_predicate)
	{
		return NULL;
	}
	return Node_FindFirst(_tree->m_root.m_left,_predicate,_context);
}

BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return NULL;
	}
	return Node_Begin(_tree->m_root.m_left);

}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(!IS_VALID(_tree))
	{
		return NULL;
	}
	return (BSTreeItr) &_tree->m_root;

}

int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return (_a == _b);
}

BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	Node* it;
	if(!_it)
	{
		return NULL;
	}
	it = ((Node*)_it);
	if(it->m_right)
	{
		return Node_Begin(it->m_right);
	}
	return  GetLeftParent(it);
}

BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	Node* it;
	if(!_it)
	{
		return NULL;
	}
	it = ((Node*)_it);
	if(it->m_left)
	{
		return Node_End(it->m_left);
	}
	return GetRightParent(it);
}


void* BSTreeItr_Remove(BSTreeItr _it)
{
	BSTreeItr curr;
	Node* it = ((Node*)_it);
	if(!_it || _it->m_parent==_it) /*or null or sentinel*/
	{
		return NULL;
	}
	if(!it->m_left && !it->m_right) /*only node in the tree*/
	{
		return FreeNode((Node*)_it);
	}
	if(!it->m_left)
	{
		curr = BSTreeItr_Next(_it);
	}
	else
	{
		curr = BSTreeItr_Prev(_it);
	}
	return ReplaceNode(it,(Node*)curr);
}

void* BSTreeItr_Get(BSTreeItr _it)
{
	if(!_it)
	{
		return NULL;
	}
	return ((Node*)_it)->m_element;
}

BSTreeItr BSTree_ForEach(const BSTree* _tree, BSTreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
	BSTreeItr retNode = NULL;
	if(!IS_VALID(_tree) || !_action)
	{
		return NULL;
	}
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER: retNode = Node_ForEach_Pre(_tree->m_root.m_left,_action,_context); break;

		case BSTREE_TRAVERSAL_INORDER:  retNode = Node_ForEach_In(_tree->m_root.m_left,_action,_context); break;
		
		case BSTREE_TRAVERSAL_POSTORDER: retNode = Node_ForEach_Post(_tree->m_root.m_left,_action,_context); break;
	}
	return retNode;
}



/*-----------------------------------------static fuctions-------------------------------------------------*/


static void NodeDestroy(Node* _root,void (*_destroyer)(void*))
{
	void* element;
	if(!_root)
	{
		return;
	}
	NodeDestroy(_root->m_left,_destroyer);
	NodeDestroy(_root->m_right,_destroyer);
	element = FreeNode(_root);
	if(_destroyer)
	{
		_destroyer(element);
	}
}

static void* FreeNode(Node* _node)
{
	void* element = _node->m_element;
	free(_node);
	return element;
}


static Node* CreateLeaf(void* _element)
{
	Node* leaf = (Node*)malloc(sizeof(Node));
	if(!leaf)
	{
		return leaf;
	}
	leaf->m_element = _element;
	leaf->m_left = NULL;
	leaf->m_right = NULL;
	return leaf;
}

static BSTreeItr NodeInsert(Node* _root,void* _item,LessComparator _less)
{
	Node* leaf = NULL;
	if(!_less(_item,_root->m_element) && !_less(_root->m_element,_item))
	{
		return leaf;  /*Already exists in the tree*/
	}
	if(!_root->m_left && _less(_item,_root->m_element))
	{
		leaf = CreateLeaf(_item);
		if(!leaf)
		{
			return leaf;
		}
		_root->m_left = leaf;
		leaf->m_parent =_root;
		return _root;
	}
	else if(!_root->m_right && _less(_root->m_element,_item))
	{
		leaf = CreateLeaf(_item);
		if(!leaf)
		{
			return leaf;
		}
		_root->m_right=leaf;
		leaf->m_parent=_root;
		return _root;
	}
	if(_less(_item,_root->m_element))
	{
		return NodeInsert(_root->m_left,_item,_less);
	}
	return NodeInsert(_root->m_right,_item,_less);
}


static BSTreeItr Node_FindFirst(Node* _root, PredicateFunction _predicate, void* _context)
{
	BSTreeItr left;
	if(!_root)
	{
		return NULL;
	}

	left = Node_FindFirst(_root->m_left,_predicate,_context);
	if(left)
	{
		return left;
	}

	if(_predicate(_root->m_element,_context))
	{
		return _root;
	}
	return Node_FindFirst(_root->m_right,_predicate,_context);

}

static BSTreeItr Node_Begin(Node* _root)
{
	BSTreeItr leftmost;
	if(!_root)
	{
		return NULL;
	}
	leftmost = Node_Begin(_root->m_left);
	if(leftmost)
	{
		return leftmost;	
	}
	return _root;
}

static BSTreeItr Node_End(Node* _root)
{
	BSTreeItr rightmost;
	if(!_root)
	{
		return NULL;
	}
	rightmost = Node_End(_root->m_right);
	if(rightmost)
	{
		return rightmost;	
	}
	return _root;
}

static void* ReplaceNode(Node* _old,Node* _new)
{
	_new->m_parent = _old->m_parent;
	_new->m_left   = _old->m_left;
	_new->m_right  = _old->m_right;
	if(IS_LEFT_CHILD(_old))
	{
		_old->m_parent->m_left = _new;
	}
	else
	{
		_old->m_parent->m_right = _new;
	}
	return FreeNode(_old);
}

static BSTreeItr Node_ForEach_Pre(Node* _root ,ActionFunction _action, void* _context)
{
	BSTreeItr retNode = NULL;
	if(!_root)
	{
		return NULL;
	}
	if(!_action(_root->m_element,_context))
	{
		return _root;
	}
	retNode = Node_ForEach_Pre(_root->m_left,_action,_context);
	if(retNode)
	{
		return retNode;
	}
	return Node_ForEach_Pre(_root->m_right,_action,_context);
}

static BSTreeItr Node_ForEach_In(Node* _root ,ActionFunction _action, void* _context)
{
	BSTreeItr retNode = NULL;
	if(!_root)
	{
		return NULL;
	}
	retNode = Node_ForEach_Pre(_root->m_left,_action,_context);
	if(retNode)
	{
		return retNode;
	}
	if(!_action(_root->m_element,_context))
	{
		return _root;
	}
	return Node_ForEach_Pre(_root->m_right,_action,_context);
}

static BSTreeItr Node_ForEach_Post(Node* _root ,ActionFunction _action, void* _context)
{
	BSTreeItr retNode = NULL;
	if(!_root)
	{
		return NULL;
	}
	retNode = Node_ForEach_Pre(_root->m_left,_action,_context);
	if(retNode)
	{
		return retNode;
	}
	retNode = Node_ForEach_Pre(_root->m_right,_action,_context);
	if(retNode)
	{
		return retNode;
	}
	if(!_action(_root->m_element,_context))
	{
		return _root;
	}
	return retNode;
}

static BSTreeItr GetRightParent(Node* _node)
{
	while(_node->m_parent!=_node && IS_LEFT_CHILD(_node))
	{
		_node = _node->m_parent;
	}
	return _node->m_parent;
}

static BSTreeItr GetLeftParent(Node* _node)
{
	while(_node->m_parent!=_node && IS_RIGHT_CHILD(_node))
	{
		_node = _node->m_parent;

	}
	return _node->m_parent;
}







