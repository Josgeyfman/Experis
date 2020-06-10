#include<stdio.h>
#include<stdlib.h>
#include "stack.h"
#include "adt_error.h"

#define MAX_LEN 100

static int IsLowerPriority(char _hi,char _low)
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


/*void StackCalc(char _str[])
{
	int i=0,j=0;
	int data;
	char result[MAX_LEN];
	stackp stPtr = StackCreate(MAX_LEN,0);

	if(!stPtr || !_str || !StackIsEmpty(stPtr))
	{
		printf("error result\n");
		StackDestroy(stPtr);
		return ;
	}
	
	while(_str[i]!='\0' && _str[i]!='\n')
	{
		if(IsOperand(_str[i]))
		{
			result[j++]=_str[i];
		}
		else if(_str[i]=='(')
		{
			StackPush(stPtr,_str[i]);

		}
		else if(_str[i]==')')
		{
			StackPrint(stPtr);
			StackPop(stPtr,&data);	
			while(!StackIsEmpty(stPtr) && data!='(')
			{
				result[j++]=data;
				printf("poped nad insert %c\n" ,data);
				StackPop(stPtr,&data);	
				StackTop(stPtr,&data);
				
			}
			if(StackIsEmpty(stPtr) && data!='(')
			{
				printf("error invalid expression\n");
				StackDestroy(stPtr);				
				return;
			}
			printf("poped %c\n" ,data);
		}
		else if(IsOperator(_str[i]))
		{
			StackTop(stPtr,&data);
			while(!StackIsEmpty(stPtr)  && !IsLowerPriority(_str[i],data))
			{
				result[j++]=data;
				StackPop(stPtr,&data);
				StackTop(stPtr,&data);	
				
			}
			StackPush(stPtr,_str[i]);
		}
		i++;
		
	}
	while(!StackIsEmpty(stPtr))
	{
		StackPop(stPtr,&data);	
		result[j++]=data;
	}
	result[j++]='\0';
	printf("result is: %s\n" ,result);
	StackDestroy(stPtr);
		
}*/


void InfixToPostfix(char* _str) 
{ 
	int i=0,j=0;
	int data;
	char result[MAX_LEN];
	stackp stPtr = StackCreate(MAX_LEN,0);

	if(!stPtr || !_str || !StackIsEmpty(stPtr))
	{
		printf("error result\n");
		StackDestroy(stPtr);
		return ;
	}
	

	while ( _str[i]) 
	{ 
		if (IsOperand(_str[i]))
		{ 
	    		result[j++] = _str[i]; 
		}
		else if (_str[i] == '(') 
		{
	   		StackPush(stPtr,_str[i]);
		}
		else if (_str[i] == ')') 
		{ 
			StackTop(stPtr,&data);
			while (!StackIsEmpty(stPtr) && data != '(') 
			{
				StackPop(stPtr,&data);	
				result[j++]=data;
				StackTop(stPtr,&data);
			}
			if (!StackIsEmpty(stPtr) && data != '(') 
			{
				return ; 			          
			}   
			else
			{
				StackPop(stPtr,&data);	
			}
		 
		else 
		{ 
	    		while (!StackIsEmpty(stPtr) && !IsLowerPriority(_str[i],data)) 
			{
				StackPop(stPtr,&data);	
				result[j++]=data;
				StackTop(stPtr,&data);
			} 
		    	StackPush(stPtr,_str[i]);
		} 
	  	i++;
	} 
  
	while (!StackIsEmpty(stPtr)) 
	{
		StackPop(stPtr,&data);	
		result[j++]=data; 
	}
	result[j++] = '\0'; 
	printf( "%s", result );
	StackDestroy(stPtr); 
}



int main()
{
	char str[MAX_LEN];
	printf("please enter string\n");
	scanf("%s",str);
	printf("string entered:\n%s\n" ,str);
	InfixToPostfix(str);
	return 0;	
}




