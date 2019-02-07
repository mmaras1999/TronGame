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

void SetupScoreboard(UI_layer*, Screen*);
void SetupPause(UI_layer*, Screen*);
void SetupWin(UI_layer*, Screen*);

void UpdateScoreBoard(UI_layer*, Screen*);
void UpdatePause(UI_layer*, Screen*);
void UpdateWin(UI_layer*, Screen*);

void DrawScoreBoard(UI_layer*, Screen*);
void DrawPause(UI_layer*, Screen*);
void DrawWin(UI_layer*, Screen*);

#endif
