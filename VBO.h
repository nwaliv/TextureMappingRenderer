#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

// The VBO (Vertex Buffer Object) stores vertex information in memory
struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

