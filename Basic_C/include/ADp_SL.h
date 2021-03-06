#ifndef ADP_H
#define ADP_H
#include<stdio.h>
#include<stdlib.h>
#define MAX_HOUR 24.
#define MIN_HOUR 0.
#define MAX_MINUTE 0.6
#define MIN_MINUTE 0.
#define MAX_LINE 100

typedef enum {ERR_SUCCESS=0,ERR_ILLEGAL_INPUT=-1,ERR_UNDERFLOW=-2,ERR_NOT_FOUND=-3, ERR_MEM_ALLOC=-4,ERR_OVERLAP=-5,ERR_FILE_OPEN=-6,ERR_ALREADY_EXISTS=-7} ERRCODE; 

typedef struct Meeting meet;

typedef struct AD_T ad_t; 

typedef meet* meetp;  

typedef ad_t* ad_p;

/*
	Description: Save diary to diary.txt file in the local folder
	input: _adPtr - pointer to an ad_t	 	
	output: ERR_SUCCESS if saved, ERR_FILE_OPEN otherwise
*/
ERRCODE SaveDiary(ad_p _adPtr);

/*
	Description: load diary.txt file to a new diary instance
	input: _adPtr - pointer to an ad_t	 	
	output: ERR_SUCCESS if saved, ERRCODE otherwise
*/
ERRCODE LoadDiary(ad_p* _adPtr);

/*
	Description: allocate an ad_t with given size and block size
	input: _initialSize - the size of diary to be allocated
	       _blockSize   - block size when resizing diary	 	
	output: pointer to allocted ad_t ,NULL otherwise
*/
ad_p CreateAD(size_t _initialSize,size_t _blockSize);

/*
	Description: allocate a meeting with given start time, end time and room number
	input: _newMeet   - a poiter to the meeting to be allocated ,
	       _startTime - start time of meeting
	       _endTime	  - end time of meeting
	       _roomNum  - room number of meeting
	output: ERR_SUCCESS if allocated, ERRCODE otherwise
*/
ERRCODE CreateMeeting(meetp* _newMeet,float _startTime,float _endTime ,int _roomNum);

/*
	Description: insert a new meeting to an ad_t diary
	input: _adPtr	 - pointer to an ad_t
	       _newMeet	 - pointer to a new meeting
	output: ERR_SUCCESS if allocated, ERRCODE otherwise
*/
ERRCODE InsertMeet(ad_p _adPtr,meetp* _newMeet);

/*
	Description: remove a meeting from the ad_t diary with a given start time
	input: _adPtr	 - pointer to an ad_t
	       _startTime -  meeting start time
	output: ERR_SUCCESS if removed, ERRCODE otherwise
*/
ERRCODE RemoveMeet(ad_p _adPtr,float _startTime);

/*
	Description: free ad_t and free it's diary
	input: adPtr - pointer to an ad_t
*/
void DestroyAD(ad_p _adPtr);

/*
	Description: print ad_t details and all it's meeting details
	input: adPtr - pointer to an ad_t
	output: the number of meetings printed, ERRCODE otherwise
*/
int PrintAD(ad_p _adPtr);

/*
	Description: find a meeting in an ad_t diary by it's start time
	input: _adPtr	  - pointer to an ad_t
	       _startTime -  meeting start time
	output: if found will return index of meeting in ad_t diary ,negative number otherwise
*/
int FindMeet(ad_p _adPtr,float _startTime);

/*
	Description: print error string by err number
	input: _err -number of error
*/
void PrintERRCODE(ERRCODE _err);

#endif



