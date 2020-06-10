#include"list_functions.h"
#include<stdbool.h>

/*----------------------------------static func signatutes---------------------------------*/

static ListItr FuncOverList(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context ,bool stopFlag);
static int ShakeLeft(ListItr _begin, ListItr _end, LessFunction _less);
static int ShakeRight(ListItr _begin, ListItr _end, LessFunction _less);
static void Swap(ListItr _curr, ListItr _next,void* _currEl,void* _nextEl);

/*----------------------------------API functions ----------------------------------------------*/

ListItr ListItr_FindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	if(!_predicate)
	{
		return NULL;
	}

	return FuncOverList(_begin,_end,_predicate,_context,true);
}

ListItr ListItr_ForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
	if(!_action)
	{
		return _end;
	}
	return FuncOverList(_begin,_end,_action,_context,false);
}

size_t ListItr_CountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
	size_t count = 0;
	if(!_predicate)
	{
		return count;
	}
	while(!ListItr_Equals(_begin,_end))
	{
		if(_predicate(ListItr_Get(_begin),_context))
		{
			count++;
		}
		_begin = ListItr_Next(_begin);
	}
	return count;
}


void ListItr_Sort(ListItr _begin, ListItr _end, LessFunction _less)
{
	register size_t swapped = 0;
	while(!ListItr_Equals(_begin,_end))		
	{
		swapped = ShakeRight(_begin,_end,_less);
		if(!swapped)
		{
			break;
		}
		swapped = ShakeLeft(ListItr_Prev(_begin),ListItr_Prev(_end),_less);
		if(!swapped)
		{
			break;
		}
		_begin = ListItr_Next(_begin);
		_end = ListItr_Prev(_end);
		swapped=0;
	}
}

ListItr ListItr_Splice(ListItr _dest, ListItr _begin, ListItr _end)
{
	void* element;
	ListItr prev = ListItr_Prev(_end);
	ListItr tmp;
	while(!ListItr_Equals(_begin,prev))
	{
		tmp = ListItr_Prev(prev);
		element = ListItr_Remove(prev);
		ListItr_InsertBefore(_dest,element);
		_dest = ListItr_Prev(_dest);
		prev = tmp;
	}
	element = ListItr_Remove(prev);
	ListItr_InsertBefore(_dest,element);
	return _begin;
}


ListItr ListItr_Merge(ListItr _destBegin, ListItr _firstBegin, ListItr _firstEnd,
			ListItr _secondBegin, ListItr _secondEnd, LessFunction _less)
{
	ListItr tmp = NULL;
	void* element = NULL;
	while(!ListItr_Equals(_firstBegin,_firstEnd) && !ListItr_Equals(_secondBegin,_secondEnd))
	{
		if(!(*_less)(ListItr_Get(_firstBegin),ListItr_Get(_secondBegin)))
		{
			tmp = ListItr_Next(_firstBegin);
			element = ListItr_Remove(_firstBegin);
			ListItr_InsertBefore(_destBegin,element);
			_firstBegin=tmp;
			
		}
		else
		{
			tmp = ListItr_Next(_secondBegin);
			element = ListItr_Remove(_secondBegin);
			ListItr_InsertBefore(_destBegin,element);
			_secondBegin = tmp;
		}
		_destBegin = ListItr_Prev(_destBegin);
	}

	while(!ListItr_Equals(_firstBegin,_firstEnd))
	{
		tmp = ListItr_Next(_firstBegin);
		element = ListItr_Remove(_firstBegin);
		ListItr_InsertBefore(_destBegin,element);
		_firstBegin=tmp;
	}
	while(!ListItr_Equals(_secondBegin,_secondEnd))
	{
		tmp = ListItr_Next(_secondBegin);
		element = ListItr_Remove(_secondBegin);
		ListItr_InsertBefore(_destBegin,element);
		_secondBegin = tmp;
	}
	return _destBegin;
}

List* ListItr_Cut(ListItr _begin, ListItr _end)
{
	List* listp = List_Create();
	ListItr tail = ListItr_End(listp);
	ListItr_Splice(tail,_begin,_end);
	return listp;
}


List* ListItr_Unique(ListItr _begin, ListItr _end, EqualsFunction _equals)
{
	List*  listp = List_Create();
	ListItr tail = ListItr_End(listp);
	ListItr next = ListItr_Next(_begin);
	ListItr tmp  = NULL;
	void* element;
	while(!ListItr_Equals(next,_end))
	{
		if(_equals(ListItr_Get(_begin),ListItr_Get(next)))
		{
			tmp = ListItr_Next(next);
			element = ListItr_Remove(next);
			ListItr_InsertBefore(tail,element);
			next = tmp;
		}
		else
		{
			_begin = next;
			next = ListItr_Next(next);
		}
	}
	return listp;
}


/*-------------------------------------static functions---------------------------------------------------------*/

static ListItr FuncOverList(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context ,bool stopFlag)
{
	void* element;
	while(!ListItr_Equals(_begin,_end))
	{
		element = ListItr_Get(_begin);
		if(stopFlag == _predicate(element,_context))
		{
			break;
		}
		_begin = ListItr_Next(_begin);
	}
	return _begin;
}

static void Swap(ListItr _curr, ListItr _next,void* _currEl,void* _nextEl)
{
	ListItr_Set(_curr,_nextEl);
	ListItr_Set(_next,_currEl);
}

static int ShakeRight(ListItr _begin, ListItr _end, LessFunction _less)
{
	register size_t swapped=0;
	ListItr next = ListItr_Next(_begin);
	void* currEl;
	void* nextEl;
	while(!ListItr_Equals(next,_end))
	{
		currEl = ListItr_Get(_begin);
		nextEl = ListItr_Get(next);
		if(!_less(currEl,nextEl))
		{
			Swap(_begin,next,currEl,nextEl);
			swapped = 1;
		}
		_begin = next;
		next = ListItr_Next(next);
	}
	return swapped;
}

static int ShakeLeft(ListItr _begin, ListItr _end, LessFunction _less)
{
	register size_t swapped=0;
	ListItr prev = ListItr_Prev(_end);
	void* currEl;
	void* prevEl;
	while(!ListItr_Equals(_begin,prev))
	{
		currEl = ListItr_Get(_end);
		prevEl = ListItr_Get(prev);
		if(!_less(prevEl,currEl))
		{
			Swap(prev,_end,prevEl,currEl);
			swapped = 1;
		}
		_end = prev;
		prev = ListItr_Prev(prev);
	}
	return swapped;
}







