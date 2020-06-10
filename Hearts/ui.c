#include<stdio.h>	/*std I\O*/
#include<string.h>	/*strcmp*/
#include<stdlib.h>	/*atoi*/
#include"ui.h"

/*------------------------static function signatures --------------------------*/

static int CheckLetter(char* str);
static int CheckSuite(char* str);
static void PrintSuite(Suite _suite);
static void PrintCardVal(CardVal _cardval);

/*------------------------API functions --------------------------*/

void PrintCard(Card _card)
{
	PrintCardVal(_card.cardVal);
	printf("_");
	PrintSuite(_card.suite);
	printf(" ");
}

ERRCODE GetCard(Card* _card)
{
	char val[2],sut[1];
	int numVal;
	if(_card)
	{	
		printf("Please choose card Value 2-10,J,Q,K,A\n");
		scanf("%s",val);
		numVal = atoi(val);
		if(numVal>= 2  && numVal<=10)
		{
			_card->cardVal=numVal-2; 
		}
		else
		{
			numVal = CheckLetter(val);
			if(numVal>0)
			{
				_card->cardVal=numVal; 
			}
			else
			{
				return ERR_ILLEGAL_INPUT;
			}
		}
		printf("Please choose card Suite H-♥️ S-♠️  D-♦️  C-♣️ \n");
		scanf("%s",sut);
		numVal =  CheckSuite(sut);
		if(numVal>=0)
		{
			_card->suite=numVal;
			return ERR_SUCCESS;
		}
		
	}
	return ERR_ILLEGAL_INPUT;
}


ERRCODE PrintString(char* _str)
{
	if(_str)
	{
		printf("%s",_str);
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}

ERRCODE GetString(char* _str)
{
	if(_str)
	{
		scanf("%s",_str);
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}

/*------------------------static functions --------------------------*/

static int CheckLetter(char* _str)
{
	if(!strcmp(_str,"j") || !strcmp(_str,"J"))
	{
		return JACK;
	}
	if(!strcmp(_str,"q") || !strcmp(_str,"Q"))
	{
		return QUEEN;
	}
	if(!strcmp(_str,"k") || !strcmp(_str,"K"))
	{
		return KING;
	}
	if(!strcmp(_str,"a") || !strcmp(_str,"a"))
	{
		return ACE;
	}
	return -1;
}

static int CheckSuite(char* _str)
{
	if(!strcmp(_str,"h") || !strcmp(_str,"H"))
	{
		return HEARTS;
	}
	if(!strcmp(_str,"d") || !strcmp(_str,"D"))
	{
		return DIAMONDS;
	}
	if(!strcmp(_str,"s") || !strcmp(_str,"S"))
	{
		return SPADES;
	}
	if(!strcmp(_str,"c") || !strcmp(_str,"C"))
	{
		return CLUBS;
	}
	return -1;
}

static void PrintSuite(Suite _suite)
{
	switch(_suite)
	{
		case CLUBS:      printf("♣️"); break;
		case DIAMONDS:   printf("♦️"); break;
		case SPADES:     printf("♠️"); break;
		case HEARTS:     printf("♥️"); break;
		case SUITE_SIZE: 	       break;
	}
}

static void PrintCardVal(CardVal _cardval)
{
	switch(_cardval)
	{
		case TWO:   printf("2"); break;
		case THREE: printf("3"); break;
		case FOUR:  printf("4"); break;
		case FIVE:  printf("5"); break;
		case SIX:   printf("6"); break;
		case SEVEN: printf("7"); break;
		case EIGHT: printf("8"); break;
		case NINE:  printf("9"); break;
		case TEN:   printf("10");break;
		case JACK:  printf("J"); break;
		case QUEEN: printf("Q"); break;
		case KING:  printf("K"); break;
		case ACE:   printf("A"); break;
		case CARDS_SIZE: 	 break;
	}
}

