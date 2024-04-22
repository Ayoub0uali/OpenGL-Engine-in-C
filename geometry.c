#include "include/glad/glad.h"
#include <GLFW/glfw3.h>


// Generates a vertexArray and a static vertex buffer from an array of vertices and returns its vertex buffer object in vbo
void initializeBuffers(unsigned int *p_vao, unsigned int *p_vbo, float *vertices, GLenum gl_array_buffer)
{
	glGenVertexArrays(1, p_vao);

    	glBindVertexArray(*p_vao); 

    	glGenBuffers(1, p_vbo); // 1 because we only need 1 buffer and vbo is the id of this buffer
	
    	// We need to bind this new buffer to GL_ARRAY_BUFFER to define it's type
    	glBindBuffer(gl_array_buffer, *p_vbo);

    	// This function copies the user defined memory (VBO) into the bound buffer (GL_ARRAY_BUFFER)
    	glBufferData(gl_array_buffer, sizeof(vertices), vertices, GL_STATIC_DRAW); // the 'usage' is GL_STATIC_DRAW because the triangle won't move
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);  
}


/* Creates a vertex shader and stores its id in 'vertexShader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createVertexShader(unsigned int *vertexShader, const char* source)
{
    	*vertexShader = glCreateShader(GL_VERTEX_SHADER); //GL_VERTEX_SHADER is the type of shader we need to create
    
    	// This will compile the source into the shader I wrote 1 because &vertexShaderSource contains 1 string
    	glShaderSource(*vertexShader, 1, &source, NULL);
    	glCompileShader(*vertexShader);

    	// We need to test if the compilation is successful
    	int test;
    	glGetShaderiv(*vertexShader, GL_COMPILE_STATUS, &test);
    	if (!test) {
		glDeleteShader(*vertexShader);
		return 0;
    	}

	return 1;
}



/* Creates a fragment shader and stores its id in 'fragmentShader' and compiles 'source' into it.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createFragmentShader(unsigned int *fragmentShader, const char* source)
{
	*fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    	glShaderSource(*fragmentShader, 1, &source, NULL);
    	glCompileShader(*fragmentShader);

    	int test;
    	glGetShaderiv(*fragmentShader, GL_COMPILE_STATUS, &test);
    	if (!test) {
            	glDeleteShader(*fragmentShader);
	    	return 0;
    	}

    	return 1;
}


/* Creates a Shader Program and stores its id in 'shaderProgram' and attaches 'vertesShader' and 'fragmentShader'.
 * Returns 1 if the creation is successful else returns 0 upon failure
 */
int createShaderProgram(unsigned int *shaderProgram, unsigned int vertexShader, unsigned int fragmentShader)
{
    	*shaderProgram = glCreateProgram();

    	glAttachShader(*shaderProgram, vertexShader);
    	glAttachShader(*shaderProgram, fragmentShader);
    	glLinkProgram(*shaderProgram);

    	// Test
    	int test;
    	glGetProgramiv(*shaderProgram, GL_LINK_STATUS, &test);
    	if(!test) {
		return 0;
    	}
	
	return 1;
}
