#include "gameManager.h"
#include "defines.h"

void ResetGame(GameManager* manager)
{
	manager->won = 0;
	manager->playerTurn = 1;
	manager->paused = 0;
	manager->escDown = 1;
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
	manager->players[0].rightReleased = 1;
	manager->players[0].leftReleased = 1;

	manager->players[1].position = position2;
	manager->players[1].direction = dir2;
	manager->players[1].prevDirection = dir2;
	manager->players[1].rightClicked = 0;
	manager->players[1].leftClicked = 0;
	manager->players[1].rightReleased = 1;
	manager->players[1].leftReleased = 1;

	manager->board.blocked[manager->players[0].position.x][manager->players[0].position.y] = 1;
	manager->board.blocked[manager->players[1].position.x][manager->players[1].position.y] = 2;
}

void UpdateGame(GameManager* manager, sfClock * clock)
{
	int deltaTime = sfTime_asMilliseconds(sfClock_getElapsedTime(clock));
	sfClock_restart(clock);

	if(!manager->paused)
	{	
		CheckInput(manager);

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
			++manager->players[manager->won - 1].score;

			if(manager->players[manager->won - 1].score < manager->totalRounds)
			{
				ResetGame(manager);
			}
			else
			{
				manager->paused = 1;
			}
		}
	}
}

void CheckInput(GameManager* manager)
{
    if(sfKeyboard_isKeyPressed(manager->players[0].KeyLeft))
    {
    	if(manager->players[0].leftReleased)
    	{
	       	manager->players[0].leftClicked = 1;
	       	manager->players[0].rightClicked = 0;
    		manager->players[0].leftReleased = 0;
    	}
    }
    else
    {
    	manager->players[0].leftReleased = 1;
    }

    if(sfKeyboard_isKeyPressed(manager->players[0].KeyRight))
    {
    	if(manager->players[0].rightReleased)
    	{
		 	manager->players[0].leftClicked = 0;
	       	manager->players[0].rightClicked = 1;
	       	manager->players[0].rightReleased = 0;
       	}
    }
    else
    {
    	manager->players[0].rightReleased = 1;
    }

     if(sfKeyboard_isKeyPressed(manager->players[1].KeyLeft))
    {
    	if(manager->players[1].leftReleased)
    	{
	       	manager->players[1].leftClicked = 1;
	       	manager->players[1].rightClicked = 0;
    		manager->players[1].leftReleased = 0;
    	}
    }
    else
    {
    	manager->players[1].leftReleased = 1;
    }

    if(sfKeyboard_isKeyPressed(manager->players[1].KeyRight))
    {
    	if(manager->players[1].rightReleased)
    	{
		 	manager->players[1].leftClicked = 0;
	       	manager->players[1].rightClicked = 1;
	       	manager->players[1].rightReleased = 0;
       	}
    }
    else
    {
    	manager->players[1].rightReleased = 1;
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
		manager->won = (p + 1) % 2 + 1;
		return;
	}

	manager->players[p].position.x = nextX;
	manager->players[p].position.y = nextY;

	manager->board.blocked[nextX][nextY] = p + 1;

	manager->playerTurn = (p + 1) % 2;
	manager->players[p].prevDirection = manager->players[p].direction;
}
