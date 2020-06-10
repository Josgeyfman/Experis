#include<stdio.h> 	
#include<stdlib.h> 
#include<time.h> 
#define LEN 1000000

int SearchQuick(int _arr[],int size,int _data)
{
	register size_t i,retIndx;
	 int tmp ;
	if(!_arr)
	{
		return -1;
	}
	tmp = _arr[size-1];
	if(tmp==_data)
	{
		return size-1;
	}
	_arr[size-1] =_data;
	for(i=0;;i++)
	{
		if(_arr[i]==_data)
		{
			retIndx = i;
			break;
		}
	}
	if(retIndx == size-1)
	{
		_arr[size-1] = tmp;
		return -1;
	}
	return retIndx;
}

int Search(int _arr[],int size,int _data)
{
	register size_t i;
	if(!_arr)
	{
		return -1;
	}
	for(i=0;i<size;i++)
	{
		if(_arr[i]==_data)
		{
			return i;
		}
	}
	return -1;
}

int main()
{
	register int i,found=0,val;
	clock_t start,fin;
	double total=0,total2=0;
	time_t t;
	int* arr = (int*)calloc(LEN,sizeof(int));
	if(!arr)
	{
		return -1;
	}
	srand((unsigned) time(&t));
	for(i=0;i<LEN;i++)
	{
		arr[i] = rand()%(2*LEN);
		
	}
	for(i=0;i<10;i++)
	{
		val = rand()%(2*LEN);
		start = clock();
		found = Search(arr,LEN,val);
		fin = clock();
		if(found>0)
		{
			total += (double) (fin-start)/CLOCKS_PER_SEC;
		}
		found=0;
		start = clock();
		found = SearchQuick(arr,LEN,val);
		fin = clock();
		if(found>0)
		{
			total2 += (double) (fin-start)/CLOCKS_PER_SEC;
		}
	}
	printf("Search run time is %lu \n" ,(sizeof(arr)/sizeof(int)));
	printf("Search run time is %f \n" ,total);
	printf("Search Quick run time is %f \n" ,total2);
	free(arr);
	return 0;
}
