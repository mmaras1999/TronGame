#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>

#include "screens.h"

void CreateMainMenu(sfRenderWindow*, Screen*);
void UpdateMainMenu(Screen*);
void DrawMainMenu(Screen*);
void CloseMainMenu(Screen*);

void SetupBackground(UI_layer*, Screen*);
void UpdateMainMenuBackground(UI_layer*, Screen*);
void DrawMainMenuBackground(UI_layer*, Screen*);

void SetupMenuButtons(UI_layer*, Screen*);
void UpdateMenuButtons(UI_layer*, Screen*);
void DrawMenuButtons(UI_layer*, Screen*);

void SetupGameSettings(UI_layer*, Screen*);
void UpdateGameSettings(UI_layer*, Screen*);
void DrawGameSettings(UI_layer*, Screen*);

#endif