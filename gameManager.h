#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "board.h"
#include "players.h"

typedef struct _gameManager
{
	Board board;
	Player players[2];

	int turnTime;
	int playerTurn;
	
	int paused;
	int won;
	int round;
	int totalRounds;

} GameManager;

void StartGame(GameManager*);
void ResetGame(GameManager*);
void UpdateGame(GameManager*, sfClock*);
void MakeTurn(GameManager*);

#endif