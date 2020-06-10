#include<stdio.h>
#include<stdlib.h>
#include"game.h"
#include"log.h"
int main()
{
	Game* game;
	if(ERR_SUCCESS!=OpenLog("hearts.log"))
	{
		printf("fopen error\n");
		return -1;
	}
	game = GameCreate(4);
	printf("File:%s Line:%d Func:%s",__FILE__,__LINE__,__func__);
	CLOG(INFO,"game started");
	GameStart(game); 
	GameDestroy(game);
	CloseLog();
	return 0;
}
