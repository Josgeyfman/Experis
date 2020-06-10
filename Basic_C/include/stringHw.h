#ifndef _STRING_HW_H_
#define _STRING_HW_H_

#include"adt_error.h"
#define LEN 18
#define TICKET_LEN 49
#define NUM_LEN 6
#define MAX_LEN 100

/*
	description: find the index of specific element in a sorted array
	input: _arr - sorted array
	      _data - value of elements
	      _size - size of array
	output: the index of the value in the array if found, -1 otherwise
*/
int BinarySearch(int _arr[],int _data,int _size);

/*
	description: choose randomly 6 out 49 numbers , and print lottery ticket accordingly
*/
void PrintLottoTicket();

/*
	description: remove all charecters from str1 that apear in str2 
	input: _str1 - string no 1
	      _str2 - string no 2
	output: ERR_SUCCESS if succeeded, ERRCODE otherwise
*/
ERRCODE Squeeze(char* _str1,const char* _str2);

/*
	description:find the location of str2 in str1 
	input: _str1 - string no 1
	       _str2 - string no 2
	output: Ehe index of the begining of str2 in str1, -1 otherwise
*/
int Location(const char* _str1,const char* _str2);

#endif
