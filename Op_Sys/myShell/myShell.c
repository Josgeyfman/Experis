#include <stdio.h>	/*I\O*/
#include <unistd.h>	/*fork*/
#include <string.h>	/*strcpy*/
#include <stdlib.h>	/*allocation*/
#include <sys/wait.h>   /*wait*/
#define MAX_LINE 80	/* The maximum length command */

static void FreeArgs(int _last ,char** _args)
{
	for(;_last>=0;_last--)
	{
		free(_args[_last]);
	}
	free(_args);
}


static char** CreateArgs(int _size)
{
	char** args;
	int i;
	args =	(char**)malloc(sizeof(char*)*_size);
	if(!args)
	{
		return NULL;
	}
	for(i=0;i<MAX_LINE/2+1;i++)
	{
		args[i]=(char*)malloc(sizeof(char)*MAX_LINE);
		if(!args[i]) 
		{
			FreeArgs(i-1,args);
		}
		args[i][0]=0;
	}
	return args;
}

static int execute(char* _read)
{
	int id,status;
	const char delim[3] = " \n";
	char *token;
	int size=2;	
	char** args;

	args = CreateArgs(MAX_LINE/2+1);
	if(!args)
	{
		return -1;
	}

	token = strtok(_read, delim); 		/* read first param */
	strcpy(args[0],token);			/* store first param*/
	while( token != NULL ) 
	{
		token = strtok(NULL, delim);
		if(token!=NULL)
		{
			strcpy(args[size-1],token);	/* store next param*/
			size++;
		}
	}
	args[size-1]=NULL;
	id=fork();					/* fork a child*/
	if(id<0)
	{
		printf("fork error\n");
		exit(-1);
	}
	else if(id>0) 
	{
		waitpid(-1,&status,0);			/* parent waiting for child*/
	}	
	else if(id==0)
	{

		execvp(args[0],args);
		printf("execvp error\n");
		exit(-1);
	}

	FreeArgs(MAX_LINE/2,args);
	
	return 0;

}

int main()
{

	int should_run = 1; 		/* flag to determine when to exit program */
	const char deli[2] = "\n";
	char read[MAX_LINE];
	
	read[0]=0;
		
	while(should_run){
		
		printf("my-shell>$ ");
		fflush(stdout);
		fgets(read,MAX_LINE,stdin);		/* read input*/
		if(!strcmp(read,""))
		{
			continue;			/* ignore emtpy command*/
		}
		if(!strcmp(read,"\n"))
		{
			 continue;			/* ignore empty command*/
		}
		
		strcpy(read,strtok(read, deli));	/* remove \n from read*/

		if(!strcmp(read,"exit")) 		/* exit command recieved*/
		{
			should_run=0;
		}
		else
		{
			if(0<execute(read))		/* fork(), execvp(), waitpid() in here */
			{
				return -1;
			}
		}

	}

	return 0;
}
