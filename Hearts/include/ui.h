#ifndef _UI_H_
#define _UI_H_
#include"card.h"
#include"adt_error.h"

/*
	description: print a given card to console
	input: _card - card struct
*/
void PrintCard(Card _card);

/*
	description: get a  card from console
	input: _card - a pointer to card
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE GetCard(Card* _card);

/*
	description: print a given string to console
	input: _str - pointer to string
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE PrintString(char* _str);

/*
	description: get a string from console
	input: _str - pointer to string
	output: ERR_SUCCESS if succeeded ,ILLEGAL_INPUT otherwise
*/
ERRCODE GetString(char* _str);

#endif /*_UI_H_*/
