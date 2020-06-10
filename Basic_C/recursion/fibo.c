#include<stdio.h>

size_t FiboRec(size_t _n )
{
	
	
	if (_n<=1) 
	{
		return _n;
	}
	return FiboRec(_n-1) +FiboRec(_n-2); 
}


void FiboRecSeries(size_t _n )
{
	
	size_t i;
	for(i=0;i<_n;i++)
	{
		
		printf("[%lu]" ,FiboRec(i));
	}
	printf("\n");
}

int main()
{
	size_t n;
	printf("please enter number\n");
	scanf("%lu",&n);
	FiboRecSeries(n);
	return 0;	
}
