#include<stdlib.h>	/*allocation*/
#include<stdio.h> 	/*sprintf*/
#include<stdbool.h>	/*bool struct*/
#include"round.h"
#define MAGIC_NUM 0xfefefebe
#define  IS_VALID(t) (t && t->magicNum == MAGIC_NUM)
#define ALLDECK 51 
#define NOHEARTS 38

struct Round
{
	bool HeartBroken;
	int trick;
	Card table[4];
	int scores[4];
	int magicNum;
	char* playerName;
};


/*------------------------static function signatures --------------------------*/

static ERRCODE InitRound(Round* _round,Player** _players,Direction _dir);  
static ERRCODE DealCardsToPlayers(Player** _players,Deck* deck);
static ERRCODE SwapThreeCards(Player** _players,Direction _dir ,Card _swapCards[][3]);
static void ChooseSwapCards(Player** _players,Card _swapCards[][3]);
static void AutoChooseCards(Player* _player ,Card _cards[3]);
static void PrintPlayerCards(Player* _player);
static int GetStartingPlayer(Player** _players);
static void PrintTrickTable(Round* _round);
static int PlayRound(Player** _players,Round* _round,int _startIndex);
static ERRCODE chooseTrickCards(Player** _players ,Round* round,int _start);
static int calcTrickPoints(Round*_round ,int _start);
static void UpdateScores(Round* _round,int* _scores);
static Card FindNextHighCard(Player* _player,int _heartBroken);
static ERRCODE GetNextLowSuite(Player* _player,Suite _sut,Card* _lowest);
static ERRCODE GetNextHighSuite(Player* _player,Suite _sut,Card* _highest);
static void PrintRealTurnTable(Round* _round ,int _before);
static void PrintLeadingSuite(Suite _suite);
static void PrintDirection(Direction _dir);
static void PrintScores(Round* _round);
/*static void PrintAllPlayerCards(Player** _players);*/

/*------------------------API functions --------------------------*/

Round* RoundCreate(char* _playerName)
{
	int i;
	Round* round;
	if(!_playerName)
	{
		return NULL;
	}
	round = (Round*)malloc(sizeof(Round));
	if(round)
	{
		round->HeartBroken = 0;
		round->trick = 0;
		round->playerName=_playerName;
		for(i=0;i<4;i++)
		{
			round->scores[i] = 0;
		}
		round->magicNum = MAGIC_NUM;
	}
	return round;
}

void RoundDestroy(Round* _round)
{
	if(IS_VALID(_round))
	{
		_round->magicNum = 0;
		free(_round);
	}
}

ERRCODE RoundStart(Round* _round ,Player** _players,Direction _dir,int* _scores)
{
	int startPlayer;
	if(IS_VALID(_round))
	{
		InitRound(_round,_players,_dir);
		startPlayer = GetStartingPlayer(_players);
		PlayRound(_players,_round,startPlayer);
		UpdateScores(_round,_scores);
		PrintString("Round scores:\n\n");
		PrintString(_round->playerName);
		PrintString("\tGeorge\tPaul\tRingo\n\n");
		PrintScores(_round);
		PrintString("\n");
		return ERR_SUCCESS;
	}
	return ERR_ILLEGAL_INPUT;
}


/*------------------------static functions --------------------------*/

/* for DEBUG
static void PrintAllPlayerCards(Player** _players)
{
	int i;
	for(i=0;i<4;i++)
	{
		PrintPlayerCards(_players[i]);
	}
}
*/

static void PrintScores(Round* _round)
{
	int i;
	char str[20];
	for(i=0;i<4;i++)
	{
		
		sprintf(str,"%d\t",_round->scores[i]);
		PrintString(str);
	}
	PrintString("\n");
}

static void UpdateScores(Round* _round,int* _scores)
{
	int i;
	for(i=0;i<4;i++)
	{
		_scores[i]+=_round->scores[i];
	}

}

