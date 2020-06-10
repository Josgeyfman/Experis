#include<stdio.h>
#include<stdlib.h>
#include"stack.h"
#include"adt_error.h"

#define MAX_LEN 100
enum {CREATE=1,PUSH,POP,PRINT,SIZE,IS_EMPTY,BRACKETS,DESTROY,EXIT};


static char GetOppositeBracket(char _bracket)
{
	switch(_bracket)
	{
		case ']':  return '[';
		case '}':  return '{';
		default :  return '(';
	}
	
}

int AllBracktesClose(stackp _stPtr , char _str[])
{
	int i=0;
	int data;
	if(!_stPtr || !_str || !StackIsEmpty(_stPtr))
	{
		return -1;
	}
	while(_str[i]!='\0')
	{
		switch(_str[i])
		{
			case '[': case '{': case '(': StackPush(_stPtr,_str[i]); break;
			
			case ']': case '}': case ')': StackPop(_stPtr,&data); 
			
						      if(data != GetOppositeBracket(_str[i]))
						      {
							 return 0; 
						      } 
						      break;
			default: return -1;
		}
		i++;
	}
	if(StackIsEmpty(_stPtr))
	{
		return 1;
	}
	return 0;
		
}

int main()
{
	size_t  size,blockSize;	
	char str[MAX_LEN];
	int    	command,data,exit=0;
	stackp stPtr = NULL;
	ERRCODE result;
	do
	{	
		printf("\nPlease enter command:\nCreate Stack: 1\nPush: 2\nPop: 3");
		printf("\nPrint: 4\nSize: 5\nIs empty?: 6\nCheck Brackets: 7\nDestroy Stack: 8\nExit: 9\n");
		scanf("%d",&command);
		switch(command)
		{
			
			case CREATE:	if(stPtr!=NULL)
					{
						
						printf("Create result: Stack exists, please destroy it first\n");
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
						stPtr = StackCreate(size,blockSize);
						if(stPtr==NULL)
						{
							printf("\nCreate result: ERR_MEM_ALLOC\n");
							break;
						}
						printf("\nCreate result: Stack created\n");
					}
					break;
	
		        case PUSH: 	printf("Please enter value to push:\n");
					scanf("%d",&data);
					result = StackPush(stPtr,data);
					printf("Push result: ");					
					PrintERRCODE(result);
					break;
			
		  	 case POP:  	result = StackPop(stPtr,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The value popped is: %d\n" ,data);
					}
					printf("Pop result: ");
					PrintERRCODE(result);
					break;
			
		       case PRINT:      result = StackPrint(stPtr);
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
	
			case SIZE:     	data = StackNumOfElements(stPtr);
					printf("The element num is: %d\n" ,data);
					break;

 	            case IS_EMPTY:	if(StackIsEmpty(stPtr))	
					{
						printf("The stack is empty\n");
					}
					else
					{
						printf("The stack is not empty\n");
					}
					break;
		      
			case BRACKETS:	printf("Please enter String to check:\n");
					scanf("%s",str);
					if(stPtr!=NULL)
					{
						data = AllBracktesClose(stPtr,str);
						if(data==1)	
						{
							printf("All brackets close\n");
						}
						else if(data==0)
						{
							printf("Not all brackets close\n");
						}
						else
						{
							printf("Illegal input\n");
						}
					}
					else
					{
						printf("Illegal input\n");
					}
					break;	
		      case DESTROY:	if(stPtr!=NULL)
					{
						StackDestroy(stPtr);
						stPtr=NULL;
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
	
	if(stPtr!=NULL)
	{
		StackDestroy(stPtr);
		stPtr=NULL;
	}
	
	return 0;
}
