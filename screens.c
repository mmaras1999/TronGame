#include "screens.h"

Screen* CreateNewScreen(GLFWwindow* window)
{
	Screen newScreen;
	Screen* ptr;

	newScreen.window = window;
	newScreen.screenType = 0;
	newScreen.Update = &UpdateMainMenu;

	ptr = &newScreen;

	return ptr;
}

void UpdateMainMenu(Screen* it)
{

}

void UpdateGameScreen(Screen* it)
{

}