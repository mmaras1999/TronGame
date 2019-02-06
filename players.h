#ifndef PLAYERS_H
#define PLAYERS_H

#include <stdio.h>
#include <stdlib.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>

#include "board.h"

//Direction:
//0 - up
//1 - right
//2 - down
//3 - left

typedef struct _player
{
	int playerID;
	int isHuman;
	int score;

	sfVector2i position;
	int direction;
	int prevDirection;

	sfKeyCode KeyRight;
	sfKeyCode KeyLeft;
	int keyType;

	int AIlevel;

	int leftClicked;
	int rightClicked;
	int leftReleased;
	int rightReleased;
	
	sfColor color;
	int colorID;	

	void (*getInput)(Board*, int, struct _player*);
} Player;



void getHumanInput(Board*, int, Player*);
void getAIInputHard(Board*, int, Player*);
void getAIInputEasy(Board*, int, Player*);

#endif
