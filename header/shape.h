/*
Title: Compute Shaders
File Name: shape.h
Copyright ? 2016
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
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>


// Our vertices will now contain not just a position, but also a color!
// This struct will store all of this vertex data conveniently.
struct Vertex2dColor {

	glm::vec4 m_position;
	glm::vec4 m_color;

	// Makes a 2d vertex with color data.
	Vertex2dColor(glm::vec4 position, glm::vec4 color) {
		m_position = position;
		m_color = color;
	}
};

class Shape {


private:
	// Vectors of shape information
	std::vector<Vertex2dColor> m_vertices;
	std::vector<unsigned int> m_indices;

	// Buffered shape info


public:
	// Constructor for a shape, takes a vector for vertices and indices
	Shape(std::vector<Vertex2dColor> vertices, std::vector<unsigned int> indices);
	// Shape destructor to clean up buffers
	~Shape();

	// Draws the shape using a given world matrix
	void Draw();

    GLuint m_vertexBuffer;
    GLuint m_indexBuffer;
    GLuint m_vao;
};