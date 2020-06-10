
#define SWAP(a,b,t) { t tmp = a ; a = b ; b = tmp ;}


int Bigger(int _a,int _b)
{
	return (_a>_b);
}

int Smaller(int _a,int _b)
{
	return (_a<_b);
}


int Even(int _a,int _b)
{
	return (_a%2!=0)&&(_b%2==0);
	
}

int Odd(int _a,int _b)
{
	return (_a%2==0)&&(_b%2!=0);
}

void BubbleSort(int arr[],int size , int (*f)(int,int) )
{
	register int i,j,swapped=0;
	for(i=0;i<size-1;i++)		
	{
		for(j=0;j<size-i-1;j++)		
		{
			if((*f)(arr[j],arr[j+1]))
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
