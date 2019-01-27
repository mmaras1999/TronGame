#include "GameScreen.h"
#include "gameManager.h"
#include "players.h"
#include "defines.h"


void CreateGameScreen(sfRenderWindow * window, Screen* screen)
{
	printf("In game screen\n");
	screen->window = window;

	screen->screenType = 1;

	screen->Update = &UpdateGameScreen;
	screen->Draw = &DrawGameScreen;
	screen->Close = &CloseGameScreen;

	screen->clock = sfClock_create();

	StartGame(&(screen->manager));
}

void UpdateGameScreen(Screen* screen)
{
	if(sfKeyboard_isKeyPressed(screen->manager.players[0].KeyRight))
    {
	 	screen->manager.players[0].leftClicked = 0;
       	screen->manager.players[0].rightClicked = 1;
    }

    if(sfKeyboard_isKeyPressed(screen->manager.players[0].KeyLeft))
    {
       	screen->manager.players[0].leftClicked = 1;
       	screen->manager.players[0].rightClicked = 0;
    }

    if(sfKeyboard_isKeyPressed(screen->manager.players[1].KeyRight))
    {
       	screen->manager.players[1].leftClicked = 0;
       	screen->manager.players[1].rightClicked = 1;
    }

    if(sfKeyboard_isKeyPressed(screen->manager.players[1].KeyLeft))
    {
       	screen->manager.players[1].leftClicked = 1;
       	screen->manager.players[1].rightClicked = 0;
    }

	UpdateGame(&(screen->manager), screen->clock);
}

void DrawGameScreen(Screen* screen)
{
	sfVector2f rectSize;
	rectSize.x = 20;
	rectSize.y = 20;

	sfRectangleShape * drawboard[BOARD_WIDTH][BOARD_HEIGHT];

	FOR(i, 0, BOARD_WIDTH)
	{
		FOR(j, 0, BOARD_HEIGHT)
		{
			drawboard[i][j] = sfRectangleShape_create();

			sfRectangleShape_setSize(drawboard[i][j], rectSize);
			sfVector2f pos;
			pos.x = 20 * i;
			pos.y = 20 * j;
			sfRectangleShape_setPosition(drawboard[i][j], pos);

			sfColor color;
			switch(screen->manager.board.blocked[i][j])
			{
				case 0:
					color = sfColor_fromRGB(100, 100, 100);
					break;
				case 1:
					color = sfCyan;
					break;
				case 2:
					color = sfRed;
					break;
			}

			sfRectangleShape_setFillColor(drawboard[i][j], color);

			sfRenderWindow_drawRectangleShape(screen->window, drawboard[i][j], 0);

			sfRectangleShape_destroy(drawboard[i][j]);
		}
	}
	//draw game board

}

void CloseGameScreen(Screen* screen)
{
	DestroyResources(screen);
	sfClock_destroy(screen->clock);
}
