#ifndef SCREENS_H
#define SCREENS_H
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct _Screen
{
	GLFWwindow* window;
	
	short screenType;
	short closed;
	

	//Screen Functions
	void (*Update)(struct _Screen*);
	void (*Draw)(struct _Screen*);
	void (*Close)(struct _Screen*);
} Screen;

/*screenType - type of screen:
0 - Main Menu
1 - Game Screen
*/

void CreateNewScreen(GLFWwindow*, Screen*);
void ChangeScreen(Screen*, int);

void UpdateMainMenu(Screen*);
void UpdateGameScreen(Screen*);
void DrawMainMenu(Screen*);
void DrawGameScreen(Screen*);
void CloseMainMenu(Screen*);
void CloseGameScreen(Screen*);

#endif