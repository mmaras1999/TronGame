#include <stdio.h>
#include <stdlib.h>

#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>

#include "constants.h"
#include "application.h"

sfRenderWindow* CreateWindow() //Create new window
{
	sfRenderWindow * window;
	sfVideoMode mode = {SCREEN_WIDTH, SCREEN_HEIGHT, 32};
	window = sfRenderWindow_create(mode, "SFML window", sfResize | sfClose, NULL);

	return window;
}

void DestroyWindow(sfRenderWindow* window) //Destroy window
{
	sfRenderWindow_destroy(window);
}

int main()
{
    sfRenderWindow* window = CreateWindow();

    if (!window) //if window is NULL
    {
    	printf("Fatal Error: error when creating a window\n");
    	return 1;
    }

    StartApp(window); //Start Application

    DestroyWindow(window);

	return 0;
}