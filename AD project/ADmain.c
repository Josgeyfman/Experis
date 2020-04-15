#include"AD.h"
#define INSERT 1
#define FIND 2
#define REMOVE 3
#define PRINT 4
#define EXIT 5

void PrintERRCODE(ERRCODE _err)
{
	printf("\nCommand result: ");
	switch(_err)
	{
		case ERR_SUCCESS: 	printf("ERR_SUCCESS\n"); 	break;
		case ERR_ILLEGAL_INPUT: printf("ERR_ILLEGAL_INPUT\n");  break;
		case ERR_UNDERFLOW: 	printf("ERR_UNDERFLOW\n"); 	break;
		case ERR_NOT_FOUND: 	printf("ERR_NOT_FOUND\n"); 	break;
		case ERR_MEM_ALLOC: 	printf("ERR_MEM_ALLOC\n"); 	break;
		case ERR_OVERLAP: 	printf("ERR_OVERLAP\n"); 	break;
	}
}

int main()
{
	size_t  size,blockSize;	
	int     command,roomNum,exit=0;
	float   startTime,endTime ;
	ad_p adPtr = NULL;
	meetp mp = NULL;
	ERRCODE result;
	printf("Please enter initial size:\n");
	scanf("%lu",&size);
	printf("Please enter blockSize:\n");
	scanf("%lu",&blockSize);
	if(size<1 || blockSize < 1){
		printf("ERR_ILLEGAL_INPUT\n");
		return -1;
	}
	adPtr = CreateAD(size,blockSize);
	if(adPtr==NULL)
	{
		printf("\nERR_MEM_ALLOC\n");
		return -1;
	}
	printf("\nAD created: ");
	PrintAD(adPtr);
	do
	{	
		printf("\nPlease enter command:\nInsert New Meeting: 1\nFind Meeting: 2\nRemove Meeting: 3");
		printf("\nPrint Diary: 4\nExit: 5\n");
		scanf("%d",&command);
		switch(command)
		{
			case INSERT: 	printf("Please enter meeting start time:\n");
					scanf("%f",&startTime);
					printf("Please enter meeting end time:\n");
					scanf("%f",&endTime);
					printf("Please enter meeting room number:\n");
					scanf("%d",&roomNum);
					result = CreateMeeting(&mp,startTime,endTime,roomNum);
					if(result==ERR_SUCCESS)
					{
						result = InsertMeet(adPtr,&mp);
					}					
					PrintERRCODE(result);
					break;
			
			case FIND:      printf("Please enter start time of meeting to be found:\n");
					scanf("%f",&startTime);
					result = FindMeet(adPtr,startTime);
					if(result>=0)
					{
						printf("The index of the meeting is: %d\n" ,result);
					}
					else
					{
						PrintERRCODE(result);			
					}
					break;
			
		
			case REMOVE:  	printf("Please enter start time of meeting to be removed:\n");
					scanf("%f",&startTime);
					result = RemoveMeet(adPtr,startTime);
					PrintERRCODE(result);
					break;
			
		         case PRINT:    result = PrintAD(adPtr);
					if(result>0)
					{
						printf("ERR_SUCCESS printed %d meetings\n", result);
					}
					else
					{
						PrintERRCODE(result);
					}	
					break;

			  case EXIT:	exit=1; 
					break;
	
		}
		
	}while(!exit);
	
	DestroyAD(adPtr);
	adPtr=NULL;
	mp =NULL;
	return 0;
}
