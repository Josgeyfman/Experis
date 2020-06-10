#include<stdio.h>
#include<stdlib.h>
int main(int argc,char* argv[])
{
	int a,b;
	if(argc<3)
	{
		printf("not enough parametrs");
		return -1;
	}
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	printf("the sum of %d + %d = %d\n",a,b,a+b);
	printf("the mul of %d * %d = %d\n",a,b,a*b);
	return 0;
}
