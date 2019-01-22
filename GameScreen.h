#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SFML/Audio.h>
#include <SFML/Graphics.h>
#include <SFML/Window.h>
#include <SFML/System.h>

#include "screens.h"

void CreateGameScreen(sfRenderWindow*, Screen*);
void UpdateGameScreen(Screen*);
void DrawGameScreen(Screen*);
void CloseGameScreen(Screen*);

#endif
