#include<stdio.h> /*printf*/
#include <stdlib.h>

int g_i = 100;


void foo2()
{
	printf("hacked\n");
}

int foo(int i,int j)
{
	int m =500,l =600;
	void** p;
	printf("i:%d i:%x Add:%p\n",i,i,(void*)&i);
	printf("j:%d j:%x Add:%p\n",j,j,(void*)&j);
	printf("m:%d m:%x Add:%p\n",m,m,(void*)&m);
	printf("l:%d l:%x Add:%p\n",l,l,(void*)&l);
	printf("p:%d p:%x Add:%p\n",p,p,(void**)&p);
	*((&p)+9)=foo2;
	return 2000;
}




int main()
{
	int i =200;
	int j = 300;
	static int sl = 1000;
	int k;
	
	k = foo(i,j);
	fflush(stdout);
	printf("\n\ng_i:%d g_i:%x Add:%p\n",g_i,g_i,(void*)&g_i);
	printf("i:%d i:%x Add:%p\n",i,i,(void*)&i);
	printf("j:%d j:%x Add:%p\n",j,j,(void*)&j);
	printf("sl:%d sl:%x Add:%p\n",sl,sl,(void*)&sl);
	printf("main:%p  foo:%p\n",(void*)&main,(void*)&foo);
	return 0;
}
