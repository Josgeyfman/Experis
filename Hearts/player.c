#include<stdlib.h>	/*allocation*/
#include<stdbool.h>	/*bool struct*/
#include"player.h"

#define MAGIC_NUM 0xbeeffeed
#define IS_VALID(t) (t && t->magicNum == MAGIC_NUM)

struct Player
{
	bool* cards;
	int cardsNum;
	int magicNum;
};

/*------------------------API functions --------------------------*/

Player* PlayerCreate(int _isreal)
{
	size_t size;
	bool* cards;
	Player* player;
	size = SUITE_SIZE*CARDS_SIZE;
	player = (Player*)malloc(sizeof(player));
	if(player)
	{
		cards = (bool*)calloc(size,sizeof(bool));
		if(!cards)
		{
			free(player);
			return NULL;	
		}
		player->cards = cards;
		player->cardsNum = 0;
		player->magicNum = MAGIC_NUM;
	}
	return player;
}


void PlayerDestroy(Player* _player)
{
	if(IS_VALID(_player))
	{
		free(_player->cards);
		_player->magicNum = 0;
		free(_player);
	}
}

ERRCODE PlayerGiveCard(Player* _player,size_t _suite ,size_t _cardval)
{
	size_t index;
	if(IS_VALID(_player))
	{
		index = (_suite*CARDS_SIZE) + _cardval;
		if(_player->cardsNum>0)
		{
			if(_player->cards[index])
			{
				_player->cards[index] = false;
				_player->cardsNum--;
				return ERR_SUCCESS;
			}
			return ERR_NOT_EXISTS;
		}
		return ERR_EMPTY;
	}
	return ERR_ILLEGAL_INPUT;
}


ERRCODE PlayerTakeCard(Player* _player,Card _card)
{
	int index;
	if(IS_VALID(_player))
	{
		index = (_card.suite*CARDS_SIZE) +_card.cardVal;
		if(!_player->cards[index])
		{
			_player->cards[index] = true;
			_player->cardsNum++;
			return ERR_SUCCESS;
		}
		return ERR_EXISTS;
	}
	return ERR_ILLEGAL_INPUT;
}

