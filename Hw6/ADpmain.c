#include"ADp.h"

enum {LOAD=0,CREATE=1,INSERT=2,FIND=3,REMOVE=4,PRINT=5,SAVE=6,DESTROY=7,EXIT=8};

int main()
{
	size_t  size,blockSize;	
	int    	command,roomNum,exit=0;
	float   startTime,endTime ;
	ad_p adPtr = NULL;
	meetp mp = NULL;
	ERRCODE result;
	do
	{	
		printf("\nPlease enter command:\nLoad Diary: 0\nCreate Diary: 1\nInsert New Meeting: 2\nFind Meeting: 3");
		printf("\nRemove Meeting: 4\nPrint Diary: 5\nSave Diary: 6\nDestroy Diary: 7\nExit: 8\n");
		scanf("%d",&command);
		switch(command)
		{
			
			case LOAD:	result = LoadDiary(&adPtr);
					printf("Load result: ");					
					PrintERRCODE(result);
					break;	

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
	
			 case SAVE:	result = SaveDiary(adPtr);
					printf("Save result: ");
					PrintERRCODE(result);
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
