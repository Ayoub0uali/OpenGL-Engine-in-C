#ifndef GL_BASICS
#define GL_BASICS

#include <GLFW/glfw3.h>


/* This function performs all the necessary initialization and creates a window that is linked to the OpenGL viewport.
 * It return 1 if it is successful and 0 if it fails.
 */
int initializeGL(GLFWwindow** window, int width, int height, char* name);


/* Creates a fragment shader and stores its id in 'fragmentShader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createFragmentShader(unsigned int *fragmentShader, const char* source);


#endif
