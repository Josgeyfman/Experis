#ifndef _BITOPS_H_
#define _BITOPS_H_

/*
	description: invert the bits of a given byte
	input: _byte - the byte to invert
	output: print the binary from of _byte after change
*/
void InvertBits(unsigned char _byte);

/*
	description: rotate left the bits of a given byte
	input: _byte - the byte to invert
	output: print the binary from of _byte after change
*/
ERRCODE RotateBits(unsigned char _byte ,size_t _n);

/*
	description: set n bits from a y byte to x byte with offset of p
	input: _x - the byte to invert
	       _y - the byte to invert
	       _n - amount of bit to set
	       _p - the offset
	output: print the binary from of _x after change
*/
ERRCODE SetBits(unsigned char _x ,size_t _n,int _p ,unsigned char _y);

/*
	description: compress every 2 chars in the string to 1 byte  (each char range 0 - 16 )
	input: _str - the string to compress
	output: ERR success if succeeded , ERR Illegal input otherwise
*/
ERRCODE CompressString(char _str[]);

#endif /*_BITOPS_H_*/
