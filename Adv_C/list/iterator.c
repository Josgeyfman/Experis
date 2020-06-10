#include"iterator.h"
#include<stdlib.h>
#include<string.h>
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead
#define IS_VALID(t) (t && t->magicNum==MAGIC_NUM)

ListItr ListItr_Begin(const List* _list)
{
	if(!IS_VALID(_list))
	{
		return NULL
	}
	return (ListItr) _list.m_head->m_next;
}

ListItr ListItr_End(const List* _list)
{
	if(!IS_VALID(_list))
	{
		return NULL;
	}
	return (ListItr) _list.m_tail->m_prev;
}

int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	if(!_a || !_b)
	{
		return NULL;
	}
	return (_a ==_b);
}

ListItr ListItr_Next(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return _itr->m_next;
}

ListItr ListItr_Prev(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return _itr->m_prev;
}

void* ListItr_Get(ListItr _itr)
{
	if(!_itr)
	{
		return NULL;
	}
	return _itr->m_element;
}

void* ListItr_Set(ListItr _itr, void* _element)
{
	if(!_itr)
	{
		return NULL;
	}
	void* retElement =_itr->m_element;
	_itr->m_element= _element;
	return retElement;
}

ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	
	if(!_itr || !_element)
	{
		return NULL;
	}
	
	_itr->m_prev->m_next =_element;
	_element->m_prev = _itr->m_prev->m_next;
	_itr->m_prev= _element;
	_element->m_next=_itr;
	return _element;
}

void* ListItr_Remove(ListItr _itr)
{
	void* element;
	if(!_itr)
	{
		return NULL;
	}
	tmpNode = _itr;
	_itr->m_prev->m_next = _itr->next;
	_itr->m_prev=NULL;
	_itr->m_next=NULL;
	element = _itr->m_element;
	free(_itr);
	return  element;
}


static ERRCODE  CreateNode(node** _newNode,void* _element)
{
	 	*_newNode = (node*)malloc(sizeof(node));
		if(!_newNode)
		{
			return ERR_MEM_ALLOC;
		}
		(*_newNode)->m_element = _element;
		(*_newNode)->m_magicNum = MAGIC_NUM;
		return ERR_SUCCESS;

}







