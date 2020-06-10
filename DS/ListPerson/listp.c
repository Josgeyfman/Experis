#include"listp.h"

#include<stdlib.h>
#include<string.h>

#define MAGIC_NUM 0xfeebbeef
#define NOT_MAGIC_NUM 0xdaeddead

struct Person
{
	size_t m_id;
	char m_name[MAX_LEN];
	size_t m_age;
	size_t magicNum;
	person* next;
};

size_t GetPersonId(person* _curr)
{
	return _curr->m_id;
}


static size_t IsValid(person* _p)
{
	if(_p && _p->magicNum==MAGIC_NUM)
	{
		return 1;
	}
	return 0;
}
int IsListSorted(person* _head)
{
	person* curr=_head;
	if(!IsValid(_head))
	{
		return -1;	
	}
	while(IsValid(curr->next))
	{
		if(GetPersonId(curr)>GetPersonId(curr->next))
		{
			return 0;
		}
		curr= curr->next;
	}
	return 1;
}

person* CreateNewPerson(size_t _id,char* _name,size_t _age)
{
	person* newPerson;
	if(_id<0 || _age<0 || !_name)
	{
		return NULL;
	}

	newPerson = (person*)malloc(sizeof(person));
	
	if(!newPerson)
	{
		return NULL;
	}

	newPerson->m_id = _id;
	strcpy(newPerson->m_name,_name);
	newPerson->m_age = _age;
	newPerson->next = NULL;
	newPerson->magicNum = MAGIC_NUM;
	return  newPerson;
}

void ListDestroy(person* _head)
{
	person* curr=_head;
	person* tmp = NULL;
	while(IsValid(curr))
	{
		tmp = curr->next;
		curr->magicNum = NOT_MAGIC_NUM;
		free(curr);
		curr=tmp;
	}
}

void ListDestroyRec(person* _head)
{
	
	if(!IsValid(_head))
	{
		return;
	}
	ListDestroyRec(_head->next);
	_head->magicNum = NOT_MAGIC_NUM;
	free(_head);
}

void GetPersonData(size_t* _id,char*  _name,size_t* _age)
{
	if(!_id || !_name || !_age )
	{
		return;
	}
	printf("Please enter id:\n");	
	scanf("%lu",_id);
	printf("Please enter name:\n");
	scanf("%s",_name);
	printf("Please enter age:\n");
	scanf("%lu",_age);
}

static person* InsertPerson(person* _curr ,person* _p , Place _where )
{
	person* tmp ;
	if(IsValid(_curr) && IsValid(_p) && (_where==START))
	{
		tmp =_curr;	
		_curr 	 = _p;
		_p->next = tmp;
		
	}
	else if(IsValid(_curr) && IsValid(_p) && (_where==MID))
	{
		tmp 	 = _curr->next;	
		_curr 	 = _p;
		_p->next = tmp;
		
	}
	else if(IsValid(_p) && (_where==START || _where==END))
	{
		_curr = _p;
	}
	return _curr;
}

person*  ListInsertHead(person* _head,person* _toInsert)
{
	return InsertPerson(_head,_toInsert,START);
}

person* ListInsertByKey(person* _head, size_t _key, person* _p)
{
	person* curr;
	if(!IsValid(_head) && !IsValid(_p))
	{
		return NULL;
	}
	if( (!IsValid(_head) && IsValid(_p)) || (_head->m_id >_key))
	{
		return InsertPerson(_head,_p,START);
	}
	if(_head->m_id == _key)
	{
		return _head; 
	}
	curr = _head;
	while(IsValid(curr->next))
	{
		if(curr->next-> m_id >_key)
		{
			curr->next = InsertPerson(curr,_p,MID);
			return _head;
		}
		if(curr->next-> m_id ==_key)
		{
			return _head; 
		}
		curr= curr->next;
	}
	 
	curr->next=InsertPerson(curr->next,_p,END);
	return _head;
}

person* ListInsertByKeyRec(person* _head, size_t _key, person* _p)
{
	if(!IsValid(_head) && !IsValid(_p))
	{
		return NULL;
	}
	else if((!IsValid(_head) && IsValid(_p)) || (_head->m_id >_key))
	{
		return InsertPerson(_head,_p,START);
	}
	else if(_head->m_id == _key)
	{
		return _head; 
	}
	else if(!IsValid(_head->next))
	{
		_head->next = InsertPerson(_head->next,_p,END);
		return _head;
	}
	else if(_head->next-> m_id >_key)
	{
		_head->next = InsertPerson(_head,_p,MID);
		return _head;
	}
	else if(_head->next-> m_id ==_key)
	{
		return _head;
	}	
	_head->next =ListInsertByKeyRec(_head->next,_key,_p);
	return _head;
}

static person* RemovePerson(person* _curr,person** _p)
{
	person* tmp = _curr;
	_curr = _curr->next;
	*_p = tmp;
	(*_p)->next=NULL;
	return _curr;

}

person*  ListRemoveHead(person* _head,person** _item)
{
		if(!IsValid(_head) || !_item)
		{
			return NULL;
		}
		return RemovePerson(_head,_item);
}


person* ListRemoveByKey(person* _head, size_t _key, person** _p)
{
	person* curr;
	if(!IsValid(_head) || !_p)
	{
		return NULL;
	}	
	if(_head->m_id==_key)
	{
		return RemovePerson(_head,_p);
	}
	curr = _head;
	while(IsValid(curr->next))
	{
		if(curr->next->m_id==_key)
		{
			curr->next = RemovePerson(curr->next,_p);
			return _head;
		}
		curr= curr->next;
	}
	return _head;
}

person* ListRemoveByKeyRec(person* _head, size_t _key, person**_p)
{
	person* curr = _head;
	if(!IsValid(curr) || !_p)
	{
		return NULL;
	}	
	if(curr->m_id==_key)
	{
		return ListRemoveHead(curr,_p);
	}
	curr->next = ListRemoveByKeyRec(curr->next,_key,_p);
	return curr;
}

void PrintPerson(person* _curr)
{
	if(IsValid(_curr))
	{		
		printf("id:%lu name:%s age:%lu\n",_curr->m_id, _curr->m_name,_curr->m_age);
	}
	else
	{
		printf("null person\n");	
	}

}

void ListPrint(person* _head)
{
	person* curr=_head;
	if(!IsValid(_head))
	{
		printf("List is Empty\n");	
	}
	while(IsValid(curr))
	{
		PrintPerson(curr);
		curr= curr->next;
	}
}




