#include "include/geometry.h"

// Generates a vertexArray and a static vertex buffer from an array of vertices and returns its vertex buffer object in vbo
void initializeBuffers(unsigned int *p_vao, unsigned int *p_vbo, float *vertices, GLenum gl_array_buffer)
{
	glGenVertexArrays(1, p_vao);

    	glGenBuffers(1, p_vbo); // 1 because we only need 1 buffer and vbo is the id of this buffer
    	
	glBindVertexArray(*p_vao); 

	
    	// We need to bind this new buffer to GL_ARRAY_BUFFER to define it's type
    	glBindBuffer(gl_array_buffer, *p_vbo);

    	// This function copies the user defined memory (VBO) into the bound buffer (GL_ARRAY_BUFFER)
    	glBufferData(gl_array_buffer, sizeof(vertices), vertices, GL_STATIC_DRAW); // the 'usage' is GL_STATIC_DRAW because the triangle won't move
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

}

