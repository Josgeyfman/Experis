#include<stdlib.h> /*allocation*/
#include<assert.h> /*assert*/
#include"list.h"
#include"iterator.h"
#include"adt_error.h"
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead
#define IS_VALID(t) (t && t->m_magicNum==MAGIC_NUM)

typedef struct Node Node;

struct Node
{
	void*     m_element;
	Node*     m_next;
	Node*     m_prev;
};

struct List
{
	size_t  m_magicNum;
	Node m_head;
	Node m_tail;
};


/*------------------------static function signatures----------------------*/

static Node* CreateNode(void* _element);
static void* FreeNode(Node* _node);

/*------------------------List API functions ----------------------------------*/

List* List_Create(void)
{
	List* listp = (List*)malloc(sizeof(List));
	if(!listp)
	{
		return listp;
	} 
	listp->m_head.m_prev=NULL;
	listp->m_tail.m_next=NULL;
	listp->m_head.m_next=&listp->m_tail;
	listp->m_tail.m_prev=&listp->m_head;
	listp->m_magicNum = MAGIC_NUM;
	return listp;
}

void List_Destroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	ListItr head,end;
	void* remElement;

	if(!_pList || !IS_VALID((*_pList)))
	{
		return;
	}

 	head =  ListItr_Begin(*_pList);
	end =	ListItr_End(*_pList);

	while(!ListItr_Equals(head,end))
	{
		List_PopHead(*_pList,&remElement);
		if(_elementDestroy)
		{
			_elementDestroy(remElement);	
		}
		head =  ListItr_Begin(*_pList);
	}
	(*_pList)->m_magicNum = NOT_MAGIC_NUM;
	free((*_pList));
	*_pList = NULL;
}


List_Result List_PushHead(List* _list, void* _item)
{
		ListItr head;
		if(!IS_VALID(_list))
		{
			return LIST_UNINITIALIZED_ERROR;
		}
		if(!_item)
		{
			return LIST_NULL_ELEMENT_ERROR;
		}

		head = ListItr_Begin(_list);

		if(!ListItr_InsertBefore(head,_item))
		{
			return LIST_ALLOCATION_ERROR;
		}

		return LIST_SUCCESS;
}

List_Result List_PushTail(List* _list, void* _item)
{
		ListItr tail;
		if(!IS_VALID(_list))
		{
			return LIST_UNINITIALIZED_ERROR;
		}
	
		if(!_item)
		{
			return LIST_NULL_ELEMENT_ERROR;
		}
	
		tail = ListItr_End(_list);

		if(!ListItr_InsertBefore(tail,_item))
		{
			return LIST_ALLOCATION_ERROR;
		}
	
		return LIST_SUCCESS;
}


List_Result List_PopHead(List* _list, void** _pItem)
{
		ListItr head;
		if(!IS_VALID(_list))
		{
			return LIST_UNINITIALIZED_ERROR;
		}

		head = ListItr_Begin(_list);

		if(ListItr_Equals(head,ListItr_End(_list)))
		{
				return LIST_NULL_ELEMENT_ERROR;
		}

		*_pItem = ListItr_Remove(head);
		return LIST_SUCCESS;
}

List_Result List_PopTail(List* _list, void** _pItem)
{
		ListItr tail;
	
		if(!IS_VALID(_list))
		{
			return LIST_UNINITIALIZED_ERROR;
		}
	
		tail = ListItr_End(_list);
		
		if(ListItr_Equals(ListItr_Begin(_list),tail))
		{
				return LIST_NULL_ELEMENT_ERROR;
		}
		tail = ListItr_Prev(tail);		
		*_pItem = ListItr_Remove(tail);
		return LIST_SUCCESS;
}

size_t List_Size(const List* _list)
{
	ListItr curr,end;
	size_t count = 0;
	if(!IS_VALID(_list))
	{
		return count;
	}
	curr =  ListItr_Begin(_list);
	end =	ListItr_End(_list);
	while(!ListItr_Equals(curr,end))
	{
		curr = ListItr_Next(curr);
		count++;
	}
	return count;
}

void List_ForEach(List* listp, actionFunction _action, void* _context)
{
	ListItr curr = ListItr_Begin(listp);
	ListItr end = ListItr_End(listp);
	if(!_action)
	{
		return;
	}
	while(!ListItr_Equals(curr,end))
	{
		_action(ListItr_Get(curr),_context);
		curr = ListItr_Next(curr);
	}
	return;
}

/*------------------------Iterator API functions --------------------------*/

ListItr ListItr_Begin(const List* _list)
{
	if(!IS_VALID(_list))
	{
		return NULL;
	}
	return (ListItr) _list->m_head.m_next;
}

ListItr ListItr_End(const List* _list)
{
	if(!IS_VALID(_list))
	{
		return NULL;
	}
	return (ListItr) &_list->m_tail;
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return (_a == _b);
}

ListItr ListItr_Next(ListItr _itr)
{
	return ((Node*)_itr)->m_next;
}

ListItr ListItr_Prev(ListItr _itr)
{
	return ((Node*)_itr)->m_prev;
}

void* ListItr_Get(ListItr _itr)
{
	return ((Node*)_itr)->m_element;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	void* retElement;
	retElement = ((Node*)_itr)->m_element;
	((Node*)_itr)->m_element= _element;
	return retElement;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node* node = (Node*) _itr;
	Node* newNode = CreateNode(_element);	
	if(!newNode)
	{
		NULL;
	}
	node->m_prev->m_next =newNode;
	newNode->m_prev = node->m_prev;
	node->m_prev = newNode;
	newNode->m_next = node;
	return newNode;
}

void* ListItr_Remove(ListItr _itr)
{
	Node* remNode = (Node*) _itr;
	
	remNode->m_prev->m_next = remNode->m_next;
	remNode->m_next->m_prev = remNode->m_prev;
	remNode->m_prev=NULL;
	remNode->m_next=NULL;
	return FreeNode((Node*)_itr);
}


/*------------------------static  functions --------------------------*/

static Node* CreateNode(void* _element)
{
	Node* _newNode;
	assert(_element);
 	_newNode = (Node*)malloc(sizeof(Node));
	if(!_newNode)
	{
		return NULL;
	}
	_newNode->m_element = _element;
	return _newNode;
}

static void* FreeNode(Node* _node)
{
	void* retElement;
	assert(_node);
	retElement = _node->m_element;
	free(_node);
	return retElement;
}





