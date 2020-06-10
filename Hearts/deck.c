#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"deck.h"
#define MAGIC_NUM 0xfeedbeef
#define IS_VALID(t) (t && t->magicNum == MAGIC_NUM)

/*------------------------structure---------------------------------------*/

struct Deck
{
	Card* cards;	
	int cardCount;
	int magicNum;
};

/*------------------------static function signatures----------------------*/

static void SwapCards(Card* _card1,Card* _card2);

/*------------------------API functions ----------------------------------*/

Deck* DeckCreate()
{
	size_t i,cardVal=0,suiteVal=0,size;
	Card* cards;
	Deck* deck = (Deck*)malloc(sizeof(Deck));
	size = SUITE_SIZE*CARDS_SIZE;
	if(!deck)
	{
		return NULL;	
	}

	cards = (Card*)malloc(size*sizeof(Card));

	if(!cards)
	{
		free(deck);
		return NULL;
	}
	
	deck->cards = cards;
	for(i=0;i<size;i++)
	{
		deck->cards[i].suite = suiteVal;
		deck->cards[i].cardVal = cardVal++;
		if(cardVal == CARDS_SIZE)
		{
			cardVal=0;
			suiteVal++;
		}
	}
	deck->cardCount = size;
	deck->magicNum = MAGIC_NUM;
	return deck;
}


ERRCODE DealCard(Deck* _deck, Card* _card)
{
	if(IS_VALID(_deck) && _deck->cardCount)
	{
		*_card = _deck->cards[_deck->cardCount-1];
		_deck->cardCount --;
		return ERR_SUCCESS;

	}
	return ERR_ILLEGAL_INPUT;
}

ERRCODE ShuffleCards(Deck* _deck)
{
	size_t i;
	int randVal;
	time_t t;
	srand((unsigned) time(&t));
	if(IS_VALID(_deck))
	{
		for(i=0;i<_deck->cardCount;i++)
		{
			randVal = rand()%_deck->cardCount;
			SwapCards(&_deck->cards[i],&_deck->cards[randVal]);
		}
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}

void DeckDestroy(Deck* _deck)
{
	if(IS_VALID(_deck))
	{
		free(_deck->cards);
		free(_deck);
		_deck->magicNum = 0;
	}
}	

/*------------------------static functions --------------------------*/

static void SwapCards(Card* _card1,Card* _card2)
{
	Card tmp;
	tmp = *_card1;
	*_card1 = *_card2;
	*_card2=tmp;
}

/*
int main()
{
	int i;
	Card card;
	Deck* deck = DeckCreate();
	if(!deck)
	{
		return -1;
	}
	for(i=0;i<deck->cardCount;i++)
	{
			printf("before shuffle %d of %d,\n"
			,deck->cards[i].cardVal,deck->cards[i].suite);	
	}
	
	ShuffleCards(deck);
	
	for(i=0;i<deck->cardCount;i++)
	{
			printf("after shuffle %d of %d,\n"
			,deck->cards[i].cardVal,deck->cards[i].suite);	
	}
	
	while(deck->cardCount)
	{
			DealCard(deck,&card);
			printf("dealed %d of %d deck size %d\n",card.cardVal,card.suite,deck->cardCount);	
	}
	for(i=0;i<deck->cardCount;i++)
	{
				printf("left after shuffle %d of %d,\n"
				,deck->cards[i].cardVal,deck->cards[i].suite);	
	}
	printf("\n");
	DeckDestroy(deck);
	return 0;
}


*/







