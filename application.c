#include "application.h"
#include "screens.h"

void StartApp(GLFWwindow* window)
{
	Screen currentScreen;

	CreateNewScreen(window, &currentScreen);

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	while(!currentScreen.closed) //Game Loop
	{
   		glfwSwapBuffers(window);
   		glfwPollEvents();

		(currentScreen.Draw)(&currentScreen); //Draw Screen
		(currentScreen.Update)(&currentScreen); //Update Game Logic
	}
}
