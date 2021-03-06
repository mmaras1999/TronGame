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
        if(!sfKeyboard_isKeyPressed(sfKeyReturn)) //Enter released
        {
            currentScreen.manager.enterDown = 0;
        }

        if(!sfKeyboard_isKeyPressed(sfKeyEscape)) //Escape released
        {
            currentScreen.manager.escDown = 0;
        }

        if(!sfMouse_isButtonPressed(sfMouseLeft)) //Left Mouse Button Released
        {
            currentScreen.manager.mouseClicked = 0;
        }

        sfRenderWindow_clear(window, sfBlack);

        (currentScreen.Draw)(&currentScreen); //Draw Screen
        (currentScreen.Update)(&currentScreen); //Update Game Logic

        while (sfRenderWindow_pollEvent(window, &event)); //To prevent "window not responding" pop up
       
        sfRenderWindow_display(window);
    }
}
