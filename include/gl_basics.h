#ifndef GL_BASICS
#define GL_BASICS

#include "glad/glad.h"
#include <GLFW/glfw3.h>


/* This function performs all the necessary initialization and creates a window that is linked to the OpenGL viewport.
 * It return 1 if it is successful and 0 if it fails.
 */
int initializeGL(GLFWwindow** window, int width, int height, char* name);


#endif
