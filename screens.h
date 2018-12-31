#ifndef SCREENS_H
#define SCREENS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct _Screen
{
	GLFWwindow* window;
	short int screenType;
	void (*Update)(struct _Screen*);

} Screen;

/*screenType - type of screen:
0 - Main Menu
1 - Game Screen
*/

Screen* CreateNewScreen(GLFWwindow*);

void UpdateMainMenu();
void UpdateGameScreen();

#endif