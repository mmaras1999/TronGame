#include <malloc.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <SFML/Window.h>

#include "screens.h"
#include "MainMenu.h"
#include "defines.h"
#include "UI.h"

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

void DestroyResources(Screen* this)
{
	FOR(i, 0, this->fontsCount)
	{
		sfFont_destroy(this->fonts[i]);
	}

	free(this->fonts);

	FOR(i, 0, this->textCount)
	{
		sfText_destroy(this->text[i]);
	}

	free(this->text);

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
