#ifndef _BITOPS3_H_
#define _BITOPS3_H_

/*print int in hex format*/
void PrintHex(unsigned int _int);

/*get absolute value of integer*/
int Abs(int _int);

/*count number of turned on bits*/
int NumOfTurnedBits(unsigned int _int);

/*switch the values of 2 bits in an integer*/
int Flip2Bits(int _int,size_t _first,size_t _second);

/*invert all bits in a given range*/
int FlipBitsInRange(int _int,size_t _from,size_t _to);

/*rotate right an integer n times*/
int RotateRight(unsigned int _int ,size_t _n);

/*rotate left an integer n times*/
int RotateLeft(unsigned int _int ,size_t _n);

/*add 2 integers bitwise*/
long BitwiseAdd(int _int1, int _int2);

#endif /*_BITOPS3_H_*/
