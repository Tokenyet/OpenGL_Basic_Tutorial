// include c/c++ library
#include <iostream>
// GLEW ( help you using functions without retreiving functions )
#define GLEW_STATIC
#include <GL\glew.h>
// GLFW ( make you a windows that support opengl operation to work fine with your platform )
#include <GLFW\glfw3.h>

// Get error from GLFW for debuging
void error_callback(int error, const char* description);
// Get keywords from GLFW windows
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() 
{
	// Init and Check GLFW working properly
	int glfwInitCheck = glfwInit();
	if (glfwInitCheck == GLFW_FALSE)
	{
		std::cout << "glfw initilization failed." << std::endl;
		return -1;
	}

	// Create GLFW windows for requirement version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Tutorial", NULL, NULL);
	if (window == nullptr) // window creation failed
	{
		return -1;
	}
	glfwMakeContextCurrent(window);  // set current windows to interact with opengl api 

	// Set GLFW callback functions
	glfwSetErrorCallback(error_callback);
	glfwSetKeyCallback(window, key_callback);


	// According to source code, this make you to access successfully full extension from some latest driver without error.
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// Define the viewport dimensions (if you will change the winodw size, put these in loop)
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	// Looping Here until user trigger closing window event.
	while (!glfwWindowShouldClose(window))
	{
		// Clear the colorbuffer
		glClearColor(0.5f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window); // show on windows
		glfwPollEvents(); // check any event(ex. mousedown, keyup...)
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

void error_callback(int error, const char* description)
{
	fprintf(stderr, "Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}