#include <stdio.h>

int countDown(void* _num)
{
	return !((*(int*)_num)--) ;
}  

void Print(void* _num)
{
	printf("third func in lib\n");
}  
