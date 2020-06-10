#include "files2.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define ALPHBET_LEN 26

typedef struct Word Word;
	
typedef struct Word
{
	char word[MAX_LINE];
	int count;
	Word* next;

} word;


static int CountWordInstances(char _fname[] ,char _word[])
{
	FILE* fp;
	char cword[MAX_LINE];
	int wordCount=0;
	if(!_fname || !_word)  
	{                    
		return -1;
	}       
	fp = fopen(_fname, "r");        	
	if(!fp)  
	{           
		return -1;
	}
	fscanf(fp,"%s",cword);
	while(!feof(fp))
	{
		if(0==strcmp(cword,_word))
		{
			wordCount++;
		}
		fscanf(fp,"%s",cword);
	}
	fclose(fp);
	return wordCount;
}

ERRCODE PrintWordInstances(char _fname[])
{
	
	FILE* fp;
	char cword[MAX_LINE],cfname[MAX_LINE];
	int wordCount=0;
	if(!_fname)  
	{                    
		return ERR_ILLEGAL_INPUT;
		
	}       
	fp = fopen(_fname, "r");        	
	if(!fp)  
	{                    
		return ERR_FILE_OPEN;
	}
	fscanf(fp,"%s%s",cfname, cword);
	while(!feof(fp))
	{
		wordCount = CountWordInstances(cfname,cword);
		printf("In file %s the word %s appeared %d times\n",cfname,cword,wordCount);
		fscanf(fp,"%s%s",cfname, cword);
	}
	return ERR_SUCCESS;
	fclose(fp);
}

void CountsLetters(FILE* _fp ,int _cletters[ALPHBET_LEN] ,int _letters[ALPHBET_LEN])
{
	char currChar;
	fseek(_fp,0,SEEK_SET);
	currChar = ftell(_fp);
	while(currChar != EOF)
	{
		currChar = fgetc(_fp);
		if(currChar>='A' && currChar<='Z') 
		{
			_cletters[currChar-'A']++;
		}
		else if(currChar>='a' && currChar<='z') 
		{
			_letters[currChar-'a']++;
		}
	}
}

void PrintLetters(int _cletters[ALPHBET_LEN] ,int _letters[ALPHBET_LEN])
{
	
	int i;
	for(i=0;i<ALPHBET_LEN;i++)
	{
		if(_letters[i]!=0)
		{	
			printf("%c\t%d\n",i+'a',_letters[i]);
		}
	}
	for(i=0;i<ALPHBET_LEN;i++)
	{
		if(_cletters[i]!=0)
		{	
			printf("%c\t%d\n",i+'A',_cletters[i]);
		}
	}
}

ERRCODE PrintLetterInstanceNum(char _fname[])
{
	
	FILE* fp;
	int letters[ALPHBET_LEN],cletters[ALPHBET_LEN];
	int i;
	if(!_fname)  
	{                    
		return ERR_ILLEGAL_INPUT;
	}       
	fp = fopen(_fname, "r");        	
	if(!fp)  
	{                    
		return ERR_FILE_OPEN;
	}
	for(i=0;i<ALPHBET_LEN;i++)
	{
		letters[i]=0;
		cletters[i]=0;
	}
	
	CountsLetters(fp,cletters,letters);
	PrintLetters(cletters,letters);

	fclose(fp);
	return ERR_SUCCESS;
}


static word* CreateWord(char _word[])
{
	word* wp = (word*)malloc(sizeof(word));
	if(!wp)
	{
		return NULL;
	}
	strcpy(wp->word,_word);
	wp->count=1;
	wp->next=NULL;
	return wp;
}

static word* GetWord(word* _words,char* _word)
{
	word* curr = _words;
	int res ;
	while(curr)
	{
		res = strcmp(curr->word,_word);
		if(res == 0)
		{
			return curr->next;
		}
		else if(res > 0)
		{
			return NULL;
		}
		curr = curr->next;
	}
	return NULL;
}


void FreeWords(word* _words)
{
	word* curr = _words;
	word* tmp;
	while(curr)
	{
		tmp = curr->next;
		free(curr);
		curr =tmp;
	}
}

void PrintWords(word* _words)
{

	word* curr = _words;
	while(curr)
	{
		printf("%s\t%d\n",curr->word,curr->count);
		curr = curr->next;
	}

}


static ERRCODE InsertWord(word* _words,word* _newWord)
{
	word* curr = _words;
	word* tmp=NULL;
	int res ;
	if(!curr)
	{
		curr = _newWord;
		return ERR_SUCCESS;
	}
	while(curr->next)	
	{
		res = strcmp(curr->next->word,_newWord->word);
		curr = curr->next;
		if(res>0)
		{
			break;
		}

	}
	
	if(curr)
	{
		_newWord->next = curr->next;
		curr->next = _newWord;
	}
	else
	{
		curr = tmp;
		tmp->next = NULL;
	}
	return ERR_SUCCESS;
}

ERRCODE CountWordInstancesinFile(char _fname[])
{
	word* words = NULL;
	FILE* fp;
	char cword[MAX_LINE];
	word* curr;
	ERRCODE res;
	if(!_fname)  
	{                    
		return ERR_ILLEGAL_INPUT;
	}       
	fp = fopen(_fname, "r");        	
	if(!fp)  
	{                    
		return ERR_FILE_OPEN;
	}
	fscanf(fp,"%s",cword);
	while(!feof(fp))
	{
		curr = GetWord(words,cword);
		if(curr)
		{
			curr->count++;
		}
		else
		{	
			curr = CreateWord(cword);
			res = InsertWord(words,curr);
			if(res!= ERR_SUCCESS)
			{
				FreeWords(words);
				fclose(fp);
			}
		}
		fscanf(fp,"%s",cword);
	}
	PrintWords(words);
	FreeWords(words);
	fclose(fp);
	return res;
	
}

int main()
{
	char fname[MAX_LINE];
	printf("Please enter file name\n");
	scanf("%s",fname);
	CountWordInstancesinFile(fname);
	return 0;
}



