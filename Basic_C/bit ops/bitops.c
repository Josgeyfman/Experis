#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<adt_error.h>
#define BYTE_LEN 8
#define INT_LEN 32

static char SetBit(int _n,unsigned char _byte)
{
	unsigned char mask = (1<<_n);
	 _byte |= mask;
	return _byte;
}

static char ToggleBit(int _n,char _byte)
{
	unsigned char mask = (1<<_n);
	 _byte ^=mask;
	return _byte;
}

static char ClearBit(int _n,unsigned char _byte)
{
	unsigned char mask = ~(1<<_n);
	_byte &= mask;
	return _byte;
}

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

int NumOfTurnedBits(unsigned char _byte)
{
	register int i,count=0;
	for(i=0;i<BYTE_LEN;i++)
	{
		if(TestBit(i,_byte))
		{
			count++;
		}
	}
	return count;
}

void InvertBits(unsigned char _byte)
{
	register int i;
	printf("before invert ");
	PrintBinary(_byte);
	for(i=0;i<BYTE_LEN;i++)
	{
		_byte = ToggleBit(i,_byte);
	}
	printf("after invert ");
	PrintBinary(_byte);
}

ERRCODE RotateBits(unsigned char _byte ,size_t _n)
{
	register int i;
	unsigned char tmp;
	if(_n > 8)
	{
		return ERR_ILLEGAL_INPUT;
	}
	printf("before rotate ");
	PrintBinary(_byte);
	for(i=0;i<_n;i++)
	{
		tmp = TestBit(0,_byte);
		_byte >>=  1;
		if(tmp)
		{
			_byte = SetBit(7,_byte);
		}
	}
	printf("after rotate ");
	PrintBinary(_byte);
	return ERR_SUCCESS;
}

ERRCODE SetBits(unsigned char _x ,size_t _n,int _p ,unsigned char _y)
{
	register int i;
	unsigned char tmp;
	if(_n > 7 || _p>7 || _p<0 )
	{
		return ERR_ILLEGAL_INPUT;
	}
	printf("before set bits x ");
	PrintBinary(_x);
	printf("before set bits y ");
	PrintBinary(_y);
	printf("n:%lu, p:%d\n",_n,_p);
	for(i=_n-1;i>=0;i--)
	{
		tmp = TestBit(i,_y);
		if(tmp)
		{
			_x = SetBit(_p,_x);
		}
		else
		{
			_x = ClearBit(_p,_x);
		}
		_p--;
		_p = (_p < 0) ? 7 : _p ;
	}
	printf("after set bits x ");
	PrintBinary(_x);
	return ERR_SUCCESS;
}

static unsigned char Compress(char _a ,char _b)
{
	unsigned char res=0;
	
	if(_b!= 0)
	{
		_b = _b -'a' +1;
	}
	_a= _a - 'a' + 1;
	res = _a << 4;
	res |= _b;
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

static int TestIntBit(int _n,unsigned int _int)
{
	unsigned int mask = (1<<_n);
	_int &= mask;
	return (_int==mask);
}

static void PrintBinaryInt(unsigned int _int)
{
	register int i;
	for(i=INT_LEN-1;i>=0;i--)
	{
		if(TestIntBit(i,_int))
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

static unsigned int SetIntBit(int _n,unsigned int _int)
{
	unsigned int mask = (1<<_n);
	 _int |= mask;
	return _int;
}

static unsigned int ClearIntBit(int _n,unsigned int _int)
{
	unsigned int mask = ~(1<<_n);
	_int &= mask;
	return _int;
}


ERRCODE SetIntBits(unsigned int _x ,int _i,int _j ,int _val)
{
		int  start,end;
		if(_j>31 || _i>31)
		{
			return ERR_ILLEGAL_INPUT;
		}
		start =_i;
		end =_j;
		printf("before SetIntBits val:%d ,i:%d ,j:%d  x:%d\n",_val,_i,_j,_x);
		PrintBinaryInt(_x);
		if(_val)
		{
			while(start!=end)
			{
				_x = SetIntBit(start--,_x);
				if(start<0)
				{
					start = INT_LEN-1;
				}
			}
			_x = SetIntBit(start,_x);
		}
		else
		{
			while(start!=end)
			{
				_x = ClearIntBit(start--,_x);
				if(start<0)
				{
					start = INT_LEN-1;
				}
			}
			_x = ClearIntBit(start,_x);
			
		}
		PrintBinaryInt(_x);	
		return ERR_SUCCESS;
}

int main()
{
	char a[50] ="abc";
	unsigned char b=192,d=255 ,e=0;
	unsigned int x = 0;
	RotateBits(b,7);
	InvertBits(b);
	SetBits(d,4,2,e);
	if(ERR_SUCCESS== CompressString(a))
	{
		PrintBinaryString(a);
	}
	SetIntBits(x,31,1,1);
	return 0;
}
