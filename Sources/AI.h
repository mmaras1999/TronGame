#ifndef AI_H
#define AI_H

#include <malloc.h>

#include "defines.h"
#include "players.h"

typedef struct _bfsQuery
{
	int player;
	int x;
	int y;
} bfsQuery;

typedef struct _node
{
	struct _node* next;
	bfsQuery val;

} Node;

typedef struct _Queue
{
	Node* begin;
	Node* end;
	int size;

} Queue;

bfsQuery CreateNewQuery(int, int, int);
void pushQueue(Queue*, bfsQuery);
void popQueue(Queue*);
LL minimax(int, int, int, Player*, Board*, int*);

#endif
