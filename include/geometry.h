#ifndef GEOM
#define GEOM
#include <GLFW/glfw3.h>


// Generates a static vertex buffer from an array of vertices and returns its vertex buffer object in vbo
void initializeBuffers(unsigned int *p_vao, unsigned int *p_vbo, float *vertices, GLenum gl_array_buffer);


/* Creates a vertex shader and stores its id in 'vertexshader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createVertexShader(unsigned int *vertexShader, const char* source);


/* Creates a Shader Program and stores its id in 'shaderProgram' and attaches 'vertesShader' and 'fragmentShader'.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);


#endif