static ERRCODE InitRound(Round* _round,Player** _players,Direction _dir)
{
	ERRCODE res;
	Deck* deck = DeckCreate();
	Card swapCards[4][3];
	if(!deck)
	{
		return ERR_MEM_ALLOC;
	}
	res = ShuffleCards(deck);
	if(res == ERR_SUCCESS)
	{
		DealCardsToPlayers(_players,deck);
	}
	PrintString("cards dealed to players\n\n");
	
	if(_dir!=NOPASS)
	{
		PrintString("Please Choose 3 cards to pass ");
		PrintDirection(_dir);
		PrintString("\n");
		ChooseSwapCards(_players,swapCards);
		SwapThreeCards(_players,_dir,swapCards);
	}
	DeckDestroy(deck);
	return ERR_SUCCESS;
}

static ERRCODE DealCardsToPlayers(Player** _players,Deck* deck)
{
	int i;	
	Card card;
	for(i=0;i<CARDS_SIZE;i++)
	{
		DealCard(deck,&card);
		PlayerTakeCard(_players[0],card);
		DealCard(deck,&card);
		PlayerTakeCard(_players[1],card);
		DealCard(deck,&card);
		PlayerTakeCard(_players[2],card);
		DealCard(deck,&card);
		PlayerTakeCard(_players[3],card);
	}
	return ERR_SUCCESS;
}


static ERRCODE SwapThreeCards(Player** _players,Direction _dir ,Card _swapCards[][3])
{
	int i;
	
	for(i=0;i<3;i++)
	{
		switch(_dir)
		{
			case LEFT:	PlayerTakeCard(_players[1],_swapCards[0][i]);
					PlayerTakeCard(_players[2],_swapCards[1][i]);
					PlayerTakeCard(_players[3],_swapCards[2][i]);
					PlayerTakeCard(_players[0],_swapCards[3][i]);
					break;
	
			case RIGHT:	PlayerTakeCard(_players[3],_swapCards[0][i]);
					PlayerTakeCard(_players[2],_swapCards[3][i]);
					PlayerTakeCard(_players[1],_swapCards[2][i]);
					PlayerTakeCard(_players[0],_swapCards[1][i]);
					break;

			case FRONT:	PlayerTakeCard(_players[2],_swapCards[0][i]);
					PlayerTakeCard(_players[0],_swapCards[2][i]);
					PlayerTakeCard(_players[1],_swapCards[3][i]);
					PlayerTakeCard(_players[3],_swapCards[1][i]);
					break;
	
			case NOPASS: 	return ERR_SUCCESS;
			case DIR_SIZE: 	return ERR_SUCCESS;
		}
		
	}
	return ERR_SUCCESS;

}

static void ChooseSwapCards(Player** _players,Card _swapCards[][3])
{
	
	int i=0;
	ERRCODE res;
	Card card;
	while(i<3)
	{
		PrintPlayerCards(_players[0]);
		res = GetCard(&card);  /*get card from real user*/
		if(!res)
		{
			PrintString("card chosen\n");
			PrintCard(card);
			PrintString("\n\n");
			res = PlayerGiveCard(_players[0],card.suite,card.cardVal);
			if(!res)
			{
				_swapCards[0][i++] = card;
			}
			else
			{
				PrintString("no such card in your deck\n\n");
			}
		}
		
	}
	
	for(i=1;i<4;i++)
	{
		AutoChooseCards(_players[i],_swapCards[i]);
	}
}

static void AutoChooseCards(Player* _player ,Card _cards[3])
{
	int i=0;
	while(i<3)
	{
		_cards[i++] = FindNextHighCard(_player,1);		
	}
}

static Card FindNextHighCard(Player* _player,int _heartBroken)
{
	int len,firstFlag=1;
	ERRCODE res;
	Card highCard,card,lastCard;
	len = (_heartBroken) ? ALLDECK : NOHEARTS;
	highCard.suite = CLUBS;
	highCard.cardVal = TWO;
	while(len>=0)
	{
		card.suite = len/CARDS_SIZE; 
		card.cardVal = len%CARDS_SIZE;
		res = PlayerGiveCard(_player,card.suite ,card.cardVal);
		if(!res && card.cardVal > highCard.cardVal)
		{
			if(firstFlag) /*first time don't take a card*/
			{
				firstFlag = 0;
			}
			else
			{
				PlayerTakeCard(_player,highCard);
			}
			highCard = card;
			
		}
		else if(!res)
		{
			PlayerTakeCard(_player,card);
			lastCard = card;  /*save last card that was checked*/
		}
		len--;
	}
	if(!_heartBroken && firstFlag) /*if no card was chosen break hearts*/
	{
		card = FindNextHighCard(_player,1);
		return card;
	}
	if(highCard.suite == CLUBS && highCard.cardVal == TWO) /*last card was reached*/
	{
		PlayerGiveCard(_player,lastCard.suite ,lastCard.cardVal);
		return lastCard;
	}
	return highCard;
}

