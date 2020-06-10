#include<stdio.h>

void PrintCharArr(char arr[],int _size)
{
	int i;

	for(i=0;i<_size;i++)
	{
		printf("%c ",arr[i]);
	}
	printf("\narr size: %d\n" ,_size);
} 

void PrintIntArr(int arr[],int _size)
{
	int i;        
	for(i=0;i<_size;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\narr size: %d\n" ,_size);
}

void PrintFloatArr(float arr[],int _size){
	int i;
	for(i=0;i<_size;i++)
	{
		printf("%f ",arr[i]);
	} 
}


void Swap(int _arr[],int _val1,int _val2)
{
	int temp;

	temp = _arr[_val1];
	_arr[_val1] = _arr[_val2];
	_arr[_val2]=temp;

}

void MirrorArr(int _arr[], int _size )
{
	int i; 

	for(i=0;i<_size/2;i++)
	{
		Swap(_arr,i,_size-i-1);
	}
	
}

int MyStrLen(char _str[]){
	
	int count=0;

	while(_str[count])
	{
		count++;
	}
	return count;
}

int IsPalyndrom();
void BubbleSort(int _arr,int size);
int IsEquaL(char _str1[],char _str2[]);

int main(){

	/*char charBuff[]={'a','b','c','d'};
	int size,intBuff[] ={1,2,3,4,5,6};
	float floatBuff[] ={.1,.2,.3,.4,5.,6.};

	size = sizeof(charBuff)/sizeof(char);
	PrintCharArr(charBuff,size);
		
	size = sizeof(intBuff)/sizeof(int);
	PrintIntArr(intBuff,size);

	size = sizeof(floatBuff)/sizeof(float);
	PrintFloatArr(floatBuff,size);
	PrintIntArr(intBuff,size);
	MirrorArr(intBuff,size);
	PrintIntArr(intBuff,size);*/
	
	printf("my str len is %d\n", MyStrLen("my str len is %d\n"));

	return 0;
}


