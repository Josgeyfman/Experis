#ifndef _GAME_H_
#define _GAME_H_
#include"player.h"
#include"round.h"
#include"ui.h"

typedef struct Game Game;

/*
	description: create game instance
	input: _playerNum - num of players in game
	output: a pointer to game if succeeded ,NULL otherwise
*/
Game* GameCreate(size_t _playerNum);

/*
	description: free game instance
	input: _game - a pointer to game
*/
void GameDestroy(Game* _game);

/*
	description: start game instance
	input:  _game - a pointer to game
	output: a pointer to round if succeeded ,NULL otherwise
*/
void GameStart(Game* _game);




#endif /*_GAME_H_*/
