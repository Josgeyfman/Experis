#include<stdio.h> 	/*sprintf*/
#include<stdlib.h>	/*allocation*/
#include"game.h"
#define MAGIC_NUM 0xbebebebe
#define IS_VALID(t) (t && t->magicNum == MAGIC_NUM)

struct Game
{
	Player** players;
	int* scores;
	int playersNum;
	int magicNum;
};

/*------------------------static function signatures --------------------------*/

static void FreePlayers(Player** _players,int _size);
static int CurrentLeader(Game* _game);
static int CheckforWinner(Game* _game);
static void PrintScores(Game* _game);
static void PrintPlayer(int _player);
/*------------------------API functions --------------------------*/

Game* GameCreate(size_t _playerNum)
{
	int i;
	int* scores;
	Player** players;
	Game* game = NULL;
	game = (Game*)malloc(sizeof(Game));
	if(game)
	{
		players =(Player**)malloc(_playerNum*sizeof(Player*));
		if(!players)
		{
			free(game);
			return NULL;
		}
		for(i=0;i<_playerNum;i++)
		{
			players[i] = PlayerCreate(1);
			if(!players[i])
			{
				FreePlayers(players,i-1);
				free(players);	
				return NULL;
			}
		}
		scores = (int*)calloc(_playerNum,sizeof(int));
		if(!scores)
		{
			FreePlayers(players,_playerNum);
			free(players);	
			return NULL;
	
		}
		game->players = players;
		game->scores = scores;
		game->playersNum=_playerNum;
		game->magicNum = MAGIC_NUM;
	}
	return game;
}

void GameDestroy(Game* _game)
{
	if(IS_VALID(_game))
	{
		FreePlayers(_game->players,_game->playersNum);
		free(_game->scores);
		_game->magicNum=0;
		free(_game);	
	}
}


void GameStart(Game* _game)
{
	
	Round* round ;
	int winner = -1;
	char pName[10];
	Direction dir = LEFT;
	PrintString("Welcome to Game of Hearts!\n\n");
	PrintString("Plaese enter your name:\n\n");
	GetString(pName);
	PrintString("Game starting!\n\n");
	while(winner<0)
	{ 
		round = RoundCreate(pName);
		RoundStart(round,_game->players,dir,_game->scores);
		RoundDestroy(round);RoundDestroy(round);
		dir++;
		dir%= DIR_SIZE;
		PrintString("Game scores:\n\n");
		PrintString(pName);
		PrintString("\tGeorge\tPaul\tRingo\n\n");
		PrintScores(_game);
		PrintString("\n");
		winner = CheckforWinner(_game);
	}
	PrintString("Winner is player no ");
	PrintPlayer(winner);
}


/*------------------------static function  --------------------------*/

static void FreePlayers(Player** _players,int _size)
{
	int i;
	for(i=0;i<_size;i++)
	{
		if(_players[i])
		{
			PlayerDestroy(_players[i]);
		}
	}
}

static int CheckforWinner(Game* _game)
{
	int i;	
	for(i=0;i<_game->playersNum;i++)
	{
		if(_game->scores[i]>100)
		{
			return CurrentLeader(_game);
		}
	}
	return -1;
}

static int CurrentLeader(Game* _game)
{
	int i,leader,min=_game->scores[0];	
	for(i=0;i<_game->playersNum;i++)
	{
		if(min>_game->scores[i])
		{
			min =_game->scores[i];
			leader=i;
		}
	}
	return leader;
}

static void PrintScores(Game* _game)
{
	int i;
	char str[20];
	for(i=0;i<4;i++)
	{
		
		sprintf(str,"%d\t",_game->scores[i]);
		PrintString(str);
	}
	PrintString("\n");
}

static void PrintPlayer(int _player)
{
	switch(_player)
	{
		case 0:     PrintString("0\n"); break;
		case 1:     PrintString("1\n"); break;
		case 2:     PrintString("2\n"); break;
		case 3:     PrintString("3\n"); break;
	}
}

