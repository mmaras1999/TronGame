#include "players.h"
#include "defines.h"
#include "AI.h"

void getHumanInput(Board* board, int p, Player* players)
{
	int dir = players[p].prevDirection;

	if(players[p].leftClicked) //Turn Left
	{
		players[p].leftClicked = 0;
		players[p].direction = (dir + 3) % 4; 
	}

	if(players[p].rightClicked) //Turn Right
	{
		players[p].rightClicked = 0;
		players[p].direction = (dir + 1) % 4;
	}
}

void getAIInputHard(Board* board, int p, Player* players)
{
	minimax(p, 0, p, players, board, &players[p].direction);
}
