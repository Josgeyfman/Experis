#include<stdio.h> 	
#include<time.h> 
#include"sort.h"
#define LEN 50000
#define BASE_LEN 10

void BubbleSort(vector* _vec)
{
	register int i,j,swapped=0;
	int curr,next,size;
	size = VectorNumOfElements(_vec);
	for(i=1;i<size;i++)		
	{
		for(j=1;j<=size-i;j++)		
		{
			VectorGet(_vec,j,&curr);
			VectorGet(_vec,j+1,&next);
			if(curr>next)
			{
				VectorSet(_vec,j,next);
				VectorSet(_vec,j+1,curr);
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

static int ShakeRight(vector* _vec,int _start,int _fin)
{
	register int j,swapped=0;
	int curr,next;
	for(j=_start;j<_fin;j++)		
	{
		VectorGet(_vec,j,&curr);
		VectorGet(_vec,j+1,&next);
		if(curr>next)
		{
			VectorSet(_vec,j,next);
			VectorSet(_vec,j+1,curr);
			swapped=1;
		}
	}
	return swapped;
}

static int ShakeLeft(vector* _vec,int _start,int _fin)
{
	register int j,swapped=0;	
	int curr,prev;
	for(j=_start;j>_fin;j--)		
	{
		VectorGet(_vec,j,&curr);
		VectorGet(_vec,j-1,&prev);
		if(curr<prev)
		{
			VectorSet(_vec,j,prev);
			VectorSet(_vec,j-1,curr);
			swapped=1;
		}
	}
	return swapped;
}

void ShakeSort(vector* _vec)
{
	register int i,size,swapped=0;
	size = VectorNumOfElements(_vec);
	for(i=1;i<=size;i++)		
	{
		swapped = ShakeRight(_vec,i,size-i+1);
		if(!swapped)
		{
			break;
		}
		swapped = ShakeLeft(_vec,size-i+1,i);
		if(!swapped)
		{
			break;
		}
		swapped=0;
	}
}

int IsSorted(vector* _vec)
{
	register int i,size = VectorNumOfElements(_vec);
	 int curr,next ;
	for(i=1;i<=size;i++)
	{
		VectorGet(_vec,i,&curr);
		VectorGet(_vec,i+1,&next);
		if(curr>next)
		{
			printf("curr:%d next:%d i:%d i+1:%d\n",curr,next,i,i+1);
			return 0;
		}
	}
	return 1;
}

static void Swap(vector* _vec,int _i,int _j,int _val1 ,int _val2)
{
	VectorSet(_vec,_i,_val2);
	VectorSet(_vec,_j,_val1);
}

static int Partition(vector* _vec,int _low,int _high)
{
	register int i =_low+1,j=_high;
	int pivot,lowVal,highVal;
	VectorGet(_vec,_low,&pivot);
	while(i<=j)
	{
		VectorGet(_vec,i,&lowVal);
		while(lowVal<=pivot && i<=j)
		{
			VectorGet(_vec,++i,&lowVal);
		}
		VectorGet(_vec,j,&highVal);
		while(highVal>pivot && i<=j)
		{
			VectorGet(_vec,--j,&highVal);
		}
		if(i<=j)
		{
			Swap(_vec,i,j,lowVal,highVal);
		}
	}
	VectorGet(_vec,j,&lowVal);
	Swap(_vec,j,_low,lowVal,pivot);
	return j;
}

void QuickSortRec(vector* _vec,int _low,int _high)
{
	register int mid;
	if(_vec &&_low <_high)
	{
		mid = Partition(_vec,_low,_high);
		QuickSortRec(_vec,_low,mid-1);
		QuickSortRec(_vec,mid+1,_high);
	}
} 


void QuickSort(vector* _vec,int _low,int _high)
{
	register int mid;
	int low=_low,high=_high;
	stack* st;
	if(!_vec)
	{
		return;
	}
	st = StackCreate(_high -_low,0);
	if(!st)
	{
		return;
	}
	StackPush(st,high);
	StackPush(st,low);
	while(!StackIsEmpty(st))	
	{
		StackPop(st,&low);
		StackPop(st,&high);
	
		mid = Partition(_vec,low,high);
		
		if(mid+1<high)
		{
			StackPush(st,high);
			StackPush(st,mid+1);
		}
		if(low<mid-1)
		{
			StackPush(st,mid-1);
			StackPush(st,low);
		}
		
	}
	
	StackDestroy(st);
	
}

void InsertionSort(vector* _vec,int _start,int _gap)
{
	register int i,j,size;
	int curr,next,newElment;
	if(!_vec)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	for(i=_start;i<=size;i+=_gap)
	{
		VectorGet(_vec,i+_gap,&newElment);
		j = i;
		VectorGet(_vec,j,&curr);
		next = newElment;
		while(j>0 && curr>newElment )
		{
			VectorSet(_vec,j,next);
			VectorSet(_vec,j+_gap,curr);
			j-=_gap;
			VectorGet(_vec,j+_gap,&next);
			VectorGet(_vec,j,&curr);
		}
	}
}

void ShellSort(vector* _vec)
{
	register int i,size,gap; 
	if(!_vec)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	gap = size/2;
	while(gap)
	{
		for(i=1;i<=gap;i++)
		{
			InsertionSort(_vec,i,gap);
		}
		gap/=2;
	}
}

static int FindMid(vector* _vec,int _start ,int _fin,int* _min)
{
	register int i,minIndx = _start;
	int min=0,curr=0;
	VectorGet(_vec,_start,&min);
	VectorGet(_vec,_fin,&curr);
	for(i=_start+1;i<=_fin;i++)
	{
		VectorGet(_vec,i,&curr);
		if(curr<min)
		{
			min = curr;
			minIndx = i; 
		}
	}
	*_min=min;
	return minIndx;
}

void SelectionSort(vector* _vec)
{
	register int i=1,size,minIndx;
	int min,curr;
	if(!_vec)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	while(i<=size)
	{
		minIndx = FindMid(_vec,i,size,&min);
		VectorGet(_vec,i,&curr);
		Swap(_vec,i,minIndx,curr,min);
		i++;
	}
}
static void Merge(vector* _vec,int _start1,int _fin1,int _start2,int _fin2,int* _arr)
{
	int i,j = _start1,val1,val2;
	i=_start1;
	while(_start1<=_fin1 && _start2<=_fin2)
	{
		VectorGet(_vec,_start1,&val1);
		VectorGet(_vec,_start2,&val2);
		if(val1<val2)
		{
			_arr[j]=val1;
			_start1++;
		}
		else
		{
			_arr[j]=val2;
			_start2++;
		}
		j++;
	}
	while(_start1<=_fin1)
	{
		VectorGet(_vec,_start1,&_arr[j]);
		_start1++;
		j++;
		
	}
	while(_start2<=_fin2)
	{
		VectorGet(_vec,_start2,&_arr[j]);
		_start2++;
		j++;
		
	}
	
	for(;i<=_fin2;i++)
	{
		VectorSet(_vec,i,_arr[i]);
	}
}
	
static void MergeSort(vector* _vec,int _start,int _fin,int* _arr)
{
	int mid;	
	if(_start >=_fin)
	{
		return;	
	}
	mid = (_fin +_start)/2;
	MergeSort(_vec,_start,mid,_arr);
	MergeSort(_vec,mid+1,_fin,_arr);
	Merge(_vec,_start,mid,mid+1,_fin,_arr);

}

void MergeSortVector(vector* _vec)
{
	register int size;
	int* arr;
	if(!_vec)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	arr = (int*)malloc(sizeof(int)*(size+1));
	if(!arr)
	{
		return;
	}
	MergeSort(_vec,1,size,arr);
	free(arr);
}

void CountingSort(vector* _vec ,int _range)
{
	register int size,i;
	int* Aarr; 
	int* Barr;
	int curr;
	if(!_vec || _range<0)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	Aarr = (int*)calloc(_range,sizeof(int));
	if(!Aarr)
	{
		return;
	}
	Barr = (int*)calloc(size,sizeof(int));
	if(!Barr)
	{
		free(Aarr);
		return;
	}
	for(i=0;i<size;i++)
	{
		VectorGet(_vec,i+1,&curr);
		Aarr[curr] = Aarr[curr]+1;
	}
	for(i=1;i<_range;i++)
	{
		Aarr[i] = Aarr[i]+Aarr[i-1];
	}
	for(i=size;i>0;i--)
	{
		VectorGet(_vec,i,&curr);
		Barr[Aarr[curr]] = curr;
		Aarr[curr]= Aarr[curr]-1;
	}
	for(i=0;i<size;i++)
	{
		VectorSet(_vec,i+1,Barr[i]);
	}
	free(Aarr);
	free(Barr);
}




static void CountSortRadix(vector* _vec ,int _base, int _digit)
{
	register int size,i;
	int* Aarr; 
	int* Barr;
	int curr;

	if(!_vec)
	{
		return;
	}
	size = VectorNumOfElements(_vec);
	Aarr = (int*)calloc(_base,sizeof(int));
	if(!Aarr)
	{
		return;
	}
	Barr = (int*)calloc(size,sizeof(int));
	if(!Barr)
	{
		free(Aarr);
		return;
	}
	for(i=0;i<size;i++)
	{
		VectorGet(_vec,i+1,&curr);
		Aarr[(curr/_digit)%_base] = Aarr[(curr/_digit)%_base]+1;
	}
	for(i=1;i<_base;i++)
	{
		Aarr[i] = Aarr[i]+Aarr[i-1];
	}
	for(i=size;i>0;i--)
	{
		VectorGet(_vec,i,&curr);
		Barr[Aarr[(curr/_digit)%_base]-1] = curr;
		Aarr[(curr/_digit)%_base]= Aarr[(curr/_digit)%_base]-1;
	}
	for(i=0;i<size;i++)
	{
		VectorSet(_vec,i+1,Barr[i]);
	}
	if(Aarr)
	{
		free(Aarr);
	}
	if(Barr)
	{
		free(Barr);
	}
}

void RadixSort(vector* _vec ,int _range)
{
	int digit;
	if(!_vec)
	{
		return;
	}
	for(digit=1;_range/digit>0;digit*=BASE_LEN)
	{
		CountSortRadix(_vec,BASE_LEN,digit);
	}

}


int main()
{
	int i,sorted=0,val;
	vector* vec = VectorCreate(LEN,3);
	vector* vec1 = VectorCreate(LEN,3);
	vector* vec2 = VectorCreate(LEN,3);
	vector* vec3 = VectorCreate(LEN,3);
	vector* vec4 = VectorCreate(LEN,3);
	vector* vec5 = VectorCreate(LEN,3);
	clock_t start,fin;
	double total;
	time_t t;
	srand((unsigned) time(&t));
	for(i=1;i<=LEN;i++)
	{
		val = rand()%(200*LEN);
		VectorAddTail(vec,val);
		VectorAddTail(vec1,val);
		VectorAddTail(vec2,val);
		VectorAddTail(vec3,val);
		VectorAddTail(vec4,val);
		VectorAddTail(vec5,val);
	}
	start = clock();
	QuickSort(vec,1,LEN);
	fin = clock();
	sorted = IsSorted(vec);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Quick Recursive run time is %f ,is sorted?%d\n" ,total,sorted);
	start = clock();
	QuickSort(vec1,1,LEN);
	fin = clock();
	sorted = IsSorted(vec1);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Quick iterative run time is %f ,is sorted?%d\n" ,total,sorted);
	start = clock();
	ShellSort(vec2);
	fin = clock();
	sorted = IsSorted(vec2);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Shell sort      run time is %f ,is sorted?%d\n" ,total,sorted);
	start = clock();
	MergeSortVector(vec3);
	fin = clock();
	sorted = IsSorted(vec3);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Merge sort      run time is %f ,is sorted?%d\n" ,total,sorted);
	start = clock();
	RadixSort(vec5,200*LEN);
	fin = clock();
	sorted = IsSorted(vec5);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Radix sort      run time is %f ,is sorted?%d\n" ,total,sorted);
	start = clock();
	CountingSort(vec4,200*LEN);
	fin = clock();
	sorted = IsSorted(vec4);
	total = (double) (fin-start)/CLOCKS_PER_SEC;
	printf("Counting sort   run time is %f ,is sorted?%d\n" ,total,sorted);
	
	VectorDestroy(vec);
	VectorDestroy(vec1);
	VectorDestroy(vec2);
	VectorDestroy(vec3);
	VectorDestroy(vec4);
	VectorDestroy(vec5);
	return 0;
}

	
