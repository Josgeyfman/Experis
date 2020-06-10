#include<stdio.h>
#include<stdlib.h>
#include "vector.h"
#include "queue.h"
#include "adt_error.h"

enum {CREATE=1,ENQUEUE,DEQUEUE,PRINT,SIZE,IS_EMPTY,DESTROY,EXIT};


int main()
{
	size_t  size;	
	int    	command,data,exit=0;
	queuep quePtr = NULL;
	ERRCODE result;
	do
	{	
		printf("\nPlease enter command:\nCreate queue: 1\nEnqueue: 2\nDequeue: 3");
		printf("\nPrint: 4\nSize: 5\nIs empty?: 6\nDestroy queue: 7\nExit: 8\n");
		scanf("%d",&command);
		switch(command)
		{
			
			case CREATE:	if(quePtr!=NULL)
					{
						
						printf("Create result: Queue exists, please destroy it first\n");
					}
					else
					{
						printf("Please enter initial size:\n");
						scanf("%lu",&size);
						if(size<1 ){
							printf("Create result: ERR_ILLEGAL_INPUT\n");
							break;
						}
						quePtr = QueueCreate(size);
						if(quePtr==NULL)
						{
							printf("\nCreate result: ERR_MEM_ALLOC\n");
							break;
						}
						printf("\nCreate result: Queue created\n");
					}
					break;
	
		        case ENQUEUE: 	printf("Please enter value to enqueue:\n");
					scanf("%d",&data);
					result = QueueEnqueue(quePtr,data);
					printf("ENQUEUE result: ");					
					PrintERRCODE(result);
					break;
			
		  	case DEQUEUE:  	result = QueueDequeue(quePtr,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The value dequeued is: %d\n" ,data);
					}
					printf("DEQUEUE result: ");
					PrintERRCODE(result);
					break;
			
		       case PRINT:      result = QueuePrint(quePtr);
					printf("Print result: ");
					if(result>0)
					{
						printf("ERR_SUCCESS printed %d values\n", result);
					}
					else
					{
						PrintERRCODE(result);
					}	
					break;
	
			case SIZE:     	data = QueueNumOfElements(quePtr);
					printf("The element num is: %d\n" ,data);
					break;

 	            case IS_EMPTY:	if(QueueIsEmpty(quePtr))	
					{
						printf("The stack is empty\n");
					}
					else
					{
						printf("The stack is not empty\n");
					}
					break;
	
		      case DESTROY:	if(quePtr!=NULL)
					{
						QueueDestroy(quePtr);
						quePtr=NULL;
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
	
	if(quePtr!=NULL)
	{
		QueueDestroy(quePtr);
		quePtr=NULL;
	}
	
	return 0;
}
