#ifndef _CARD_H_
#define _CARD_H_

typedef enum
{
	CLUBS,
	DIAMONDS,
	SPADES,
	HEARTS,
	SUITE_SIZE
} Suite;

typedef enum
{
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN,
	JACK,
	QUEEN,
	KING,
	ACE,
	CARDS_SIZE
} CardVal;

typedef struct Card
{
	Suite suite;
	CardVal cardVal;
}Card;

#endif /*_CARD_H_*/





