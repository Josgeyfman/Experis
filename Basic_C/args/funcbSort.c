#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"fbsort.h"
#define LEN 20

int main()
{
	
	int arr[LEN];
	register int i;
	for(i=0;i<LEN;i++)		
	{
		arr[i]=rand()%(2*LEN);
	}
	BubbleSort(arr,LEN,&Bigger);
	for(i=0;i<LEN;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	BubbleSort(arr,LEN,&Smaller);
	for(i=0;i<LEN;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	BubbleSort(arr,LEN,&Even);
	for(i=0;i<LEN;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	BubbleSort(arr,LEN,&Odd);
	for(i=0;i<LEN;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
	return 0;
}




