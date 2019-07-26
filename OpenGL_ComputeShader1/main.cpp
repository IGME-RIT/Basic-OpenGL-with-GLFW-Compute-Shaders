/*
Title: Compute Shaders
File Name: main.cpp
Copyright � 2016
Author: David Erbelding
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.

This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/



#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "shape.h"
#include "shader.h"
#include <iostream>

Shape* square;

// Shaders.
Shader vertexShader;
Shader fragmentShader;
Shader computeShader;

// GL index for the shader program
GLuint shaderProgram;
GLuint computeProgram;


// Window resize callback
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}




int main(int argc, char **argv)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	// Initializes the GLFW library
	glfwInit();

	// Initialize window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Compute Shaders", nullptr, nullptr);

	glfwMakeContextCurrent(window);

	//set resize callback
	glfwSetFramebufferSizeCallback(window, resizeCallback);

	// Initializes the glew library
	glewInit();


	// Indices for square (-1, -1)[2] to (1, 1)[1]
	// [0]------[1]
	//	|		 |
	//	|		 |
	//	|		 |
	// [2]------[3]

	// Create square vertex data.
	std::vector<Vertex2dColor> vertices;
	vertices.push_back(Vertex2dColor(glm::vec4(-.5, .5, 0, 1), glm::vec4(.5, .5, .5, 1)));
	vertices.push_back(Vertex2dColor(glm::vec4(.5, .5, 0, 1), glm::vec4(.5, .5, .5, 1)));
	vertices.push_back(Vertex2dColor(glm::vec4(-.5, -.5, 0, 1), glm::vec4(.5, .5, .5, 1)));
	vertices.push_back(Vertex2dColor(glm::vec4(.5, -.5, 0, 1), glm::vec4(.5, .5, .5, 1)));
    // Index data.
	std::vector<unsigned int> indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(3);
	indices.push_back(2);
	indices.push_back(1);


	// Create shape object with that info.
	square = new Shape(vertices, indices);


    ///////////////////////////
	// Drawing Shader Setup //
    /////////////////////////

	// Initialize the shaders from file.
	vertexShader.InitFromFile("../Assets/vertex.glsl", GL_VERTEX_SHADER);
	fragmentShader.InitFromFile("../Assets/fragment.glsl", GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();

	// Attach shaders and link program.
	vertexShader.AttachTo(shaderProgram);
	fragmentShader.AttachTo(shaderProgram);
	glLinkProgram(shaderProgram);


    ///////////////////////////
    // Compute Shader Setup //
    /////////////////////////

    // Load the compute shader, and make a shader program from it.
    computeShader.InitFromFile("../Assets/compute.glsl", GL_COMPUTE_SHADER);
    computeProgram = glCreateProgram();
    computeShader.AttachTo(computeProgram);
    glLinkProgram(computeProgram);

    // Note: If there is a compute shader attached to a program, OpenGL won't let you link with any other types of attached shaders.


	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
        // Calculate delta time.
        float dt = glfwGetTime();
        // Reset the timer.
        glfwSetTime(0);

		// Clear the screen.
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.0, 0.0, 0.0, 0.0);

        // COMPUTE

        // First, we need to bind the data we want to process to GL_SHADER_STORAGE_BUFFER
        // 0 is the buffer binding location (declared in the shader with layout(binding = 0))
        // We are binding the vertex buffer from our square.
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, square->m_vertexBuffer);
        // Same as with drawing, but we bind a compute shader program instead.
        glUseProgram(computeProgram);
        // Set the uniform at location 0 to delta time.
        glUniform1f(0, dt);
        // Tell the compute shader to run once for each vertex in the buffer.
        glDispatchCompute(vertices.size(), 1, 1);



        // DRAW

		// Set the current shader program.
		glUseProgram(shaderProgram);
		// The Draw the square
		square->Draw();
		// Stop using the shader program.
		glUseProgram(0);



		// Swap the backbuffer to the front.
		glfwSwapBuffers(window);

		// Poll input and window events.
		glfwPollEvents();

	}

	// Free memory from shader program and individual shaders
	glDeleteProgram(shaderProgram);
    glDeleteProgram(computeProgram);

	// Free memory from shape object
	delete square;

	// Free GLFW memory.
	glfwTerminate();


	// End of Program.
	return 0;
}
