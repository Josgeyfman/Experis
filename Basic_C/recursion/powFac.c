#include<stdio.h>


int PowerRec(int _n ,int _k)
{
	return (_k==1) ? _n : _n * PowerRec(_n,_k-1) ; 
}

int FactorialRec(int _n )
{
	return (_n==1) ? _n : _n * FactorialRec(_n-1) ; 
}

void PrintNums(int _n)
{
	if(_n==0)
	{
		return; 
	}
	PrintNums(_n-1); 
	printf("%d\n" ,_n);
}

int main()
{
	int n;
	printf("please enter number\n");
	scanf("%d",&n);
	printf("please enter exp\n");
	scanf("%d",&k);
	n = FactorialRec(n);
	printf("result: %d\n" ,n);
	return 0;	
}