static void PrintPlayerCards(Player* _player)
{
	int i=0;
	int sut,cval;
	Card card;
	ERRCODE res = ERR_NOT_EXISTS;
	while(i<52)
	{
		sut = i/CARDS_SIZE; 
		cval = i%CARDS_SIZE;
		res = PlayerGiveCard(_player,sut,cval);
		if(!res)
		{
			card.suite = sut;
			card.cardVal = cval;
			PrintCard(card);
			PlayerTakeCard(_player,card);
			PrintString("  ");
		}
		i++;
	}
	PrintString("\n");

}

static int GetStartingPlayer(Player** _players)
{
	int i;
	Card card = {CLUBS,TWO};
	ERRCODE res;
	for(i=0;i<4;i++)
	{
		res = PlayerGiveCard(_players[i],CLUBS,TWO);
		if(!res)
		{
			PlayerTakeCard(_players[i],card);
			return i;
		}
	}
	return -1;
}

static int PlayRound(Player** _players,Round* _round,int _startIndex)
{
	int i = _startIndex;
	while(_round->trick<13)
	{
		chooseTrickCards(_players,_round,i);
		PrintTrickTable(_round);
		i = calcTrickPoints(_round,i);
		_round->trick++;
	}
	
	return i;
}


static ERRCODE chooseTrickCards(Player** _players ,Round* _round,int _start)
{
	int i;
	ERRCODE res = ERR_BREAK;
	Card card = {CLUBS,TWO},card2 = {SPADES,THREE} ;
	Suite leadingSuite = CLUBS ,suiteCheck = CLUBS;
	for(i=_start;i< 4 + _start;i++)
	{
		if( i%4!=0 && i ==_start) /*  if auto player starts */
		{
			res  = PlayerGiveCard(_players[_start],CLUBS,TWO);
			if(!res) /*if  player starts first trick */
			{
				_round->table[_start]=card;
				leadingSuite = card.suite;
			}
			else
			{	/* find next high val last priority heart suite*/
				card = FindNextHighCard(_players[_start],0); 
				leadingSuite = card.suite;
				if(leadingSuite==HEARTS) /* if hearts suite returned , hearts broke ,get lowest heart*/
				{			
					if(!_round->HeartBroken)
					{
						_round->HeartBroken=1;
						PrintString("Hearts Broke\n\n");
					}
					PlayerTakeCard(_players[_start],card);
					res = GetNextLowSuite(_players[_start],leadingSuite,&card);
				}
				_round->table[_start]=card;
			}
		}
		else if(i%4!=0) /*auto player regular turn*/
		{
			if(leadingSuite==HEARTS) /*if leading suite is hearts find lowest card in suite*/
			{
				
				res = GetNextLowSuite(_players[i%4],leadingSuite,&card);
			}
			else /*else find biggest card in leading suite*/
			{
				res = GetNextHighSuite(_players[i%4],leadingSuite,&card);
				
			}
			if(res)	/*if no cards from leading suite exist find biggest from other suite */
			{						
				card = FindNextHighCard(_players[i%4],0);
				suiteCheck = card.suite;
				if(suiteCheck== HEARTS && !_round->HeartBroken) /*if chosen card suit is heart break hearts*/
				{
					_round->HeartBroken=1;
					PrintString("Hearts Broke\n\n");
				}
			}
			_round->table[i%4]=card;
			
		}
		

		if(i%4==0 && i == _start )/* if real player starts*/
		{
			res  = PlayerGiveCard(_players[_start],CLUBS,TWO);
			if(!res) /*if  player starts first trick */
			{
				do
				{
					PlayerTakeCard(_players[_start],card);
					PrintRealTurnTable(_round,i-_start);
					PrintPlayerCards(_players[i%4]);
					PrintString("You start the round, please Choose 2 Clubs to start\n\n");
					res = GetCard(&card2);
					if(!res)
					{
						res = PlayerGiveCard(_players[i%4],CLUBS,TWO);
					}
				}while(res);
			}
			else	
			{
				do
				{
					PrintRealTurnTable(_round,i-_start);
					PrintPlayerCards(_players[i%4]);
					PrintString("Please Choose a card from your hand\n\n");
					res = GetCard(&card);
					if(!res)
					{
						res = PlayerGiveCard(_players[i%4],card.suite,card.cardVal);
						if(res)
						{
							PrintCard(card);
							PrintString("Is not in your hand\n\n");
						}
						if(!res && !_round->HeartBroken && card.suite==HEARTS)
						{
							card2 = FindNextHighCard(_players[i%4],0);
							if(card2.suite!=HEARTS)
							{
								PlayerTakeCard(_players[_start],card2);
								PlayerTakeCard(_players[_start],card);
								PrintString("Hearts are not broken yet,pick from other suite\n\n");
								res = ERR_BREAK;
							}
							else
							{
								_round->HeartBroken=1;
								PrintString("Hearts Broke\n\n");
							}
						}
					}
					else
					{
						PrintString("Bad input please try again\n\n");
					}
					
				}while(res);
			}
			_round->table[_start]=card;
			leadingSuite = card.suite;
		}
		else if(i%4==0)
		{
			/*handle real  player regular turn if h broken and if not*/
			do
			{
				PrintString("Please Choose a card from your hand\n\n");
				PrintString("Leading suite is ");
				PrintLeadingSuite(leadingSuite);
				PrintRealTurnTable(_round,i-_start);
				PrintPlayerCards(_players[i%4]);
				res = GetCard(&card);
				if(!res)
				{
					res = PlayerGiveCard(_players[i%4],card.suite,card.cardVal);
					if(res)
					{
						PrintCard(card);
						PrintString("Is not in your hand\n\n");
					}
					else if(!res && card.suite!=leadingSuite)
					{
						res = GetNextLowSuite(_players[i%4],leadingSuite,&card2);
						if(!res)
						{
							PlayerTakeCard(_players[i%4],card2);
							PlayerTakeCard(_players[i%4],card);
							PrintString("Please choose card from leading suite,try again\n\n");
							res = ERR_BREAK;
						}
						else if(res)
						{
							if(card.suite==HEARTS && !_round->HeartBroken)
							{
								_round->HeartBroken = 1;
								PrintString("Hearts Broke\n\n");
							}
							res = ERR_SUCCESS;
						}
						
					}
				}
				else
				{
					PrintString("Bad input please try again\n\n");
				}
				
			}while(res);
			_round->table[i%4]=card;
		}
		
	}
	return  ERR_SUCCESS;
}

