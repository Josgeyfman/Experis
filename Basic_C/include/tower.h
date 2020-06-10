#ifndef _TOWER_H_
#define _TOWER_H_
#include"stack.h"
/**
	initialize stacks, start game
**/
void InitGame(int _n);

/*

	move disk from _from tower to _to tower

*/
void Move(stackp _from ,stackp _to);


/*

	recursively move tower

*/
void TowerPlay(int _n ,stackp _from ,stackp _to ,stackp _via);

#endif /*_TOWER_H_*/
