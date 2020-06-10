#include<stdio.h> /*printf*/
#include<math.h>  /*pow*/
#define BYTE_LEN 8
#define INT_LEN sizeof(int)*BYTE_LEN
#define CHAR_LEN 256
typedef enum {FIRST=1,SECOND,THIRD} Num;

static int  ToggleBit(int _n,unsigned char  _int)
{ 
	unsigned int mask = (1<<_n);
	 _int ^=mask;
	return _int;
}

static int TestBit(int _n,unsigned int _int)
{
	unsigned int mask = (1<<_n);
	_int &= mask;
	return (_int==mask);
}

static int InvertBits(int _int ,size_t _from ,size_t _to)
{
	register int i;
	for(i=_from;i<=_to;i++)
	{
		_int = ToggleBit(i,_int);
	}
	return _int;
}


static int Test4Bits(size_t _start,unsigned int _int)
{
	int i,val = 0;
	for(i=3;i>=0;i--)
	{
		if(TestBit(_start--,_int))
		{
			val += pow(2,i);
		}
	}
	return val;
}

void PrintHex(unsigned int _int)
{
	register int i,val;
	printf("0x");
	for(i=INT_LEN-1;i>=0;i-=4)
	{
		val = Test4Bits(i,_int);
		switch(val)
		{
			case 0:  break;
			case 10: printf("A"); break;
			case 11: printf("B"); break;
			case 12: printf("C"); break;
			case 13: printf("D"); break;
			case 14: printf("E"); break;
			case 15: printf("F"); break;
			default : printf("%d",val);
		}
	}
	printf("\n");
}

int Abs(int _int)
{
	return TestBit(INT_LEN-1,_int) ? InvertBits(_int,0,INT_LEN-1) + 1 : _int ;
}


int Flip2Bits(int _int,size_t _first,size_t _second)
{
	if(_first==_second || _second>=INT_LEN || _first>=INT_LEN)
	{
		return _int;
	}
	_int = ToggleBit(_first,_int);
	_int = ToggleBit(_second,_int);
	return _int;
}

int FlipBitsInRange(int _int,size_t _from,size_t _to)
{
	if(_from >_to || _from>=INT_LEN || _to>=INT_LEN)
	{
		return _int;
	}
	return InvertBits(_int,_from,_to);
}

int RotateRight(unsigned int _int ,size_t _n)
{
	register int i;
	int mask;
	_n %= INT_LEN;
	for(i=0;i<_n;i++)
	{
		mask = TestBit(0,_int);
		_int = (_int >>  1 ) | mask;
		
	}
	return _int;
}

int RotateLeft(unsigned int _int ,size_t _n)
{
	register int i;
	int mask;
	_n %= INT_LEN;
	for(i=0;i<_n;i++)
	{
		mask = TestBit(INT_LEN-1,_int);
		_int = (_int <<  1 ) | mask;
	}
	return _int;
}

long BitwiseAdd(int _int1, int _int2)
{
	long res, long2,carry = 0;
	res = (long)_int1;
	long2  = (long)_int2;
	while (long2 != 0) 
	{ 
		carry = res & long2;   
		res = res ^ long2;  
		long2 = carry << 1; 
	} 
	return res; 
}

static int lutFlag;
static int lut[CHAR_LEN];
static int 1n3[CHAR_LEN];
static int 2n3[CHAR_LEN];
static int 3n3[CHAR_LEN];


static int TestCharBit(char _n,unsigned char _char)
{
	unsigned char mask = (1<<_n);
	_char &= mask;
	return (_char==mask);
}

static int Find(unsigned char _char,Num _num)
{
	unsigned char i=0;
	while(_num>0)
	{
		_num-=TestCharBit(i++,_char);
	}
	return i;
}

static void BuildLuts()
{
	unsigned char i;
	for(i=0;i<CHAR_LEN-1;i++)
	{
		if(lut[i]==3)
		{
			1n3[i]=Find(i,FIRST);
			2n3[i]=Find(i,SECOND);
			3n3[i]=Find(i,THIRD);
		}
		else
		{
			1n3[i]=-1;
			2n3[i]=-1;
			3n3[i]=-1;
		}
	}

}

int FindThirdTurnedIntBit(unsigned int _int)
{
	register int i,count=0;
	for(i=0;i<4;i++)
	{

	}

}

static int NumOfTurnedBits(unsigned char _char)
{
	register int i,count=0;
	for(i=0;i<BYTE_LEN;i++)
	{
		count+=TestCharBit(i,_char);
	}
	return count;
}

static void BuildLut()
{
	unsigned char i;
	for(i=0;i<CHAR_LEN-1;i++)
	{
		lut[i] = NumOfTurnedBits(i);
		
	}
	lutFlag=1;
}

int NumOfTurnedIntBits(unsigned int _int)
{
	int i,sum=0;
	unsigned int mask= 0xFF;
	unsigned char curr;
	for(i=0;i<4;i++)
	{
		curr = _int & mask;
		sum += lut[curr];
		mask <<= 8;
		
	}
	return sum;
}

int main()
{
	int a =165;
	int b = -165;
	PrintHex(b);
	printf("abs of %d is %d\n",b,Abs(b));
	if(!lutFlag)
	{
		BuildLut();
		BuildLuts();
	}
	printf("num of bit in %d is %d\n",a,NumOfTurnedIntBits(a));
	printf("flip2bits (0-1) 165 ->166 (%d -> %d)\n",a,Flip2Bits(a,0,1));
	printf("FlipBitsInRange (7-31) -165 -> 219 ( %d is %d)\n",b,FlipBitsInRange(b,7,31));
	printf("RotateRight %d >> 7 is %d\n",b,RotateRight(b,7));
	printf("RotateLeft  %d << 7 is %d\n",b,RotateLeft(b,7));
	printf("BitwiseAdd  %d+%d is %ld\n",2147483647,2147483647,BitwiseAdd(2147483647,2147483647));
	return 0;
}
