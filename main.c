// A simple OpenGL app that displays a triangle using GLFW for windowing
#include "include/glad/glad.h"
#include <GLFW/glfw3.h>
#include "include/gl_basics.h"
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

	
	// 
	unsigned int VAO;
    	// Creating a vertex buffer object (Which is how we store the vertex data in the gpu)
    	unsigned int VBO;
	//initializeBuffers(&VAO, &VBO, vertices, GL_ARRAY_BUFFER);
	//////////
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
    	const char *vertexShaderSource = "#version 330 core\n"
    	"in vec3 vp;\n"
    	"void main()\n"
    	"{\n"
    	"   gl_Position = vec4(vp, 1.0);\n"
    	"}\0";
    
    	// This is the shader object
    	unsigned int vertexShader;
	// this function will create the shader object and compile the source into it returning 1 upon success and 0 upon failure
	if (!createVertexShader(&vertexShader, vertexShaderSource)) {
			printf("Vertex shader compilation error!\n");
			glfwTerminate();
			return 1;
	}

    	// Fragment shader
    	const char *fragmentShaderSource = "#version 330 core\n"
    	"out vec4 FragColor;\n"
    	"void main()\n"
    	"{\n"
    	"   FragColor = vec4(0.0f, 0.5f, 1.0f, 1.0f);\n"
    	"}\0";
    
	unsigned int fragmentShader;
    	if (!createFragmentShader(&fragmentShader, fragmentShaderSource)) {
		printf("Fragment shader compilation error!\n");
		glDeleteShader(vertexShader);
	    	glfwTerminate();
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
		glDrawArrays(GL_TRIANGLES, 0, 3);

        	// RENDERING
        	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


        	// This function takes the input from the user like keyboard and mouse
        	glfwPollEvents();

        	// EVENTS AND BUFFER
        	// From what I understand OpenGL has 2 viewport buffers one that it won't edit because it's being diplayed
        	// and the other one is being rendered to. We need to call this function to update what it's showing
        	glfwSwapBuffers(window);
    	}

    	glfwTerminate();
    	return 0;
}




// This function will get called every frame to allow us to get the user input and know if the user wants to close the window by pressing escape
void processInput(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        	glfwSetWindowShouldClose(window, true);
}