static ERRCODE GetNextLowSuite(Player* _player,Suite _sut,Card* _lowest)
{
	int lowest = _sut*CARDS_SIZE  ,highest = (1+_sut)*CARDS_SIZE-1;
	int firstFlag = 1,last=0;
	ERRCODE res = ERR_BREAK;
	Card lowCard,card,lastCard;
	card.suite = _sut;
	lowCard.cardVal = highest%CARDS_SIZE;
	lastCard.cardVal = highest%CARDS_SIZE;
	lastCard.suite = _sut;
	lowCard.suite = _sut;
	while(lowest<=highest)
	{
		card.cardVal = highest%CARDS_SIZE;
		res = PlayerGiveCard(_player,_sut,card.cardVal);
		if(!res && card.cardVal < lowCard.cardVal)
		{
			if(firstFlag) /*first time don't take a card*/
			{
				firstFlag = 0;
			}
			else
			{
				PlayerTakeCard(_player,lowCard);
			}
			lowCard = card;
			
		}
		else if(!res)
		{
			PlayerTakeCard(_player,card);
			lastCard=card; 
			last=1;
		}
		highest--;
	}
	if(firstFlag && !last)
	{
		return ERR_BREAK;
	}
	if(lowCard.cardVal<lastCard.cardVal)
	{
		*_lowest = lowCard;
	}
	else
	{
		PlayerGiveCard(_player,_sut,lastCard.cardVal);
		*_lowest =lastCard;
	}
	return ERR_SUCCESS;

}

