#include "AI.h"
#include "defines.h"

//UP = 0,
//RIGHT = 1,
//DOWN = 2,
//LEFT = 3

bfsQuery CreateNewQuery(int player, int x, int y)
{
	bfsQuery newQuery;

	newQuery.player = player;
	newQuery.x = x;
	newQuery.y = y;

	return newQuery;
}

void pushQueue(Queue* q, bfsQuery query)
{
	if(q->size)
	{
		++(q->size);
		q->end->next = (Node*)(malloc(sizeof(Node)));
		q->end = q->end->next;
		q->end->val = query;
	}
	else
	{
		q->size = 1;
		q->begin = (Node*)(malloc(sizeof(Node)));
		q->begin->val = query;
		q->end = q->begin;
	}
}

void popQueue(Queue* q)
{
	if(q->size)
	{
		if(q->size > 1)
		{
			Node* temp = q->begin;
			(q->size)--;
			q->begin = q->begin->next;
			free(temp);
		}
		else
		{
			q->size = 0;
			free(q->begin);
			q->begin = q->end = 0;
		}
	}
}

LL minimax(int player, int depth, int me, Player* players, Board* board, int * nextMove)
{
	int movePattern[4][2] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };

	if (depth != MINIMAX_DEPTH)
	{
		LL result = -LLINF - 1;
		int best_move = 0;

		if (player != me)
		{
			result = LLINF + 1;
		}

		FOR(i, 0, 4)
		{
			players[player].position.x += movePattern[i][0];
			players[player].position.y += movePattern[i][1];

			int nextX = players[player].position.x;
			int nextY = players[player].position.y;

			LL temp = 0;

			if (nextX < 0 || nextX >= BOARD_WIDTH || nextY < 0 || nextY >= BOARD_HEIGHT || board->blocked[nextX][nextY])
			{
				if (player != me)
				{
					temp = LLINF;
				}
				else
				{
					temp = -LLINF;
				}
			}
			else
			{
				board->blocked[nextX][nextY] = 1;
				temp = minimax((player + 1) & 1, depth + 1, me, players, board, nextMove);
				board->blocked[nextX][nextY] = 0;
			}

			if (player != me)
			{
				if (result > temp)
				{
					result = temp;
					best_move = i;
				}
			}
			else
			{
				if (result < temp)
				{
					result = temp;
					best_move = i;
				}
			}

			players[player].position.x -= movePattern[i][0];
			players[player].position.y -= movePattern[i][1];
		}

		if (depth == 0)
		{
			(*nextMove) = best_move;
		}

		return result;
	}
	else
	{
		int distBoard[BOARD_WIDTH][BOARD_HEIGHT];
		
		Queue bfs;
		bfs.size = 0;
		bfs.begin = bfs.end = 0;

		FOR(i, 0, BOARD_WIDTH)
		{
			FOR(j, 0, BOARD_HEIGHT)
			{
				distBoard[i][j] = 0;
			}
		}

		//CALCULATE RESULT
		LL closer = 0;
		LL edges = 0;
		LL opponent = 0;

		pushQueue(&bfs, CreateNewQuery(me, players[me].position.x, players[me].position.y));
		pushQueue(&bfs, CreateNewQuery((me + 1) & 1, players[(me + 1) & 1].position.x, players[(me + 1) & 1].position.y));

		while (bfs.size)
		{
			bfsQuery v = bfs.begin->val;
			popQueue(&bfs);

			FOR(i, 0, 4)
			{
				int nextX = v.x + movePattern[i][0];
				int nextY = v.y + movePattern[i][1];

				if (nextX >= 0 && nextX < BOARD_WIDTH && nextY >= 0 && nextY < BOARD_HEIGHT && !(board->blocked[nextX][nextY]))
				{
					if(v.player == me)
					{
						++edges;
					}

					if (!distBoard[nextX][nextY])
					{
						distBoard[nextX][nextY] = 1;
						
						pushQueue(&bfs, CreateNewQuery(v.player, nextX, nextY));

						if (v.player == me)
						{
							++closer;
						}
						else
						{
							++opponent;
						}
					}
				}
			}
		}

		return 1000ll* edges + closer * 1000ll + opponent * (-1ll);
	}
}
