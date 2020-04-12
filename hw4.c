#include<stdio.h>

int IsPalyndrom();
void BubbleSort(int _arr[],int size);
void Swap(int _arr[],int _val1,int _val2);
void PrintIntArr(int arr[],int _size);
int IsEqual(char _str1[],char _str2[]);


int main(){
	
	int arr[] ={1,7,5,2,2,2,3,1,4,9};
	int arr1[] ={1,1,1,3,2,2,3,1,1,1};
	int st[] = {'a','b','b','a'};
	char str1[] = "abcdefghijklmnopqrstuvwxyz";
	char str2[] = "abcdefghijklmnopqrstuvwxyz";
	char str3[] = "abcdefghijklmnopsdqrstuvwxyz";
	char str4[] = "abcdefghijsdklmnopqrstuvwxyz";

	printf("compiled with script\n");
	printf("is arr a Palyndrom? %d\n", IsPalyndrom(arr,10));
	printf("is arr1 a Palyndrom? %d\n", IsPalyndrom(arr1,10));
	printf("is st a Palyndrom? %d\n", IsPalyndrom(st,4));       	

	printf("arr before sort: ");
	PrintIntArr(arr,10);	
	BubbleSort(arr,10);
	printf("arr after sort: ");	
	PrintIntArr(arr,10);

	printf("str1 and str2 are equal? %d\n", IsEqual(str1,str2));
	printf("str3 and str4 are equal? %d\n", IsEqual(str3,str4));
	
	return 0;
}

int IsPalyndrom(int _str[],int _size)
{
	int i ;
	
	for(i=0;i<_size/2;i++)
	{
		if(_str[i] -'0'!= _str[_size-i-1]- '0')
		{
			return 0;
		}
	}
	return 1;
}



void PrintIntArr(int arr[],int _size)
{
	int i;        
	for(i=0;i<_size;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

int IsEqual(char _str1[],char _str2[])
{
	int i = 0;
	while(_str1[i] && _str2[i]){
		if(_str1[i]!=_str2[i])
		{
			return 0;
		}
		i++;
	}
	return 1;
}

