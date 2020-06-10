#include"dllist.h"
#include<stdlib.h>
#include<string.h>
#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

struct Node
{
	int       data;
	size_t  magicNum;
	Node*     next;
	Node*     prev;
};

struct List
{
	Node head;
	Node tail;
	size_t  magicNum;
};

static size_t IsValid(list* _p)
{
	if(_p && _p->magicNum==MAGIC_NUM)
	{
		return 1;
	}
	return 0;
}

list*   ListCreate(void)
{
	list* listp = (list*)malloc(sizeof(list));
	if(!listp)
	{
		return listp;
	} 
	listp->head.prev=NULL;
	listp->tail.next=NULL;
	listp->head.next=&listp->tail;
	listp->tail.prev=&listp->head;
	listp->magicNum = MAGIC_NUM;
	return listp;
}

void    ListDestroy(list* _list)
{
	node* tmp;
	if(!IsValid(_list))
	{
		return;
	}
	while(_list->head.next!=&_list->tail)
	{
		tmp = _list->head.next->next;
		_list->head.next->magicNum = NOT_MAGIC_NUM;
		free(_list->head.next);
		_list->head.next=tmp;
	}
	_list->magicNum = NOT_MAGIC_NUM;
	free(_list);
}

ERRCODE  CreateNode(node** _newNode,int _data)
{
	 	*_newNode = (node*)malloc(sizeof(node));
		if(!_newNode)
		{
			return ERR_MEM_ALLOC;
		}
		(*_newNode)->data = _data;
		(*_newNode)->magicNum = MAGIC_NUM;
		return ERR_SUCCESS;

}

static void PushToList(node* _currNode , node* _nextNode)
{
		_currNode->next = _nextNode;
		_nextNode->prev->next = _currNode;
		_currNode->prev = _nextNode->prev;
		_nextNode->prev =_currNode;
}

ERRCODE     ListPushHead(list* _list, int _data)
{
		ERRCODE res;
		node* newNode;
		if(!IsValid(_list))
		{
			return ERR_ILLEGAL_INPUT;
		}
		res = CreateNode(&newNode,_data);
		if(res!=ERR_SUCCESS)
		{
			return res;
		}
		PushToList(newNode,_list->head.next);
		return res;
}

ERRCODE     ListPushTail(list* _list, int _data)
{
		ERRCODE res;
		node* newNode;
		if(!IsValid(_list))
		{
			return ERR_ILLEGAL_INPUT;
		}
		res = CreateNode(&newNode,_data);
		if(res!=ERR_SUCCESS)
		{
			return res;
		}
		PushToList(newNode,&_list->tail);
		return res;
	
}

static void PopFromList(node* _rem ,int* _data)
{
	_rem->prev->next = _rem->next;
	_rem->next->prev = _rem->prev;
	*_data = _rem ->data;
	_rem->magicNum = NOT_MAGIC_NUM;
	free(_rem);
}

ERRCODE     ListPopHead(list* _list, int* _data)
{
		node* toRomve;
		if(!IsValid(_list) || !_data)
		{
			return ERR_ILLEGAL_INPUT;
		}
		if(ListIsEmpty(_list))
		{
			return ERR_EMPTY;
		}
		toRomve = _list->head.next;
		PopFromList(toRomve,_data);
		return ERR_SUCCESS;
}

ERRCODE     ListPopTail(List* _list, int* _data)
{
		node* toRomve;
		if(!IsValid(_list) || !_data)
		{
			return ERR_ILLEGAL_INPUT;
		}
		if(ListIsEmpty(_list))
		{
			return ERR_EMPTY;
		}
		toRomve = _list->tail.prev;
		PopFromList(toRomve,_data);
		return ERR_SUCCESS;
}

size_t ListCountItems(List* _list)
{
	node* curr;
	size_t count = 0;
	if(!IsValid(_list))
	{
		return count;
	}
	curr=_list->head.next;
	while(curr!=&_list->tail)
	{
		count++;
		curr=curr->next;
	}
	return count;
}

int ListIsEmpty(List* _list)
{
	if(IsValid(_list) &&_list->head.next == &_list->tail)
	{
			return 1;
	}
	return 0;
}

void ListPrint(List* _list)
{
	node* curr;
	int count=0;
	if(!IsValid(_list))
	{
		return;
	}
	curr=_list->head.next;
	while(curr!=&_list->tail)
	{
		
		count++;
		if(count%10==0)
		{
			printf("[%d]\n",curr->data);
		}
		else
		{
			printf("[%d]->",curr->data);
		}	
		curr=curr->next;
	}
	printf("|\n");
}




