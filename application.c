#include "application.h"
#include "screens.h"

void StartApp(sfRenderWindow* window)
{
	Screen currentScreen;
	sfEvent event; //handles events

	CreateNewScreen(window, &currentScreen); //Set up new scene (main menu)
	currentScreen.event = &event;

    while (sfRenderWindow_isOpen(window)) //Game Loop
    {
        sfRenderWindow_clear(window, sfBlack);

        (currentScreen.Draw)(&currentScreen); //Draw Screen
        (currentScreen.Update)(&currentScreen); //Update Game Logic

        while (sfRenderWindow_pollEvent(window, &event)); //To prevent "window not responding" pop up
       
       sfRenderWindow_display(window);
    }
}
