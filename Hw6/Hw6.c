#include"Hw6.h"

ERRCODE ReadFirstNlines(char _name[] ,int _n) 
{
	FILE* fp;
	char line[MAX_LINE];
	int i=0;       
	fp = fopen(_name, "r");        	
	if(fp == NULL)  
	{                    
		return ERR_FILE_OPEN;
	}
	while (!feof(fp) && i<_n ) 
	{
		fgets ( line, sizeof line, fp ); 
		printf("%s",line);
		i++;
	}
	printf("\n");
	fclose(fp);
	return ERR_SUCCESS;
}

ERRCODE ReadLastNlines(char _name[] ,int _n) 
{
	FILE* fp;
	char line[MAX_LINE];
	int lineCount=0;       
	long pos;
	fp = fopen(_name, "r");        	
	if(fp == NULL)  
	{                    
		return ERR_FILE_OPEN;
	}

	if(!fseek(fp,0,SEEK_END))
	{
		pos = ftell(fp); 

		while (pos>0) 
		{ 
			if (!fseek(fp, --pos, SEEK_SET)) 
			{ 
				if (fgetc(fp) == '\n')
				{
					if ( lineCount == _n) 
					{
						break;
					}
					lineCount++;
				}
			}
			else
			{
				fclose(fp);
				return ERR_SEEK;
			} 
			fseek(fp, pos, SEEK_SET);
		} 
	}
	lineCount=0;
	while (!feof(fp) && lineCount<_n ) 
	{
		fgets ( line, sizeof(line), fp ); 
		printf("%s",line);
		lineCount++;
	}
	printf("\n");
	fclose(fp);
	return ERR_SUCCESS;
}

int CountLines(FILE *_fp)
{
	int i = 0;
	char line[MAX_LINE];
	
	if(!fseek(_fp,0,SEEK_SET))
	{
		while (!feof(_fp)) 
		{
			fgets ( line, sizeof line, _fp ); 
			i++;
		}
	}
	
	return i;
}

void PrintRestOfLines(int _rest,int _lineCount,int* _errorCountPtr)
{
	int i;
	for(i=1;i<_rest;i++)
	{
		printf("files differ on line %d\n",++_lineCount);
		(*_errorCountPtr)++;
	}
}

ERRCODE CompareFiles(char _name1[] ,char _name2[])
{
	FILE *fp1 , *fp2;
	char line1[MAX_LINE],line2[MAX_LINE];
	int lineCount=0,errorCount=0,rest; 
	
	fp1 = fopen(_name1, "r");  
	fp2= fopen(_name2, "r");   

	if(fp1 == NULL || fp2 == NULL)  
	{                    
		return ERR_FILE_OPEN;
	}

    	rest  =  CountLines(fp1);
	rest -=  CountLines(fp2);
	rest  =  (rest > 0)? rest : (-1)*rest ;

	if(!fseek(fp1,0,SEEK_SET) && !fseek(fp2,0,SEEK_SET))
	{
		while (!feof(fp1) && !feof(fp2) ) 
		{
			lineCount++;
			fgets( line1, sizeof line1, fp1 ); 
			fgets( line2, sizeof line2, fp2 ); 
			if( strcmp(line1,line2) != 0 )
			{
				printf("files differ on line %d\n",lineCount);
				errorCount++;
			}
		}
	
		PrintRestOfLines(rest,lineCount,&errorCount);
		
		if(0==errorCount)
		{
			printf("files are equal\n");
		}
	}
	else
	{
		return ERR_SEEK;
	}
	fclose(fp1);
	fclose(fp2);
	return ERR_SUCCESS;
}

int CountWordInstances(char _fname[] ,char _word[])
{
	FILE* fp;
	char cword[MAX_LINE] ,currChar;
	int wordCount=0 ,i=0;       
	fp = fopen(_fname, "r");        	
	if(fp == NULL)  
	{                    
		return -1;
	}
	while(currChar != EOF)
	{
		currChar = fgetc(fp);
		if(currChar == ' ' || currChar == '\n')
		{
			cword[i]='\0';
			i=0;
			if(0==strcmp(cword,_word))
			{
				wordCount++;
			}
		}
		else
		{
			cword[i++]=currChar;
		}

	}
	
	fclose(fp);
	return wordCount;
}

