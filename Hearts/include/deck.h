#ifndef _DECK_H_
#define _DECK_H_
#include"card.h"
#include"adt_error.h"

typedef struct Deck Deck;

/*
	description: create card deck instance
	output: a pointer to deck if succeeded ,NULL otherwise
*/
Deck* DeckCreate();

/*
	description: free deck instance
	input: _deck - a pointer to deck
*/
void DeckDestroy(Deck* _deck);

/*
	description: deal a card from the deck 
	input: _deck - a pointer to deck 
		_card - a pointer to a card
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE DealCard(Deck* _deck, Card* _card);

/*
	description: Shuffle cards in the deck 
	input: _deck - a pointer to deck 
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE ShuffleCards(Deck* _deck);

#endif /*_DECK_H_*/
