#include<stdio.h>
#include"stack.h"
#include"tower.h"



void Move(stackp _from ,stackp _to)
{
	int data,data2;
	StackTop(_from,&data);
	StackTop(_to,&data2);
	if(data2!=0 && data>data2)
	{
		printf("error\n");
		exit(1);
	}
	StackPop(_from,&data);
	StackPush(_to,data);
}

void TowerPlay(int _n ,stackp _from ,stackp _to ,stackp _via)
{
	
	if(_n==1)
	{
		Move(_from,_to);	
		return;
	}
	TowerPlay(_n-1,_from,_via,_to);
	TowerPlay(1,_from,_to,_via );
	TowerPlay(_n-1,_via,_to,_from);

}

void InitGame(int _n)
{
	int i;	
	stackp p1;
	stackp p2;
	stackp p3;
	
	p1 = StackCreate(_n,0);
	p2 = StackCreate(_n,0);
	p3 = StackCreate(_n,0);

	for(i=0;i<_n;i++)
	{
		StackPush(p1,_n-i);
	}
	printf("\nfrom stack before: ");	
	StackPrint(p1);

	TowerPlay(_n,p1,p2,p3);
	printf("\nfrom stack: ");
	StackPrint(p1);
	printf("\nto stack: ");
	StackPrint(p2);

	StackDestroy(p1);
	StackDestroy(p2);
	StackDestroy(p3);
}







