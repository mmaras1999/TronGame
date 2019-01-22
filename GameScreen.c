#include "GameScreen.h"
#include "defines.h"

void CreateGameScreen(sfRenderWindow * window, Screen* screen)
{
	printf("In game screen\n");
	screen->window = window;

	screen->screenType = 1;

	screen->Update = &UpdateGameScreen;
	screen->Draw = &DrawGameScreen;
	screen->Close = &CloseGameScreen;
}

void UpdateGameScreen(Screen* screen)
{
	//do nth
}

void DrawGameScreen(Screen* screen)
{
	//do nth
}

void CloseGameScreen(Screen* screen)
{
	//do nth
}
