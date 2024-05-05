// This library handles all things related to shaders such as creating a fragment or a vertex shader as well as the shader program
#ifndef SHADERS
#define SHADERS

#include "glad/glad.h"
#include <GLFW/glfw3.h>


// Reads the content of the files in the vertexPath and fragmentPath then compiles it and returns 1 upon success or 0 upon failure
int shadersFromFile(char* vertexPath, char* fragmentPath, GLuint *vertexShader, GLuint *fragmentShader);
/* Creates a fragment shader and stores its id in 'fragmentShader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createFragmentShader(unsigned int *fragmentShader, const char* source);


/* Creates a vertex shader and stores its id in 'vertexshader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createVertexShader(unsigned int *vertexShader, const char* source);


/* Creates a Shader Program and stores its id in 'shaderProgram' and attaches 'vertesShader' and 'fragmentShader'.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader);

#endif
