#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "application.h"


int main()
{

	if(!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW.\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 8); // 8x antialiasing	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

	// Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
	window = glfwCreateWindow( 1024, 768, "TronGame", NULL, NULL);
	
	if(window == NULL)
	{
   		fprintf( stderr, "Failed to open GLFW window.\n" );
   	 	glfwTerminate();
   	 	return -1;
	}

	glfwMakeContextCurrent(window); // Initialize GLEW
	glewExperimental = 1; // Needed in core profile
	
	if (glewInit() != GLEW_OK) 
	{
   	 	fprintf(stderr, "Failed to initialize GLEW\n");
    	return -1;
	}

	StartApp(window);

	return 0;
}