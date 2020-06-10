#include<stdio.h> /*I\O*/
#include<stdlib.h> /*allocation*/
#include"myStruct.h"
#define MY_ALLOC 17
#define MAGIC_NUM_S 0xffddccaa
#define NOT_MAGIC_NUM 0xffaabbcc
#define IS_VALID_S(t) (t && t->magicNum==MAGIC_NUM_S)

struct MyStruct{
	
	size_t magicNum;
	int myInt;
	char myChar;
	float myFloat;
};

static int id=0;

mystruct* CreateMyStruct()
{
	mystruct* mys = (mystruct*)malloc(sizeof(mystruct));
	if(!mys)
	{
		return NULL;
	}
	mys->myInt=id++;
	mys->myChar=('0'+id)%256;
	mys->myFloat=id+.256;
	mys->magicNum=MAGIC_NUM_S;
	return mys;
}

void FreeMyStruct(void* _mys)
{
	mystruct* mys = (mystruct*)_mys;
	if(!IS_VALID_S(mys))
	{
		return;
	}
	mys->magicNum=NOT_MAGIC_NUM;
	id--;
	free(mys);
}

void PrintMyStruct(const void* _mys,void* _context)
{
	mystruct* mys = (mystruct*)_mys;
	if(IS_VALID_S(mys))
	{
		printf("mys[i:%d][c:%c][f:%.0f]",mys->myInt,mys->myChar,mys->myFloat);
	}
}

