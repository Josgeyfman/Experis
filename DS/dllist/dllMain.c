#include<stdio.h>
#include "dllist.h"

enum {CREATE=1,PUSHHEAD,POPHEAD,PUSHTAIL,POPTAIL,PRINT,COUNT,ISEMPTY,DESTROY,EXIT};

int main()
{
	size_t command,exit=0;
	int data;
	ERRCODE res;
	list* listp = NULL;
	do
	{	
		printf("\nPlease enter command:\nCreate list: 1\nAdd to head: 2\nRemove from head: 3");
		printf("\nAdd to tail: 4\nRemove from tail: 5\nPrint list: 6\nCount List: 7");
		printf("\nIs Empty?: 8\nDestroy List: 9\nExit: 10\n");		
		scanf("%lu",&command);
		switch(command)
		{
			
			case CREATE:    listp = ListCreate();
					if(listp)
					{
						printf("List created\n");
					}
					else
					{
						printf("Error Creating list\n");
					}
					break;

		        case PUSHHEAD: 	printf("Please enter data to push\n");
					scanf("%d",&data);
					res = ListPushHead(listp,data);
					if(res==ERR_SUCCESS)
					{
						printf("Added %d to head\n" ,data);
					}
					else
					{
						printf("Failed to add\n");
					}
					break;
			
		  	 case POPHEAD:  res = ListPopHead(listp,&data);
					if(res==ERR_SUCCESS)
					{
						printf("Removed %d from head\n" ,data);
					}
					else
					{
						printf("Failed to remove\n");
					}
					break;

			 case PUSHTAIL: printf("Please enter data to push\n");
					scanf("%d",&data);
					res = ListPushTail(listp,data);
					if(res==ERR_SUCCESS)
					{
						printf("Added %d to tail\n" ,data);
					}
					else
					{
						printf("Failed to remove\n");
					}
					break;
			
		  	 case POPTAIL:  res = ListPopTail(listp,&data);
					if(res==ERR_SUCCESS)
					{
						printf("Removed %d from tail\n" ,data);
					}
					else
					{
						printf("Failed to add\n");
					}
					break;
					
			case PRINT:	ListPrint(listp);
					break;

		        case COUNT:	data = ListCountItems(listp);
					printf("The number of items in the list is %d\n" ,data);
					break;
		      case ISEMPTY:     if(ListIsEmpty(listp))
					{
						printf("The list is empty\n");
					}
					else
					{
						printf("The list is not empty\n");
					}
					break;
	
		      case DESTROY:	if(listp!=NULL)
					{
						ListDestroy(listp);
						listp=NULL;
						printf("Destroy result: success\n");
						break;
					}
					else
					{
						printf("Destroy result: nothing to destroy\n");
					}
					break;
	
			  case EXIT:	exit=1; 
					break;
	
		}
		
	}while(!exit);
	
	if(listp)
	{
		ListDestroy(listp);
		listp=NULL;
	}
	return 0;
}

	
	
	
