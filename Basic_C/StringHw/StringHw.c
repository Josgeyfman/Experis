#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"stringHw.h"


int BinarySearch(int _arr[],int _data,int _size)
{
	int low=0,high = _size-1;
	int mid;
	if(!_arr || _arr[low]>_data || _arr[high]<_data)	
	{
		return -1;
	}
	while(high>=low)
	{
		mid = (high + low) /2;
		if(_arr[mid]==_data)
		{
			return mid;
		}
		if(_arr[mid]<_data)
		{
			low=mid+1;
		}
		else
		{
			high=mid-1;
		}
	}
	return -1;

}

static int Exists(int _data, int _arr[],int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		if(_data==_arr[i])
		{
			return 1;
		}
	}
	return 0;
}

static void PrintLines(int _chosen[])
{
	int i;	
	for(i=1;i<=TICKET_LEN;i++)
	{
		if(Exists(i,_chosen,NUM_LEN))
		{
			printf("+");			
		}
		else
		{
			printf("-");	
		}
		if(i%10==0)
		{
		 	printf("\n");
		}

	}
	printf("\n");

}

void PrintLottoTicket()
{
	int currentNum=0,chosen[NUM_LEN];
	int tmp;
	time_t t;
	srand((unsigned) time(&t));
	while(currentNum<NUM_LEN)
	{
		tmp = 1 + rand() % TICKET_LEN;
		if(!Exists(tmp,chosen,currentNum))
		{
			chosen[currentNum++]=tmp;
		}
	}	
	PrintLines(chosen);
}

ERRCODE Squeeze(char* _str1,const char* _str2)
{
	char* token;
	/*char result[MAX_LEN] = "";*/
	if(!_str1 || !_str2)
	{
		return ERR_ILLEGAL_INPUT;
	}
	token = strtok(_str1,_str2);
	while(token)
	{
		strcat(_str1,token);
		token = strtok(NULL,_str2);
		
	}
	/*strcpy(_str1,result);*/
	return ERR_SUCCESS;
}

int Location(const char* _str1,const char* _str2)
{
	const char* curr = _str1;
	int size1,size2;
	if(!_str1 || !_str2)
	{
		return -1;
	}
	size1 = strlen(_str1);
	size2 = strlen(_str2);
	while(*curr!= '\0' && size1>=size2 )
	{
		if(strncmp(curr,_str2,size2)==0)
		{	
			return curr -_str1;
		}
		curr++;
		size1--;
	}
	return -1;
	
}

int main()
{
	int i,arr[LEN]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17};
	char str1[MAX_LEN] = "ABCDEFABCBDEDEFABCDEF";
	char* str2="BDE";
	i=BinarySearch(arr,17,17);
	printf("index of 5 is %d\n",i);
	PrintLottoTicket();
	i = Location(str1,str2);
	printf("Location of BDE %d\n",i);
	Squeeze(str1,str2);
	printf("squeeze result  %s\n",str1);
	return 0;
}
