#ifndef _PLAYER_H_
#define _PLAYER_H_
#include"card.h"
#include"adt_error.h"

typedef struct Player Player; 

/*
	description: create player instance
	output: a pointer to player if succeeded ,NULL otherwise
*/
Player* PlayerCreate();

/*
	description: free player instance
	input: __player - a pointer to player
*/
void PlayerDestroy(Player* _player);

/*
	description: retrieve a card from the player 
	input: _player - a pointer to player 
		_suite -  card suite
		_cardval - card value
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT ,EMPTY NOT_EXISTS otherwise
*/
ERRCODE PlayerGiveCard(Player* _player,size_t _suite ,size_t _cardval);

/*
	description: add a card to the player 
	input: _player - a pointer to player 
		_card -  card to add
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT,NOT_EXISTS otherwise
*/
ERRCODE PlayerTakeCard(Player* _player,Card _card);


#endif /*_PLAYER_H_*/