static ERRCODE GetNextHighSuite(Player* _player,Suite _sut,Card* _highest)
{
	int lowest = _sut*CARDS_SIZE  ,highest = (1+_sut)*CARDS_SIZE-1;
	int firstFlag = 1,last=0;
	ERRCODE res = ERR_BREAK;
	Card highCard,card,lastCard;
	card.suite = _sut;
	highCard.cardVal = lowest%CARDS_SIZE;
	lastCard.cardVal = lowest%CARDS_SIZE;
	highCard.suite = _sut;
	lastCard.suite = _sut;
	while(lowest<=highest)
	{
		card.cardVal = lowest%CARDS_SIZE;
		res = PlayerGiveCard(_player,_sut,card.cardVal);
		if(!res && card.cardVal > highCard.cardVal)
		{
			if(firstFlag) /*first time don't take a card*/
			{
				firstFlag = 0;
			}
			else
			{
				PlayerTakeCard(_player,highCard);
			}
			highCard = card;
			
		}
		else if(!res)
		{
			PlayerTakeCard(_player,card);
			lastCard=card; 
			last = 1;
		}
		lowest++;
	}
	if(firstFlag && !last)
	{
		return ERR_BREAK;
	}
	if(highCard.cardVal>lastCard.cardVal)
	{
		*_highest =  highCard;
	}
	else
	{
		PlayerGiveCard(_player,_sut,lastCard.cardVal);
	  	*_highest = lastCard;
	}
	return ERR_SUCCESS;

}

static int calcTrickPoints(Round*_round ,int _start)
{
	int i,points=0,loser = _start;
	Suite sut = _round->table[_start].suite;
	for(i=_start+1;i<4+_start;i++)
	{
		if(_round->table[i%4].suite==sut && _round->table[i%4].cardVal > _round->table[loser].cardVal)
		{
			loser = i%4;
		}
	}
	for(i=0;i<4;i++)
	{
		if(_round->table[i].suite==HEARTS)
		{
			points++;
		}
		if(_round->table[i].suite==SPADES && _round->table[i].cardVal==QUEEN)
		{
			points+=13;
		}
	}
	_round->scores[loser]+=points;
	return loser;
}

static void PrintTrickTable(Round* _round)
{
	PrintString("\t\tPaul\n\t\t ");
	PrintCard(_round->table[2]);
	PrintString("\n");
	PrintString("George ");
	PrintCard(_round->table[1]);
	PrintString("\t\t\t");
	PrintCard(_round->table[3]);
	PrintString(" Ringo");
	PrintString("\n\t\t ");
	PrintCard(_round->table[0]);
	PrintString("\n\t\t");
	PrintString(_round->playerName);
	PrintString(" \n\n");
}

static void PrintRealTurnTable(Round* _round ,int _before)
{
	PrintString("\t\tPaul\n\t\t ");
	if(_before>=2)
	{
		PrintCard(_round->table[2]);
	}
	PrintString("\n");
	PrintString("George ");
	if(_before==3)
	{
		PrintCard(_round->table[1]);
	}
	PrintString("\t\t\t");
	if(_before>=1)
	{
		PrintCard(_round->table[3]);
	}
	PrintString(" Ringo");
	PrintString("\n\t\t ");
	PrintString("\n\t\t");
	PrintString(_round->playerName);
	PrintString(" \n\n");
}

static void PrintLeadingSuite(Suite _suite)
{	
	switch(_suite)
	{
		case CLUBS:       PrintString("\xE2\x99\xA3\n");    break;
		case DIAMONDS:    PrintString("\xE2\x99\xA6\n"); break;
		case SPADES:      PrintString("\xE2\x99\xA0\n");   break;
		case HEARTS:      PrintString("\xE2\x99\xA5\n");   break;
		case SUITE_SIZE: 	       break;
	}
}

static void PrintDirection(Direction _dir)
{	
	switch(_dir)
	{
		case LEFT:       PrintString("Left\n");    break;
		case RIGHT:    	 PrintString("Right\n"); break;
		case FRONT:      PrintString("Front\n");   break;
		case NOPASS:    	   break;
		case DIR_SIZE: 	     		  break;
	}
}

