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

void getAIInputEasy(Board* board, int p, Player* players)
{
	int moves[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	LL best = LLINF;
	int nextMove = 0;

	FOR(i, 0, 4)
	{
		int nextX = players[p].position.x + moves[i][0];
		int nextY = players[p].position.y + moves[i][1];
	
		if (nextX >= 0 && nextX < BOARD_WIDTH && nextY >= 0 && nextY < BOARD_HEIGHT && !(board->blocked[nextX][nextY]))
		{
			LL d = abs(players[(p + 1) & 1].position.x - nextX) + abs(players[(p + 1) & 1].position.y - nextY);

			if(d < best)
			{
				best = d;
				nextMove = i;
			}
		}
	}

	players[p].direction = nextMove;
}
