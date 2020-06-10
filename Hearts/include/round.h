#ifndef _ROUND_H_
#define _ROUND_H_
#include"player.h"
#include"ui.h"
#include"deck.h"
#include"adt_error.h"

typedef enum{LEFT,RIGHT,FRONT,NOPASS,DIR_SIZE} Direction;

typedef struct Round Round;

/*
	description: create round instance
	input: _playerName - a pointer to real player name
	output: a pointer to round if succeeded ,NULL otherwise
*/
Round* RoundCreate(char* _playerName);

/*
	description: free round instance
	input: _round - a pointer to round
*/
void RoundDestroy(Round* _round);

/*
	description: start round in herats game
	input: _round - a pointer to round
	      _players - pointer to players
		_dir- direction of round swap
		_scores -pointer to scores
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE RoundStart(Round* _round ,Player** _players,Direction _dir,int* _scores);


#endif /*_ROUND_H_*/
