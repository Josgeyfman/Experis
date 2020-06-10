#include<stdio.h>
#include<stdlib.h>

int g_i;
int g_k=5;
int g_j=0;

static int s_i;
static int s_k=8;
static int s_j=0;

int main()
{
	int l_i;
	int l_k=3;
	int l_j=0;

	static int sl_i;
	static int sl_k=4;
	static int sl_j=0;
	
	printf("the add of g_i %p in bss\n", (void*) &g_i);
	printf("the add of g_k %p in r/w \n", (void*) &g_k);
	printf("the add of g_j %p in bss \n", (void*) &g_j);

	printf("the add of s_i %p in bss\n", (void*) &s_i);
	printf("the add of s_k %p in r/w\n", (void*) &s_k);
	printf("the add of s_j %p in bss\n", (void*) &s_j);
	
	printf("the add of l_i %p in stack \n", (void*) &l_i);
	printf("the add of l_k %p in stack \n", (void*) &l_k);
	printf("the add of l_j %p in stack \n", (void*) &l_j);
	
	printf("the add of sl_i %p in bss \n", (void*) &sl_i);
	printf("the add of sl_k %p in r/w \n", (void*) &sl_k);
	printf("the add of sl_j %p in bss \n", (void*) &sl_j);
	return 0;
}
