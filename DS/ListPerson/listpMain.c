#include<stdio.h>
#include "listp.h"

enum {ADDHEAD=1,REMHEAD,PRINT,ADDIND,REMIND,ADDREC,REMREC,DESTROY,EXIT};



int main()
{
	size_t age,id,command,exit=0;
	char name[MAX_LEN];
	person* head = NULL;
	person* newPerson = NULL;
	do
	{	
		printf("\nPlease enter command:\nAdd to head: 1\nRemove from head: 2\nPrint: 3");
		printf("\nAdd to index: 4\nRemove from index: 5\nAdd index recursivly: 6\nRemove index recursivly: 7");
		printf("\nDestroy List: 8\nExit: 9\n");		
		scanf("%lu",&command);
		switch(command)
		{
			
	
		        case ADDHEAD: 	GetPersonData(&id,name,&age);
					newPerson = CreateNewPerson(id,name,age);
					head = ListInsertHead(head,newPerson);
					printf("Added new head:\n");
					PrintPerson(head);
					printf("\n");
					break;
			
		  	 case REMHEAD:  head = ListRemoveHead(head,&newPerson);
					printf("person removed:\n");
					PrintPerson(newPerson);
					printf("\n");
					break;

			case PRINT:	ListPrint(head);
					break;

		       case ADDIND:  	GetPersonData(&id,name,&age);
					newPerson = CreateNewPerson(id,name,age);
					head = ListInsertByKey(head,id,newPerson);
					break;
	
			case REMIND:    printf("Please enter the id of person to be removed\n");
					scanf("%lu",&id);
					head = ListRemoveByKey(head,id,&newPerson);
					printf("person removed:\n");
					PrintPerson(newPerson);
					break;
	
 	          	case ADDREC:	GetPersonData(&id,name,&age);
					newPerson = CreateNewPerson(id,name,age);
					head = ListInsertByKeyRec(head,id,newPerson);
					printf("person added recursivly\n");
					break;
		      
			case REMREC:	printf("Please enter the id of person to be removed\n");
					scanf("%lu",&id);
					head = ListRemoveByKeyRec(head,id,&newPerson);
					printf("person removed rec:\n");
					PrintPerson(newPerson);
					break;

		      case DESTROY:	if(head!=NULL)
					{
						ListDestroy(head);
						head=NULL;
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
	
	if(head)
	{
		ListDestroy(head);
		head=NULL;
	}
	newPerson=NULL;
	return 0;
}

	
	
	