void GetListingData(char* _fname, char* _lname,char* _email)
{
	printf("please enter first name\n");
	scanf("%s",_fname);
	printf("please enter last name\n");
	scanf("%s",_lname);
	printf("please enter email\n");
	scanf("%s",_email);
}


ERRCODE WriteListingsToFile(char _name[],int _listingsNum)
{
	FILE* fp;
	char fname[MAX_LINE],lname[MAX_LINE],email[MAX_LINE];
	
	int i;       
	fp = fopen(_name, "w");        	
	if(fp == NULL)  
	{                    
		return ERR_FILE_OPEN;
	}
	
	for(i=0;i<_listingsNum;i++)
	{
		GetListingData(fname,lname,email);
		fprintf(fp,"%-20s%-20s%s\n",fname,lname,email);
	}
	
	fclose(fp);
	return	ERR_SUCCESS;
}

void FreeALLData(char*** _data,int _row )
{
	int i,j;	
	if(_data!=NULL)
	{
		for(i=0;i<_row;i++)
		{
			if(_data[i]!=NULL)
			{
				for(j=0;j<DATA_LEN;j++)
				{
					if(_data[i][j]!=NULL)
					{
						free(_data[i][j]);
					}
				}
				free(_data[i]);
			}
		}
		free(_data);	
	}
}


char*** CreateDataArray(int _lineNum)
{
	char*** data ;	
	int i,j;
	data =(char***)malloc(_lineNum*sizeof(char**));
	if(data!=NULL)
	{
		for(i=0;i<_lineNum;i++)
		{
			data[i] =(char**)malloc(DATA_LEN*sizeof(char*));
			if(data[i]!=NULL)
			{
				for(j=0;j<DATA_LEN;j++)
				{
					data[i][j] =(char*)malloc(MAX_LINE*sizeof(char));
					if(data[i][j]==NULL)
					{
						FreeALLData(data,i);
					}
				}
			}
			else
			{
				FreeALLData(data,i);
			}
		}
		return data;	
	}
	return NULL;
	
}



int IsDataCorrect(char _name[],int _lineNum)
{
	FILE* fp;
	char fname[MAX_LINE],lname[MAX_LINE],email[MAX_LINE];
	int i;       
	char*** data;
	data = CreateDataArray(_lineNum);
	if(data==NULL)
	{
		return -1;
	}

	for(i=0;i<_lineNum;i++)
	{
		GetListingData(data[i][0],data[i][1],data[i][2]);
	}

	fp = fopen(_name, "r");        	
	if(fp == NULL)  
	{                    
		return -1;
	} 
	for(i=0;i<_lineNum;i++)
	{
		fscanf(fp,"%s%s%s",fname,lname,email);
		if(strcmp(data[i][0],fname)!= 0)
		{
			return 0;
		}
		if(strcmp(data[i][1],lname)!= 0)
		{
			return 0;
		}
		if(strcmp(data[i][2],email)!= 0)
		{
			return 0;
		}
	}
	FreeALLData(data,_lineNum);
	fclose(fp);
	return 1;
}


ERRCODE PrintListings(char _name[])
{
	FILE* fp;
	char line[MAX_LINE];

	fp = fopen(_name, "r");        	
	if(fp == NULL)  
	{                    
		return ERR_FILE_OPEN;
	} 
	while(!feof(fp))
	{
		fgets(line,sizeof line,fp);
		if(!feof(fp))	
		{
			printf("%s",line);
		}
	}
	fclose(fp);
	return ERR_SUCCESS;
}

void PrintERRCODE(ERRCODE _err)
{
	switch(_err)
	{
		case ERR_SUCCESS: 	printf("ERR_SUCCESS\n"); 	break;
		case ERR_SEEK: 		printf("ERR_SEEK\n");  	break;
		case ERR_FILE_OPEN: 	printf("ERR_FILE_OPEN\n"); 	break;
	}
}

