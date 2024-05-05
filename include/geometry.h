#ifndef GEOM
#define GEOM

#include "glad/glad.h"
#include <GLFW/glfw3.h>


// Generates a static vertex buffer from an array of vertices and returns its vertex buffer object in vbo
void initializeBuffers(unsigned int *p_vao, unsigned int *p_vbo, float *vertices, GLenum gl_array_buffer);


#endif
