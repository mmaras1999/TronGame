#include "screens.h"

void CreateNewScreen(GLFWwindow* window, Screen* newScreen)
{
	newScreen->window = window;
	newScreen->screenType = 0;
	newScreen->closed = 0;
	newScreen->Update = &UpdateMainMenu;
	newScreen->Draw = &DrawMainMenu;
	newScreen->Close = &CloseMainMenu;
}

void ChangeScreen(Screen* screen, int screenType)
{
	screen->screenType = screenType;
	(screen->Close)(screen);

	switch(screenType)
	{
		case 0:
		{
			screen->screenType = 0;
			screen->Update = &UpdateMainMenu;
			screen->Draw = &DrawMainMenu;
			screen->Close = &CloseMainMenu;
			break;
		}	

		case 1:
		{
			screen->screenType = 1;
			screen->Update = &UpdateGameScreen;
			screen->Draw = &DrawGameScreen;
			screen->Close = &CloseGameScreen;
			break;
		}

		default: //ERROR - wrong scene - close to prevent errors
		{
			screen->closed = 1;
			break;
		}
	}
}

void UpdateMainMenu(Screen* this)
{
	if(glfwGetKey(this->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) //Exit Game
	{
		printf("KeyPressed");
		this->closed = 1;
	}

	if(glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS) //Proceed to Game Screen
	{
		ChangeScreen(this, 1);
	}
}

void UpdateGameScreen(Screen* this)
{

}

void DrawMainMenu(Screen* this)
{

}

void DrawGameScreen(Screen* this)
{

}

void CloseMainMenu(Screen * this)
{

}

void CloseGameScreen(Screen * this)
{

}