#include <malloc.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>

#include "screens.h"
#include "constants.h"
//#include "UI.h"

#define FOR(a, b, c) for(int a = b; a < c; ++a)

void CreateNewScreen(sfRenderWindow* window, Screen* newScreen)
{
	CreateMainMenu(window, newScreen);
}

void ChangeScreen(Screen* screen, int screenType)
{
	screen->screenType = screenType;
	(screen->Close)(screen);

	switch(screenType)
	{
		case 0:
		{
			CreateMainMenu(screen->window, screen);
			break;
		}	

		case 1:
		{
			CreateGameScreen(screen->window, screen);
			break;
		}

		default: //ERROR - wrong scene - close to prevent errors
		{
			sfRenderWindow_close(screen->window);
			break;
		}
	}
}

void CreateMainMenu(sfRenderWindow* window, Screen* screen)
{
	printf("In main menu\n");
	screen->window = window;

	screen->screenType = 0;

	screen->Update = &UpdateMainMenu;
	screen->Draw = &DrawMainMenu;
	screen->Close = &CloseMainMenu;

	//SETUP UI - TBD
	/*
	#define UI_ELEMENT(A, B) screen->UIlayers[ A ].elements[ B ];
	screen->UIlayersCount = 1;
	screen->UIlayers = (UI_layer*)(malloc(sizeof(UI_layer)));

	screen->UIlayers[0].elementCount = 1;
	screen->UIlayers[0].locked = 0;
	screen->UIlayers[0].hidden = 0;
	screen->UIlayers[0].elements = (UI_element*)malloc(sizeof(UI_element));

	UI_ELEMENT(0, 0).locked = 0;
	UI_ELEMENT(0, 0).hidden = 0;
	*/

	//Load graphics
	screen->fontsCount = 0;
	screen->texturesCount = 1;
	screen->spritesCount = 1;

	screen->fonts = (sfFont**)(malloc(0 * sizeof(sfFont*)));
	screen->textures = (sfTexture**)(malloc(1 * sizeof(sfTexture*)));
	screen->sprites = (sfSprite**)(malloc(1 * sizeof(sfSprite*)));

	screen->textures[0] = sfTexture_createFromFile("assets/MainMenuBackground.png", NULL);

	if(CheckLoadedResources(screen))
	{
		printf("FATAL ERROR: Failed loading Main Menu resources!\n");
		CloseMainMenu(screen);
		sfRenderWindow_close(screen->window);
		return;
	}

	sfVector2f scale;
	scale.x = (float)(SCREEN_WIDTH) / 1920.f;
	scale.y = (float)(SCREEN_HEIGHT) / 1080.f; 
	screen->sprites[0] = sfSprite_create();
	sfSprite_setTexture(screen->sprites[0], screen->textures[0], sfTrue);
	sfSprite_setScale(screen->sprites[0], scale);

}

void CreateGameScreen(sfRenderWindow* window, Screen* screen)
{	
	printf("In game screen\n");
	screen->window = window;

	screen->screenType = 1;

	screen->Update = &UpdateGameScreen;
	screen->Draw = &DrawGameScreen;
	screen->Close = &CloseGameScreen;
}


void UpdateMainMenu(Screen* this)
{
	if(sfKeyboard_isKeyPressed(sfKeyEscape)) //Exit Game
	{
		ChangeScreen(this, -1); //Close App
	}

	if(sfKeyboard_isKeyPressed(sfKeyReturn)) //Enter pressed
	{
		ChangeScreen(this, 1); //Proceed to game screen
	}

	//UpdateLayer(&this->UIlayers[0]);
}

void UpdateGameScreen(Screen* this)
{

}

void DrawMainMenu(Screen* this)
{
	sfRenderWindow_drawSprite(this->window, this->sprites[0], NULL);
}

void DrawGameScreen(Screen* this)
{

}

void CloseMainMenu(Screen * this)
{
	//FOR(i, 0, this->UIlayersCount)
	//{
	//	free(this->UIlayers[i].elements);
	//}

	//free(this->UIlayers);

	DestroyResources(this);

	printf("closed\n");
}

void CloseGameScreen(Screen * this)
{

}


void DestroyResources(Screen* this)
{
	FOR(i, 0, this->fontsCount)
	{
		sfFont_destroy(this->fonts[i]);
	}

	free(this->fonts);

	FOR(i, 0, this->texturesCount)
	{
		sfTexture_destroy(this->textures[i]);
	}

	free(this->textures);

	FOR(i, 0, this->spritesCount)
	{
		sfSprite_destroy(this->sprites[i]);
	}

	free(this->sprites);
}

int CheckLoadedResources(Screen* this)
{
	FOR(i, 0, this->fontsCount)
	{
		if(!(this->fonts[i]))
		{
			return 1;
		}
	}

	FOR(i, 0, this->texturesCount)
	{
		if(!(this->textures[i]))
		{
			return 1;
		}
	}

	return 0;
}