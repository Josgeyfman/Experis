#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<adt_error.h>
#define BYTE_LEN 8
#define INT_LEN 32

typedef struct ByteReg
{
	unsigned char b :4;
	unsigned char a :4;
	
}bytereg;

static int TestBit(int _n,unsigned char _byte)
{
	unsigned char mask = (1<<_n);
	_byte &= mask;
	return (_byte==mask);
}

static void PrintBinary(unsigned char _byte)
{
	register int i;
	for(i=BYTE_LEN-1;i>=0;i--)
	{
		if(TestBit(i,_byte))
		{
			printf("1");
		}
		else
		{
			printf("0");
		}
	}
	printf("\n");
}

static unsigned char Compress(char _a ,char _b)
{
	unsigned char res=0;
	bytereg* p=&res;
	if(_b!= 0)
	{
		_b = _b -'a' +1;
	}
	_a= _a - 'a' + 1;
	p->a =_a;
	p->b =_b;
	return res;
	
}

static int IsStringValid(char _str[])
{
	char* curr = _str;
	while(*curr!='\0')
	{
		if(*curr!=0 && (*curr<'a' || *curr>'o'))
		{
			return 0;
		}
		curr++;
	}
	return 1;
}
	
ERRCODE CompressString(char _str[])
{
	register int i=0,j=0;
	int size ;
	if(!_str || !IsStringValid(_str))
	{
		return ERR_ILLEGAL_INPUT;
	}
	size = strlen(_str);
	while(i<size)
	{
		_str[j++] = Compress(_str[i],_str[i+1]);
		i+=2;
	}
	_str[j] = '\0';
	return ERR_SUCCESS;
}

static void PrintBinaryString(char* _str)
{
	int i,size;
	if(!_str)
	{
		return;
	}
	size = strlen(_str);
	for(i=0;i<size;i++)
	{
		PrintBinary(_str[i]);
	}

}

int main()
{
	char a[50] ="abcdefghijklmno";
	if(ERR_SUCCESS== CompressString(a))
	{
		PrintBinaryString(a);
	}
	return 0;
}
