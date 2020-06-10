#include"ADp.h"
#define CREATE 1
#define INSERT 2
#define FIND 3
#define REMOVE 4
#define PRINT 5
#define DESTROY 6
#define EXIT 7



void PrintERRCODE(ERRCODE _err)
{
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
	char x = 150;
	ad_p adPtr = NULL;
	meetp mp = NULL;
	ERRCODE result;
	printf("%d\n" ,x);
	do
	{	
		printf("\nPlease enter command:\nCreate Diary: 1\nInsert New Meeting: 2\nFind Meeting: 3\nRemove Meeting: 4");
		printf("\nPrint Diary: 5\nDestroy Diary: 6\nExit: 7\n");
		scanf("%d",&command);
		switch(command)
		{
			case CREATE:	if(adPtr!=NULL)
					{
						
						printf("Create result: Diary exists, please destroy it first\n");
					}
					else
					{
						printf("Please enter initial size:\n");
						scanf("%lu",&size);
						printf("Please enter blockSize:\n");
						scanf("%lu",&blockSize);
						if(size<1 || blockSize < 1){
							printf("Create result: ERR_ILLEGAL_INPUT\n");
							break;
						}
						adPtr = CreateAD(size,blockSize);
						if(adPtr==NULL)
						{
							printf("\nCreate result: ERR_MEM_ALLOC\n");
							break;
						}
						printf("\nCreate result: AD created\n");
					}
					break;
	
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
					printf("Insert result: ");					
					PrintERRCODE(result);
					break;
			
			case FIND:      printf("Please enter start time of meeting to be found:\n");
					scanf("%f",&startTime);
					result = FindMeet(adPtr,startTime);
					printf("Find result: ");
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
					printf("Remove result: ");
					PrintERRCODE(result);
					break;
			
		         case PRINT:    result = PrintAD(adPtr);
					printf("Print result: ");
					if(result>0)
					{
						printf("ERR_SUCCESS printed %d meetings\n", result);
					}
					else
					{
						PrintERRCODE(result);
					}	
					break;
			  case DESTROY:	if(adPtr!=NULL)
					{
						DestroyAD(adPtr);
						adPtr=NULL;
						printf("Destroy result: ERR_SUCCESS\n");
						break;
					}
					else
					{
						printf("Destroy result: ERR_ILLEGAL_INPUT\n");
					}
					break;
	
			  case EXIT:	exit=1; 
					break;
	
		}
		
	}while(!exit);
	
	mp =NULL;
	if(adPtr!=NULL)
	{
		DestroyAD(adPtr);
		adPtr=NULL;
	}
	
	return 0;
}
