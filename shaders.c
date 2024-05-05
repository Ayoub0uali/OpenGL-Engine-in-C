#include "include/shaders.h"
#include <stdio.h>


// Reads the content of the files in the vertexPath and fragmentPath then compiles it and returns 1 upon success or 0 upon failure
int shadersFromFile(char* vertexPath, char* fragmentPath, GLuint *vertexShader, GLuint *fragmentShader)
{
	FILE *vertexFile, *fragmentFile;

	// Opening the files
	vertexFile = fopen(vertexPath, "r");
	if (vertexFile == NULL) {
		return 0;
	}
	fragmentFile = fopen(fragmentPath, "r");
	if (fragmentFile == NULL) {
		fclose(vertexFile);
		return 0;
	}
	
	// Reading the files
	char vertexCode[100], fragmentCode[100];
	char* ch = vertexCode;
	while(1) {
		*ch = fgetc(vertexFile);
		if ((*ch) == EOF) {
			break;
		}
		ch++;
	};


	ch = fragmentCode;
	while(1) {
		*ch = fgetc(fragmentFile);
		if ((*ch) == EOF) {
			break;
		}
		ch++;
	};

	
	// Create the vertex shader
	if (!createVertexShader(vertexShader, vertexCode)) {
		fclose(fragmentFile); 
		return 0;
	}
	
	// Create the fragment shader
	if (!createFragmentShader(fragmentShader, fragmentCode)) {
		fclose(vertexFile);
		fclose(fragmentFile);
		return 0;
	}


	// Close the files
	fclose(vertexFile);
	fclose(fragmentFile); 
	return 1;
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

