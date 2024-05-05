// This is a file that contains the opengl basic functions and boiler plate
#include "include/gl_basics.h"



// Contains the boiler plate for initializing GLFW the window library
void initializeGLFW()
{
	// Initialize glfw the window library
	glfwInit();

	// Indicate the major and minor OpenGL version we will use. In this case 3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// Indicate the profile. As I understand CORE is the modern core there is also a legacy core
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}


// Creates a GLFW window with a specific width, height and name. Returns 1 if it is successful and 0 if it fails
int createWindow(GLFWwindow** window, int width, int height, char* name)
{
	// Creating a window
	*window = glfwCreateWindow(width, height, name, NULL, NULL);
	if ((*window) == NULL) {
        	return 0;
    	}

	// Binds the window to glfw to display it
	glfwMakeContextCurrent(*window);
	return 1;
}


// This is a function that gets called everytime the window is resized to resize the OpenGL viewport to match it
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



/* This function performs all the necessary initialization and creates a window that is linked to the OpenGL viewport.
 * It return 1 if it is successful and 0 if it fails.
 */
int initializeGL(GLFWwindow** window, int width, int height, char* name)
{
	// Initialize glfw
	initializeGLFW();

	// Creating a window
	if (!createWindow(window, width, height, name)) {
        	return 0;
    	}

	// Initialize Glad because OpenGL is a set of specification and not an api
	// so we need glad to grab the specific implementation of the machine
    	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
        	return 0;
    	}

	// Initializing the OpenGL viewport which is the area that OpenGL renders to
	glViewport(0, 0, width, height);

	// OpenGL viewport is different from the window this callback will resize it everytime it changes
	glfwSetFramebufferSizeCallback(*window, framebuffer_size_callback);

	return 1;
}
