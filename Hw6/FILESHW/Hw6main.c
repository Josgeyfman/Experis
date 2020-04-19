#include"Hw6.h"

enum {FIRST_N=1,LAST_N=2,COMPARE=3,COUNT=4,WRITE=5,CHECK=6,PRINT=7,EXIT=8};

int main()
{
	int command,n,exit=0;
	char fname[MAX_LINE],fname2[MAX_LINE];
	ERRCODE result;
	do
	{	
		printf("\nPlease enter command:\nPrint first N lines: 1\nPrint last N lines: 2\nCompare two files: 3");
		printf("\nCount word instances in file: 4\nWrite people to file: 5\nCheck if File is Correct: 6");
		printf("\nPrint people file: 7\nExit: 8\n");
		scanf("%d",&command);
		switch(command)
		{
			
			case FIRST_N: 	printf("Please enter file name to read from\n");
					scanf("%s",fname);
					printf("Please enter number of lines to read\n");
					scanf("%d",&n);
					result = ReadFirstNlines(fname,n);
					PrintERRCODE(result);
				    	break;

			case LAST_N: 	printf("Please enter file name to read from\n");
					scanf("%s",fname);
					printf("Please enter number of lines to read\n");
					scanf("%d",&n);
					result = ReadLastNlines(fname,n);
					PrintERRCODE(result);
				    	break;
	
			case COMPARE: 	printf("Please enter file name to read from\n");
					scanf("%s",fname);
					printf("Please enter file name to read from\n");
					scanf("%s",fname2);
					result = CompareFiles(fname,fname2);
					PrintERRCODE(result);
				    	break;
			
			case COUNT:     printf("Please enter file name to read from\n");
					scanf("%s",fname);
					printf("Please enter the word to be looked up\n");
					scanf("%s",fname2);
					n = CountWordInstances(fname,fname2);
					if(n>=0)
					{
						printf("The number of instances of %s in %s is %d\n",fname2,fname,n);
					}
					else
					{
						printf("Error counting number of word's instances \n");
					}
				    	break;
	
			case WRITE: 	printf("Please enter file name to write into\n");
					scanf("%s",fname);
					printf("Please enter number of lines to write\n");
					scanf("%d",&n);
					result = WriteListingsToFile(fname,n);
					PrintERRCODE(result);
				    	break;

			case CHECK: 	printf("Please enter file name to read from\n");
					scanf("%s",fname);
					printf("Please enter number of listings to be checked\n");
					scanf("%d",&n);
					n =  IsDataCorrect(fname,n);
					if(n==1)
					{
						printf("\n%s is correct\n",fname);
					}
					else if(n==0)
					{
						printf("\n%s is not correct\n",fname);
					}
					else
					{
						printf("\nError counting number of word's instanses \n");
					}
					break;
			
			case PRINT: 	printf("Please enter file name to read from\n");
					scanf("%s",fname);
					result = PrintListings(fname);
					PrintERRCODE(result);
					break;

			case EXIT: 	exit = 1;
					break;
	
		}
		
	}while(!exit);
	
	return 0;
}
