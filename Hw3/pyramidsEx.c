
#include<stdio.h>

void printPyramid(int baseLength,int orientation){
	char currentChar='*';
	int secondHalf = baseLength/2, row,col, startPosition;
	int firstHalf = (baseLength%2!=0) ? secondHalf+1 : secondHalf ;
	if(baseLength<1){
		orientation=6;
	}	
	switch(orientation){
		case 1: for(row=0;row<firstHalf;row++){
				for(col=0;col<=row;col++){
					printf("%c",currentChar);
				}
				printf("\n");
			}
			for(row=secondHalf;row>0;row--){
				for(col=row;col>0;col--){
					printf("%c",currentChar);
				}
				printf("\n");
			}
			break;

		case 2: currentChar=' ';
			startPosition=firstHalf;
			for(row=0;row<firstHalf;row++){
				for(col=1;col<=baseLength;col++){
					if(col==startPosition){
						currentChar='*';
						startPosition--;
					}
					printf("%c",currentChar);
					if(baseLength-startPosition==col){
						currentChar=' ';
					}
				}
				printf("\n");
			}
		 	break;

		case 3: secondHalf=0; 
				for(row=0;row<firstHalf;row++){
					for(col=0;col<=baseLength;col++){
						if(col==secondHalf){
							currentChar='*';
						}
						if(baseLength-secondHalf==col){
							currentChar=' ';
						}
						printf("%c",currentChar);
					}
					secondHalf++;
					printf("\n");
				}
			    break; 
		case 4: currentChar=' ';
			startPosition=1;
			for(row=0;row<firstHalf;row++){
				for(col=0;col<firstHalf;col++){
					if(col==firstHalf-startPosition){
						currentChar='*';
					}
					printf("%c",currentChar);
				}
				printf("\n");
				currentChar=' ';
				startPosition++;
			}
			startPosition=(secondHalf<firstHalf)? secondHalf-1: secondHalf ;
			for(row=secondHalf;row>0;row--){
				for(col=0;col<firstHalf;col++){
					if(col==secondHalf-startPosition){
						currentChar='*';
					}
					printf("%c",currentChar);
				}
				printf("\n");
				currentChar = ' ';
				startPosition--;
			}
			break;
		case 5: printPyramid(baseLength,2);
			printPyramid(baseLength,3);
			printPyramid(baseLength,4);
			printPyramid(baseLength,1);
			break;
		default: printf("bad input\n");
	}
}


int main(){

	int baseLen ,orientation;
	printf("Please enter pyramid base length:");
	scanf("%d", &baseLen);
	printf("Please enter orientation: 1 > , 2 ^ , 3 v , 4 < , 5 all: ");
	scanf("%d", &orientation);
	printPyramid(baseLen,orientation);
	return 0;

}



