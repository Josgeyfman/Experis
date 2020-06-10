#include <stdio.h>

int countUp(void* _num)
{
	return !((*(int*)_num)++);
}

void Print2(void* _num)
{
	printf("fourth func in lib\n");
}
