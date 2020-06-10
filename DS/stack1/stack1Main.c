#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "adt_error.h"

#define MAX_LEN 100
enum {CREATE=1,PUSH,POP,TOP,PRINT,SIZE,IS_EMPTY,BRACKETS,CALC,DESTROY,EXIT};


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
			
			case ']': case '}': case ')': StackPop(_stPtr,&data); if(data != GetOppositeBracket(_str[i])){ return 0; } break;
			
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

static int LowerPriority(char _hi,char _low)
{
	if(_hi=='^' && _low !='^')
	{
		return 1;
	}
	if(_hi=='/' ||  _hi!='*')
	{
		if(_low=='+' ||  _low!='-')
		{
			return 1;
		}
	}
	return 0;
	

}	

static int IsOperator(char _data)
{
	if(_data=='+' || _data=='-' ||_data=='*' || _data=='/' || _data=='^')
	{
		return 1;
	}
	return 0;	
}

static int IsOperand(char _data)
{
	if(_data>='0' && _data<='9')
	{
		return 1;
	}
	if(_data>='a' && _data<='z')
	{
		return 1;
	}
	if(_data>='A' && _data<='Z')
	{
		return 1;
	}
	return 0;	
}


void StackCalc(stackp _stPtr , char _str[])
{
	int i=0,j=0;
	int data;
	char result[MAX_LEN];
	for(i=0;i<MAX_LEN;i++)
	{
		result[i]=' ';
	}

	i=0;
	if(!_stPtr || !_str || !StackIsEmpty(_stPtr))
	{
		printf("error result\n");
		return ;
	}
	while(_str[i]!='\0' || _str[i]!='\n')
	{
		if(IsOperand(_str[i]))
		{
			result[j++]=_str[i];
			result[j]='\0';
		}
		if(IsOperator(_str[i]))
		{
			while(!StackIsEmpty(_stPtr))
			{
				StackTop(_stPtr,&data);
				if(data!='(')
				{
					break;
				}
				if(IsOperator(data) && LowerPriority(_str[i],data))
				{
					break;
				}
				StackPop(_stPtr,&data);	
				result[j++]=data;
			}
			result[j++]=_str[i];
			result[j]='\0';

		}
		if(_str[i]==')')
		{
			while(data!='(' || !StackIsEmpty(_stPtr))
			{
				StackPop(_stPtr,&data);	
				result[j++]=data;
				result[j]='\0';
			}
			
		}	
		i++;
		printf("result is: %s\n" ,result);
	}
	while(!StackIsEmpty(_stPtr))
	{
		StackPop(_stPtr,&data);	
		result[j++]=data;
	}
	result[j]='\0';
	printf("result is: %s" ,result);
		
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
		printf("\nTop: 4\nPrint: 5\nSize: 6\nIs empty?: 7\nCheck Brackets: 8\nCalc Stack: 9\nDestroy Stack: 10\nExit: 11\n");
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
			case TOP:  	result = StackTop(stPtr,&data);
					if(result==ERR_SUCCESS)
					{
						printf("The value popped is: %d\n" ,data);
					}
					printf("Top result: ");
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
			case CALC :	printf("Please enter String to check:\n");
					scanf("%s",str);
					StackCalc(stPtr,str);	
					break;

		      case DESTROY:	if(stPtr!=NULL)
					{
						StackDestroy(stPtr);
						/*stPtr=NULL;*/
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
