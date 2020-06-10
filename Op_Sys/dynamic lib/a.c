#include <stdio.h>

int countDown(void* _num)
{
	printf("in countdown\n");
	return !((*(int*)_num)--) ;
}  

void Print(void* _num)
{
	printf("third func in lib\n");
}  
