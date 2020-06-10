#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct Node Node;

typedef struct Node
{
	int data;
	Node* next;
}node;

node* createList(node* head ,int size)
{
	int i;
	node* tmp;
	for(i=0;i<size;i++)
	{
		tmp = (node*) malloc(sizeof(node));
		if(!tmp)
		{
			return NULL;
		}
		tmp->data=size-i;
		if(head){
			tmp->next=head;
		}
		else
		{
			tmp->next=NULL;
		}
		head = tmp;
	}
	return head;
}

void printList(node* head)
{
	node* curr = head;
	while(curr)
	{
		printf("%d->",curr->data);
		curr=curr->next;
	}
	printf("|\n");
}

void freeList(node* head)
{
	node* curr = head;
	node* tmp;
	while(curr)
	{
		tmp=curr->next;
		free(curr);
		curr=tmp;
	}
	printf("|\n");
}

node* Flip(node* _node)
{
	node* rev;
	if(!_node->next)
	{
		return _node;
	}
	rev = Flip(_node->next);
	_node->next->next =_node; 
	_node->next = NULL;
	return rev;
}

int main()
{
	node* p=NULL;
	p = createList(p,6);
	printList(p);
	p = Flip(p);
	printList(p);
	return 0;
}







