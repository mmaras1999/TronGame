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
	screen->textCount = 3 + 1 + 2;
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

	//SETUP UI
	#define UI_LAYERS screen->UIlayers
	screen->UIlayersCount = 3;
	UI_LAYERS = (UI_layer*)(malloc(screen->UIlayersCount * sizeof(UI_layer)));
	
	SetupScoreboard(&(UI_LAYERS[0]), screen);
	SetupPause(&(UI_LAYERS[1]), screen);
	SetupWin(&(UI_LAYERS[2]), screen);

	ResetGame(&(screen->manager));
}

void UpdateGameScreen(Screen* screen)
{
	UpdateGame(&(screen->manager), screen->clock);
	UpdateScoreBoard(&(screen->UIlayers[0]), screen);
	UpdatePause(&(screen->UIlayers[1]), screen);
	UpdateWin(&(screen->UIlayers[2]), screen);
}

void DrawGameScreen(Screen* screen)
{
	sfRenderWindow_clear(screen->window, sfDarkBlue);

	sfVector2f rectSize;
	int firstX = 140;
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
	
	DrawScoreBoard(&(screen->UIlayers[0]), screen);
	DrawPause(&(screen->UIlayers[1]), screen);
	DrawWin(&(screen->UIlayers[2]), screen);
}

void CloseGameScreen(Screen* screen)
{
	free(screen->UIlayers[0].text[1].txt);
	free(screen->UIlayers[0].text[2].txt);

	DestroyResources(screen);
	sfClock_destroy(screen->clock);
}

