#ifndef SCREENS_H
#define SCREENS_H
#include <stdio.h>
#include <stdlib.h>

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>

#include "UI.h"
#include "gameManager.h"

typedef struct _Screen
{
	sfRenderWindow* window; //pointer to window
	sfEvent* event; //pointer to event handler
	
	short screenType; //screen type
	
	sfClock * clock;

	//Game
	GameManager manager;

	//UI
	int UIlayersCount;
	UI_layer* UIlayers;

	//Graphics
	int fontsCount;
	int textCount;
	int texturesCount;
	int spritesCount;

	sfTexture ** textures;
	sfFont ** fonts;
	sfSprite ** sprites;
	sfText ** text;

	//Screen Functions
	void (*Update)(struct _Screen*); //Update screen
	void (*Draw)(struct _Screen*); //Draw screen
	void (*Close)(struct _Screen*); //Close screen (destroy all screen components)
} Screen;

/*screenType - type of screen:
0 - Main Menu
1 - Game Screen
*/

void CreateNewScreen(sfRenderWindow*, Screen*);
void CreateGameScreen(sfRenderWindow*, Screen*);
void ChangeScreen(Screen*, int);

void DestroyResources(Screen*);
int CheckLoadedResources(Screen*);

#endif
