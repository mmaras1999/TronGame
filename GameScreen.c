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

	//Load graphics
	screen->fontsCount = 1;
	screen->textCount = 0;
	screen->texturesCount = 1;
	screen->spritesCount = 1;

	screen->fonts = (sfFont**)(malloc(screen->fontsCount * sizeof(sfFont*)));
	screen->text = (sfText**)(malloc(screen->textCount * sizeof(sfText*)));
	screen->textures = (sfTexture**)(malloc(screen->texturesCount * sizeof(sfTexture*)));
	screen->sprites = (sfSprite**)(malloc(screen->spritesCount * sizeof(sfSprite*)));

	screen->textures[0] = sfTexture_createFromFile("Assets/Images/Tile.png", NULL);
	screen->fonts[0] = sfFont_createFromFile("Assets/Fonts/SpaceAge.ttf");

	if(CheckLoadedResources(screen))
	{
		printf("FATAL ERROR: Failed loading Game Screen resources!\n");
		CloseGameScreen(screen);
		sfRenderWindow_close(screen->window);
		return;
	}

	FOR(i, 0, screen->textCount)
	{
		screen->text[i] = sfText_create();
	}

	FOR(i, 0, screen->spritesCount)
	{
		screen->sprites[i] = sfSprite_create();
	}

	screen->clock = sfClock_create();

	StartGame(&(screen->manager));
}

void UpdateGameScreen(Screen* screen)
{
	UpdateGame(&(screen->manager), screen->clock);
}

void DrawGameScreen(Screen* screen)
{
	sfRenderWindow_clear(screen->window, sfDarkBlue);

	sfVector2f rectSize;
	int firstX = 10;
	int firstY = 100;
	rectSize.x = 20;
	rectSize.y = 20;

	sfRectangleShape * drawboard[BOARD_WIDTH][BOARD_HEIGHT];

	FOR(i, 0, BOARD_WIDTH)
	{
		FOR(j, 0, BOARD_HEIGHT)
		{
			if(!screen->manager.board.blocked[i][j])
			{
				sfVector2f pos;
				pos.x = 20 * i + firstX;
				pos.y = 20 * j + firstY;
				sfSprite_setTexture(screen->sprites[0], screen->textures[0], sfTrue);
				sfSprite_setPosition(screen->sprites[0], pos);
				sfRenderWindow_drawSprite(screen->window, screen->sprites[0], NULL);
			}
			else
			{

				drawboard[i][j] = sfRectangleShape_create();

				sfRectangleShape_setSize(drawboard[i][j], rectSize);
				sfVector2f pos;
				pos.x = 20 * i + firstX;
				pos.y = 20 * j + firstY;
				sfRectangleShape_setPosition(drawboard[i][j], pos);

				sfColor color = screen->manager.players[screen->manager.board.blocked[i][j] - 1].color;


				sfRectangleShape_setFillColor(drawboard[i][j], color);

				sfRenderWindow_drawRectangleShape(screen->window, drawboard[i][j], 0);

				sfRectangleShape_destroy(drawboard[i][j]);
			}
		}
	}
	//draw game board
}

void CloseGameScreen(Screen* screen)
{
	DestroyResources(screen);
	sfClock_destroy(screen->clock);
}
