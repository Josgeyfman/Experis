#include<stdio.h>
#include<stdlib.h>

void PrintNum(int *_pnum,int _num){
	
	printf("addrres is: %p ,num is %d ,pnum val is %d\n" ,(void*)_pnum,_num,*_pnum);
		
}

void PrintIntPointerDiff(int* _pa,int* _pb)
{
		long result =_pb -_pa;
		printf("pa address is: %p ,pb address is %p ,pb - pa = %ld\n" ,(void*)_pa,(void*)_pb,result);
}

void PrintCharPointerDiff(char* _pa,char* _pb)
{
		long result =_pb -_pa;
		printf("pa address is: %p ,pb address is %p ,pb - pa = %ld\n" ,(void*)_pa,(void*)_pb,result);
}

void PointToArr(int* _parr[],int _arr[],int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		_parr[i]=&_arr[i];	
	}
}

void PrintPointerArr(int* _parr[],int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		printf("%d ", *(_parr[i]));	
	}
	printf("\n");
}

void SwapPointer(int** _val1,int** _val2)
{
	int* temp;

	temp = *_val1;
	*_val1 = *_val2;
	*_val2 =  temp;

}

void BubbleSortPointerArr(int* _arr[],int _size)
{
	int i,j,swapped;
	for(i=0;i<_size-1;i++)
	{
		swapped=0;
		for(j = 0 ;j < _size-i-1 ; j++)
		{
			if(*(_arr[j]) > *(_arr[j+1]))
			{
				SwapPointer(&_arr[j],&_arr[j+1]);
				swapped=1;
			}
		}
		if(!swapped){
			break;
		}
	}
}

void RandomInitPointer(int* _arr,int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		_arr[i]=rand()%_size;	
	}

	for(i=0;i<_size;i++)
	{
		printf("%d",_arr[i]);
	}
	printf("\n");
}

int main()
{
	/*int *a = &arr[2],*b=&arr[5];
	char buff[] =" my buffer";
	char *c = &buff[2],*d=&buff[5];
	PrintIntPointerDiff(a,b);
	PrintCharPointerDiff(c,d);
	int arr[] ={50,10,20,30,4,7,8};
	int size = sizeof(arr)/sizeof(arr[0]);
	int *parr[sizeof(arr)/sizeof(arr[0])];
	
	PointToArr(parr,arr,size);
	printf("before sort: ");
	PrintPointerArr(parr,size);

	BubbleSortPointerArr(parr,size);
	printf("after sort: ");
	PrintPointerArr(parr,size);*/

	int *ptr ,size;
	printf("please enter size:\n");
	scanf("%d",&size);
	ptr = (int*)malloc(size*sizeof(int));
	if(ptr==NULL)
	{
		printf("memory allocation error\n");
		return 1;
	}
	RandomInitPointer(ptr,size);
	free(ptr);
	return 0;
}




