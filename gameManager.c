#include "gameManager.h"
#include "defines.h"

void StartGame(GameManager* manager)
{
	manager->paused = 0;
	manager->totalRounds = 2;

	manager->players[0].isHuman = 1;
	manager->players[0].KeyRight = sfKeyRight;
	manager->players[0].KeyLeft = sfKeyLeft;
	manager->players[0].getInput = &getHumanInput;
	manager->players[0].playerID = 0;

	manager->players[1].isHuman = 0;
	manager->players[1].KeyRight = sfKeyD;
	manager->players[1].KeyLeft = sfKeyA;
	manager->players[1].getInput = &getAIInputHard;
	manager->players[1].playerID = 1;

	ResetGame(manager);
}

void ResetGame(GameManager* manager)
{
	manager->won = 0;
	manager->playerTurn = 1;
	manager->paused = 0;
	manager->turnTime = TURN_TIME;

	FOR(i, 0, BOARD_WIDTH)
	{
		FOR(j, 0, BOARD_HEIGHT)
		{
			manager->board.blocked[i][j] = 0;
		}
	}

	srand(time(0));

	sfVector2i position;
	position.x = rand() % (BOARD_WIDTH / 3);
	position.y = rand() % (BOARD_HEIGHT);
	int dir = 1;

	sfVector2i position2;
	position2.x = BOARD_WIDTH - 1 - position.x;
	position2.y = BOARD_HEIGHT - 1 - position.y;
	int dir2 = 3;

	int swap = rand() % 2;

	if(swap)
	{
		int temp = position.x;
		position.x = position2.x;
		position2.x = temp;

		temp = position.y;
		position.y = position2.y;
		position2.y = temp;

		temp = dir;
		dir = dir2;
		dir2 = temp;
	}

	manager->players[0].position = position;
	manager->players[0].direction = dir;
	manager->players[0].prevDirection = dir;
	manager->players[0].rightClicked = 0;
	manager->players[0].leftClicked = 0;

	manager->players[1].position = position2;
	manager->players[1].direction = dir2;
	manager->players[1].prevDirection = dir2;
	manager->players[1].rightClicked = 0;
	manager->players[1].leftClicked = 0;

	manager->board.blocked[manager->players[0].position.x][manager->players[0].position.y] = 1;
	manager->board.blocked[manager->players[1].position.x][manager->players[1].position.y] = 2;
}

void UpdateGame(GameManager* manager, sfClock * clock)
{
	int deltaTime = sfTime_asMilliseconds(sfClock_getElapsedTime(clock));
	sfClock_restart(clock);

	if(!manager->won)
	{
		manager->turnTime -= deltaTime;

		if(!manager->paused && manager->turnTime <= 0)
		{
			manager->turnTime = TURN_TIME;
			(manager->players[manager->playerTurn].getInput)(&(manager->board), manager->playerTurn, manager->players);

			MakeTurn(manager);
		}
	}
	else
	{
		printf("Player %d won!\n", manager->won);
		ResetGame(manager);
	}
}

void MakeTurn(GameManager* manager)
{
	int p = manager->playerTurn;



	int moves[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0}};

	int nextX = manager->players[p].position.x + moves[manager->players[p].direction][0];
	int nextY = manager->players[p].position.y + moves[manager->players[p].direction][1];

	if(nextX < 0 || nextX >= BOARD_WIDTH || nextY < 0 || nextY >= BOARD_HEIGHT || manager->board.blocked[nextX][nextY])
	{
		manager->won = p + 1;
		return;
	}

	manager->players[p].position.x = nextX;
	manager->players[p].position.y = nextY;

	manager->board.blocked[nextX][nextY] = p + 1;

	manager->playerTurn = (p + 1) % 2;
	manager->players[p].prevDirection = manager->players[p].direction;
}
