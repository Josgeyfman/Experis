#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define SWAP(a,b,t) { t tmp = a ; a = b ; b = tmp ;}
#define LEN 50000
typedef enum{INT,CHAR,FLOAT}dtype;


typedef union Data
{
	int a;
	float b;
	char c;
}data;

struct UN
{
	data d;
	dtype type;
};


void printUnion()
{
	struct UN un[10];
	int i;
	for(i=0;i<10;i++)
	{
		if(i%3==0)
		{
			un[i].type = INT;
			un[i].d.a = i;
			printf("%d\n",un[i].d.a);
		}
		if(i%3==1)
		{
			un[i].type = FLOAT;
			un[i].d.b = i+.1;
			printf("%f\n",un[i].d.b);
		}
		if(i%3==2)
		{
			un[i].type = CHAR;
			un[i].d.c = i+'a';
			printf("%c\n",un[i].d.c);
		}
		
	}
}


void Swap(int* a,int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;

}

void BubbleSort(int arr[],int size)
{
	register int i,j,swapped=0;
	for(i=0;i<size-1;i++)		
	{
		for(j=0;j<size-i-1;j++)		
		{
			if(arr[j]>arr[j+1])
			{
				/*SWAP(arr[j],arr[j+1],int);*/
				Swap(&arr[j],&arr[j+1]);
				swapped=1;
			}
		}	
		if(!swapped)
		{
			break;
		}
		swapped=0;
	}
}


void BubbleSortMac(int arr[],int size)
{
	register int i,j,swapped=0;
	for(i=0;i<size-1;i++)		
	{
		for(j=0;j<size-i-1;j++)		
		{
			if(arr[j]>arr[j+1])
			{
				SWAP(arr[j],arr[j+1],int);
				swapped=1;
			}
		}	
		if(!swapped)
		{
			break;
		}
		swapped=0;
	}
}
int main()
{
	
	int arr1[LEN],arr2[LEN],isSorted=1;
	register int i;
	double total;
	clock_t stime,ftime;
	for(i=0;i<LEN;i++)		
	{
		arr1[i]=rand()%(2*LEN);
		arr2[i]=rand()%(2*LEN);
	}
	stime = clock();
	BubbleSort(arr1,LEN);
	ftime = clock();
	total=(double)(ftime-stime)/CLOCKS_PER_SEC;
	for(i=0;i<LEN-1;i++)		
	{
		if(arr1[i]>arr1[i+1])
		{
			isSorted=0;
		}
		
	}
	printf("runtime equals %f seconds,sort success? :%d\n",total,isSorted);
	stime = clock();
	BubbleSortMac(arr2,LEN);
	ftime = clock();
	total=(double)(ftime-stime)/CLOCKS_PER_SEC;
	for(i=0;i<LEN-1;i++)		
	{
		if(arr2[i]>arr2[i+1])
		{
			isSorted=0;
		}
		
	}
	printf("Macro runtime equals %f seconds,sort success? :%d\n",total,isSorted);
	return 0;
}




