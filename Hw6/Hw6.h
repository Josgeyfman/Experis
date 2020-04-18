#ifndef HW6_H
#define HW6_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_LINE 50
#define DATA_LEN 3

typedef enum {ERR_SUCCESS=0,ERR_SEEK=-1,ERR_FILE_OPEN=-2} ERRCODE;

/*
	Description: print first N lines of a file
	input: _name - file name
	       _n   - num of lines
	output: ERR_SUCCESS if succeeded, ERR_FILE_OPEN otherwise	 	
*/
ERRCODE ReadFirstNlines(char _name[] ,int _n); 

/*
	Description: print last N lines of a file
	input: _name - file name
	       _n   - num of lines
	output: ERR_SUCCESS if succeeded, ERR_FILE_OPEN or  ERR_SEEK otherwise	 	
*/
ERRCODE ReadLastNlines(char _name[] ,int _n);

/*
	Description: compare two files,print all lines where they differ
	input: _name1 - file name
	       _name2 - file name
`	output: ERR_SUCCESS if succeeded, ERR_FILE_OPEN otherwise	 	
*/
ERRCODE CompareFiles(char _name1[] ,char _name2[]);

/*
	Description: count all apperances of a word in a file
	input: _fname - file name
	       _word  - the word to be looked up 	
	output: the number of intstances if succeeded ,-1 otherwise
*/
int CountWordInstances(char _fname[] ,char _word[]);

/*
	Description: write people listings to a file
	input: _name - file name
	       _listingsNum  - number of people to write 
	output: ERR_SUCCESS if succeeded, ERR_FILE_OPEN otherwise	
*/
ERRCODE WriteListingsToFile(char _name[],int _listingsNum);

/*
	Description: check if file exists and if it's content is correct
	input: _name - file name
	       _data[][MAX_LINE]   - the content to be compared with	 	
	output: 1 if data is correct ,0 otherwise
*/
int IsDataCorrect(char _name[],int _lineNum);

/*
	Description: print all line of file
	input: _name - file name
	output: ERR_SUCCESS if succeeded, ERR_FILE_OPEN otherwise
*/
ERRCODE PrintListings(char _name[]);

/*
	Description: print error string by err number
	input: _err -number of error
*/
void PrintERRCODE(ERRCODE _err);

#endif
