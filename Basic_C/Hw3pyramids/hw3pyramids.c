
#include<stdio.h>
#define STAR '*'
#define SPACE ' '
#define RIGHT 1
#define UP 2
#define DOWN 3
#define LEFT 4
#define ALL 5
#define EXIT 6

void PrintLine(int _length,char _currentChar);

void printRightPyramid(int _baseLength);

void PrintUpPyramid(int _baseLength);

void PrintDownPyramid(int _baseLength);

void PrintLeftPyramid(int _baseLength);
 
int main(){
	int baseLength ,orientation;
	do{	
		printf("Please enter orientation:\n1 >\n2 ^\n3 v\n4 <\n5 all\n6 exit\n");
		scanf("%d", &orientation);
		printf("Please enter pyramid base length:");
		scanf("%d", &baseLength);
		if(baseLength<1){
			orientation=7;
		}
		switch(orientation){
			case RIGHT: printRightPyramid(baseLength);
				    break;

			case UP:    PrintUpPyramid(baseLength);
			 	    break;

			case DOWN:  PrintDownPyramid(baseLength);
				    break; 

			case LEFT: PrintLeftPyramid(baseLength);
				   break;

			case ALL:  PrintUpPyramid(baseLength);
				   PrintDownPyramid(baseLength);
				   PrintLeftPyramid(baseLength);
				   printRightPyramid(baseLength);
				   break;
			case EXIT: return 0;
			default: printf("bad input\n");
				 break; 
				 
		}
	}while(1);
	return 0;

}

void printRightPyramid(int _baseLength)
{
	int secondHalf = _baseLength/2, starNum;
	int firstHalf = (_baseLength%2!=0) ? secondHalf+1 : secondHalf ;
	for(starNum=0;starNum<firstHalf;starNum++)
	{
		PrintLine(starNum+1,STAR);
		printf("\n");
	}
	for(starNum=secondHalf;starNum>0;starNum--)
	{
		PrintLine(starNum,STAR);
		printf("\n");
	}
}

void PrintUpPyramid(int _baseLength)
{
	int firstHalf = (_baseLength%2!=0) ? _baseLength/2+1 : _baseLength/2 ;
	int row, spaceNum=firstHalf-1,starNum = (_baseLength%2!=0) ? 1 : 2 ;
	
        for(row=0;row<firstHalf;row++)
	{
                PrintLine(spaceNum,SPACE);
		PrintLine(starNum,STAR);
		starNum+=2;
		spaceNum--;
		printf("\n");
	}
}

void PrintDownPyramid(int _baseLength)
{
	int row, spaceNum=0,starNum=_baseLength;
	int firstHalf = (_baseLength%2!=0) ? _baseLength/2+1 : _baseLength/2 ;
        for(row=0;row<firstHalf;row++)
	{
                PrintLine(spaceNum,SPACE);
		PrintLine(starNum,STAR);
		starNum-=2;
		spaceNum++;
		printf("\n");
	}
}

void PrintLeftPyramid(int _baseLength)
{
	int secondHalf = _baseLength/2, row,spaceNum,starNum =1;
	int firstHalf = (_baseLength%2!=0) ? secondHalf+1 : secondHalf ;
	spaceNum=firstHalf-1;
	for(row=0;row<firstHalf;row++)
	{
		PrintLine(spaceNum,SPACE);
		PrintLine(starNum,STAR);
		starNum++;
		spaceNum--;
		printf("\n");
	}
	starNum--;
	spaceNum = (firstHalf==secondHalf) ? 0:1;
	starNum-= spaceNum;
	for(row=secondHalf;row>0;row--)
	{
		PrintLine(spaceNum,SPACE);
		PrintLine(starNum,STAR);
		starNum--;
		spaceNum++;
		printf("\n");
	}	
}

void PrintLine(int _length,char _currentChar)
{
	for(;0<_length;_length--)
	{
		printf("%c",_currentChar);
	}
}


