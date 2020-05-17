typedef struct Node Node;
struct Node 
{
    int	 m_key;
    Node*   m_next;      
};


Node*  FindFirstCommon(Node* _Head1, Node* _Head2)
{
		Node* newListCurr;
		Node* tmp1;
		Node* tmp2;
		if(!_Head1 || !_Head2)
		{
			return NULL;
		}
		newListCurr = _Head1;
		tmp1 =	_Head1 ->m_next;
		tmp2 =	_Head2;
		while(newListCurr)
		{
			newListCurr->m_next = tmp2;
			tmp2 = tmp2->m_next;
			if(newListCurr->m_next==tmp1)
			{
				return tmp1;
			}
			newListCurr->m_next = tmp1;
			tmp1 = tmp1->m_next;
			if(newListCurr->m_next==tmp2)
			{
				return tmp2;
			}
		}
		return newListCurr;
}


typedef struct MinStack 
{
    vector*	 vec;
   int  count;      
}mstack;


errcode MinStackTop(mstack _mp ,int* min)
{
	int min;
	if(!_mp || StackMinIsEmpty(_mp))
	{
		*min=NULL
		return ERR_Empty;
	}
	return VectorGet(_mp->vec,VectorNumOfElements(_mp->vec),min);
}

errcode MinStackPush(mstack _mp ,int data)
{
	int* min;
	if(!_mp || StackMinIsEmpty(_mp))
	{
		*min=NULL
		return ERR_Empty;
	}
	MinStackTop(_mp,min);
	if(min && *min>data)
	{
		VerctorAddTail(_mp->vec,VectorNumOfElements(_mp->vec),data);
	}
	else
	{
		VerctorRemoveTail(_mp->vec,VectorNumOfElements(_mp->vec),min);
		VerctorAddTail(_mp->vec,VectorNumOfElements(_mp->vec),data);
		VerctorAddTail(_mp->vec,VectorNumOfElements(_mp->vec),min);
	}
	return Success;
}


typedef struct Queue Queue;
struct Queue
{
    int*     m_vec;
    int      m_size;
    int      m_head;      
    int      m_tail;      
    int      m_nItems;
};
ADTErr QueueInsert(Queue *_queue, int _item)
{
    if (_queue->m_nItems == _queue->m_size) 
    {   
 /* Queue is full. */
        return ERR_OVERFLOW;
    }

	res = VectorSet(_queue->m_vec,_queue->m_tail,item);
   _queue->m_tail = (queue->m_tail %  _queue->m_size) + 1; 

    return ERR_OK;



Node* Flip(Node* _node)
{
	Node* rev;
	if(!_node->next){

		return _node; 
	}
	else
	{
		rev = Flip(_node->m_next);
		rev->next  = _node;
		_node->next = NULL
		return rev;
	}
}