#include<stdio.h>
#include<stdlib.h>
#define MAX_HOUR 24.
#define MIN_HOUR 0.
#define MAX_MINUTE 0.6
#define MIN_MINUTE 0.


typedef enum {ERR_SUCCESS=0,ERR_ILLEGAL_INPUT=-1,ERR_UNDERFLOW=-2,ERR_NOT_FOUND=-3, ERR_MEM_ALLOC=-4,ERR_OVERLAP=-5} ERRCODE; 

typedef struct Meeting
{
	float startTime;
	float endTime;
	int roomNum;

} meet;

typedef meet* meetp;

typedef struct AD_T
{
	meetp * diary;
	size_t blockSize;
	size_t elementNum;
	size_t size; 
} ad_t; 
  
typedef ad_t* ad_p;

void PrintMeeting(meetp _meetPtr);

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
	Description: free ad_t and free it's diar
y
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