void SetupScoreboard(UI_layer* ui, Screen* screen)
{
	ui->updating = 1; //is updating
	ui->drawing = 1; //is drawing
	
	ui->imageCount = 0;
	ui->buttonCount = 0;
	ui->textCount = 3;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->text[0].txt = "Score:";
	ui->text[0].text = screen->text[0];
	ui->text[0].color = sfWhite;

	ui->text[1].txt = (char*)(malloc(12 * sizeof(char)));
	sprintf(ui->text[1].txt, "%d", 0);
	ui->text[1].text = screen->text[1];
	ui->text[1].color = sfWhite;

	ui->text[2].txt = (char*)(malloc(12 * sizeof(char)));
	sprintf(ui->text[2].txt, "%d", 0);
	ui->text[2].text = screen->text[2];
	ui->text[2].color = sfWhite;

	sfText_setFont(ui->text[0].text, screen->fonts[0]);
	sfText_setFont(ui->text[1].text, screen->fonts[0]);
	sfText_setFont(ui->text[2].text, screen->fonts[0]);

	sfText_setString(ui->text[0].text, ui->text[0].txt);
	sfText_setString(ui->text[1].text, ui->text[1].txt);
	sfText_setString(ui->text[2].text, ui->text[2].txt);

	sfText_setCharacterSize(ui->text[0].text, 30);
	sfText_setCharacterSize(ui->text[1].text, 35);
	sfText_setCharacterSize(ui->text[2].text, 35);

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	//SCORE text
	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = 20;
	sfText_setPosition(ui->text[0].text, newPos);

	//P1 Score text
	bounds = sfText_getLocalBounds(ui->text[1].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[1].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f - 150;
	newPos.y = 70;
	sfText_setPosition(ui->text[1].text, newPos);

	//P2 Score text
	bounds = sfText_getLocalBounds(ui->text[2].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[2].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f + 150;
	newPos.y = 70;
	sfText_setPosition(ui->text[2].text, newPos);
}

void SetupPause(UI_layer* ui, Screen* screen)
{
	ui->updating = 0; //is updating
	ui->drawing = 0; //is drawing
	
	ui->imageCount = 0;
	ui->buttonCount = 0;
	ui->textCount = 1;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->text[0].txt = "Game paused";
	ui->text[0].text = screen->text[3];
	ui->text[0].color = sfWhite;

	sfText_setFont(ui->text[0].text, screen->fonts[0]);
	sfText_setString(ui->text[0].text, ui->text[0].txt);
	sfText_setCharacterSize(ui->text[0].text, 50);

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	//SCORE text
	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f;
	sfText_setPosition(ui->text[0].text, newPos);
}

void SetupWin(UI_layer* ui, Screen* screen)
{
	ui->updating = 0; //is updating
	ui->drawing = 0; //is drawing
	
	ui->imageCount = 0;
	ui->buttonCount = 1;
	ui->textCount = 2;

	ui->buttons = (UI_button*)(malloc(ui->buttonCount * sizeof(UI_button)));
	ui->images = (UI_image*)(malloc(ui->imageCount * sizeof(UI_image)));
	ui->text = (UI_text*)(malloc(ui->textCount * sizeof(UI_text)));

	ui->text[0].txt = "Player 1 wins!";
	ui->text[0].text = screen->text[4];
	ui->text[0].color = sfWhite;

	ui->text[1].txt = "Continue";
	ui->text[1].text = screen->text[5];
	ui->text[1].color = sfWhite;

	sfText_setFont(ui->text[0].text, screen->fonts[0]);
	sfText_setString(ui->text[0].text, ui->text[0].txt);
	sfText_setCharacterSize(ui->text[0].text, 50);

	sfText_setFont(ui->text[1].text, screen->fonts[0]);
	sfText_setString(ui->text[1].text, ui->text[1].txt);
	sfText_setCharacterSize(ui->text[1].text, 35);

	sfVector2f origin;
	sfVector2f newPos;
	sfFloatRect bounds;

	//Win text
	//Set text origin and position
	bounds = sfText_getLocalBounds(ui->text[0].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[0].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f;
	sfText_setPosition(ui->text[0].text, newPos);

	//Continue text
	bounds = sfText_getLocalBounds(ui->text[1].text);
	origin.x = bounds.left + bounds.width/2.0f;
	origin.y = bounds.top  + bounds.height/2.0f;
	sfText_setOrigin(ui->text[1].text, origin);
	newPos.x = SCREEN_WIDTH / 2.0f;
	newPos.y = SCREEN_HEIGHT / 2.0f + 100;
	sfText_setPosition(ui->text[1].text, newPos);

	//Continue button
	bounds = sfText_getGlobalBounds(ui->text[1].text);
	ui->buttons[0].x = bounds.left; //x position of left top
	ui->buttons[0].y = bounds.top; //y position of left top
	ui->buttons[0].width = bounds.width;
	ui->buttons[0].height = bounds.height;
	ui->buttons[0].clicked = 0;
	ui->buttons[0].highlighted = 0;
}

void UpdateScoreBoard(UI_layer* ui, Screen* screen)
{
	if(ui->updating)
	{
		sfVector2f origin;
		sfVector2f newPos;
		sfFloatRect bounds;

		sprintf(ui->text[1].txt, "%d", screen->manager.players[0].score);
		sprintf(ui->text[2].txt, "%d", screen->manager.players[1].score);
		sfText_setString(ui->text[1].text, ui->text[1].txt);
		sfText_setString(ui->text[2].text, ui->text[2].txt);

		//P1 Score text
		bounds = sfText_getLocalBounds(ui->text[1].text);
		origin.x = bounds.left + bounds.width/2.0f;
		origin.y = bounds.top  + bounds.height/2.0f;
		sfText_setOrigin(ui->text[1].text, origin);
		newPos.x = SCREEN_WIDTH / 2.0f - 150;
		newPos.y = 70;
		sfText_setPosition(ui->text[1].text, newPos);

		//P2 Score text
		bounds = sfText_getLocalBounds(ui->text[2].text);
		origin.x = bounds.left + bounds.width/2.0f;
		origin.y = bounds.top  + bounds.height/2.0f;
		sfText_setOrigin(ui->text[2].text, origin);
		newPos.x = SCREEN_WIDTH / 2.0f + 150;
		newPos.y = 70;
		sfText_setPosition(ui->text[2].text, newPos);

		if(sfKeyboard_isKeyPressed(sfKeyEscape) && !screen->manager.escDown)
		{
			screen->manager.escDown = 1;
			screen->manager.paused = 1;

			ui->updating = 0;
			screen->UIlayers[1].drawing = 1;
			screen->UIlayers[1].updating = 1;
			return;
		}

		if(screen->manager.players[0].score == screen->manager.totalRounds || screen->manager.players[1].score == screen->manager.totalRounds)
		{
			if(screen->manager.players[0].score == screen->manager.totalRounds)
			{
				screen->UIlayers[2].text[0].txt = "Player 1 wins!";
				sfText_setString(screen->UIlayers[2].text[0].text, screen->UIlayers[2].text[0].txt);
			}
			else
			{
				screen->UIlayers[2].text[0].txt = "Player 2 wins!";
				sfText_setString(screen->UIlayers[2].text[0].text, screen->UIlayers[2].text[0].txt);
			}

			screen->manager.paused = 1;
			ui->updating = 0;

			screen->UIlayers[2].drawing = 1;
			screen->UIlayers[2].updating = 1;
		}
	}
}

void UpdatePause(UI_layer* ui, Screen* screen)
{
	if(ui->updating)
	{
		if(sfKeyboard_isKeyPressed(sfKeyEscape) && !screen->manager.escDown)
		{
			screen->manager.escDown = 1;
			screen->manager.paused = 0;

			screen->UIlayers[0].updating= 1;
			ui->drawing = 0;
			ui->updating = 0;
			return;
		}
	}
}

void UpdateWin(UI_layer* ui, Screen* screen)
{
	if(ui->updating)
	{
		sfVector2i mousePos = sfMouse_getPositionRenderWindow(screen->window);

		if(sfKeyboard_isKeyPressed(sfKeyReturn) && !(screen->manager.enterDown)) //Enter pressed
		{
			screen->manager.enterDown = 1;
			ChangeScreen(screen, 0);
			return;
		}

		if(ui->buttons[0].highlighted)
		{
			if(ui->buttons[0].x <= mousePos.x && mousePos.x <= ui->buttons[0].x + ui->buttons[0].width && ui->buttons[0].y <= mousePos.y && mousePos.y <= ui->buttons[0].y + ui->buttons[0].height)
			{
				if(sfMouse_isButtonPressed(sfMouseLeft) && !(screen->manager.mouseClicked))
				{
					screen->manager.mouseClicked = 1;
					ChangeScreen(screen, 0);
					return;
				}
			}
			else
			{
				ui->buttons[0].highlighted = 0;
				sfText_setFillColor(ui->text[1].text, sfWhite);
			}
		}
		else
		{
			if(ui->buttons[0].x <= mousePos.x && mousePos.x <= ui->buttons[0].x + ui->buttons[0].width && ui->buttons[0].y <= mousePos.y && mousePos.y <= ui->buttons[0].y + ui->buttons[0].height)
			{
				ui->buttons[0].highlighted = 1;
				sfColor highl = sfColor_fromRGB(200, 200, 200);
				sfText_setFillColor(ui->text[1].text, highl);
			}
		}
	}
}

void DrawScoreBoard(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawText(screen->window, ui->text[0].text, NULL);
		sfRenderWindow_drawText(screen->window, ui->text[1].text, NULL);
		sfRenderWindow_drawText(screen->window, ui->text[2].text, NULL);
	}
}

void DrawPause(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawText(screen->window, ui->text[0].text, NULL);
	}
}

void DrawWin(UI_layer* ui, Screen* screen)
{
	if(ui->drawing)
	{
		sfRenderWindow_drawText(screen->window, ui->text[0].text, NULL);
		sfRenderWindow_drawText(screen->window, ui->text[1].text, NULL);
	}
}
