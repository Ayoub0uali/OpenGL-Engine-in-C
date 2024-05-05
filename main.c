// A simple OpenGL app that displays a triangle using GLFW for windowing
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "include/gl_basics.h"
#include "include/shaders.h"
#include "include/geometry.h"
//#include <KHR/khrplatform.h>
#include <stdio.h>
#include <stdbool.h>


// Width of the window
#define WIDTH 800
// Height of the window
#define HEIGHT 600


void processInput(GLFWwindow *window);


int main()
{	
    	//////// INITIALIZATION
	// this function performs all the necessary initialization and creates a window that is linked to the opengl viewport
	GLFWwindow* window;
	if (!initializeGL(&window, WIDTH, HEIGHT, "Triangle")) {
		printf("Error initializing\n");
		glfwTerminate();
		return 0;
	}


    	///////// CREATE A TRIANGLE
    	// The vertices (the geometry in general)
    	float vertices[] = {
    		-0.5f, -0.5f, 0.0f,
     		0.5f, -0.5f, 0.0f,
     		0.0f,  0.5f, 0.0f
    	};

	
    	// Creating a vertex buffer object VBO (Which is how we store the vertex data to send it to the GPU)
	// and VAO is a vertex array buffer object which is an array of VBOs which makes accessing and treating them easier
    	GLuint VAO, VBO;
	//initializeBuffers(&VAO, &VBO, vertices, GL_ARRAY_BUFFER);
	
	glGenVertexArrays(1, &VAO);
    	glBindVertexArray(VAO); 


    	glGenBuffers(1, &VBO); // 1 because we only need 1 buffer and vbo is the id of this buffer
	
    	// We need to bind this new buffer to GL_ARRAY_BUFFER to define it's type
    	glBindBuffer(GL_ARRAY_BUFFER, VBO);

    	// This function copies the user defined memory (VBO) into the bound buffer (GL_ARRAY_BUFFER)
    	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // the 'usage' is GL_STATIC_DRAW because the triangle won't move
	

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
    	//////// SHADERS
    	// OpenGL requires a vertex shader and fragment shader in order to render geometry
    	// Vertex shader
    	// This shader is responsible for positioning the vertices on screen it has to be compiled at runtime so i'm putting it in a constant but it could be a file
    	// This is the shader object
    	unsigned int vertexShader;
	unsigned int fragmentShader;

	// This function will load the shader code from the files, compile it then put it in a shader object
    	if (!shadersFromFile("../resources/shader.vert", "../resources/shader.frag", &vertexShader, &fragmentShader)) {
		printf("Shader loading error!\n");
	    	glfwTerminate();
		glfwDestroyWindow(window);
	    	return 1;
    	}


    	///////////// SHADER PROGRAM
    	unsigned int shaderProgram;
    	if(!createShaderProgram(&shaderProgram, vertexShader, fragmentShader)) {
    		printf("Error linking the shader program\n");
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glfwTerminate();
		return 1;
    	}

    	// Deleting the shaders because they're now in the shader program and are no longer needed
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);


    	//////// MAIN LOOP
    	while(!glfwWindowShouldClose(window))
    	{
        	glClear(GL_COLOR_BUFFER_BIT);

        	// INPUT
        	processInput(window);
		
		// Geometry
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Triangles is the type of primitives we're using
		glDrawArrays(GL_TRIANGLES, 0, 3);

        	// RENDERING
        	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


        	// This function takes the input from the user like keyboard and mouse
        	glfwPollEvents();

        	// From what I understand OpenGL has 2 viewport buffers one that it won't edit because it's being displayed
        	// and the other one is being rendered to. We need to call this function to swap them and show what was drawn
        	glfwSwapBuffers(window);
    	}
	
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
    	glfwTerminate();
    	return 0;
}




// This function will get called every frame to allow us to get the user input and know if the user wants to close the window by pressing escape
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);
}
