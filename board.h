#ifndef BOARD_H
#define BOARD_H

#include "defines.h"


typedef struct _board
{
	int blocked[BOARD_WIDTH][BOARD_HEIGHT];
} Board;

#endif
