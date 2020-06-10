#include<stdio.h> /*printf*/
#include <stdlib.h>

struct mys
{
	char a;
	char d;
	int i;
	long b;
	char arr[13];
	double c;
	
};




int main()
{
	struct mys m;
	printf("size of mys:%ld\n",sizeof(m));
	return 0;
}
