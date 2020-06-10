#include<stdio.h>

int countUp(void* _num);

int countDown(void* _num);

void Print(void* _num);

void Print2(void* _num);



int main()
{
	int num1 =15 ,num =-12;
	countUp(&num1);
	countDown(&num);
	printf("count up %d , count down %d\n",num1,num);
	Print(&num1);
	Print2(&num1);
	return 0;
}
