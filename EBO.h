#pragma once

#include <glad/glad.h>
#include <vector>

// The EBO (Element Buffer Object) stores an array of indices(each assigned to a vertex) in memory

class EBO
{
public:
	// ID reference of Elements Buffer Object
	GLuint ID;
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint>& indices);

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();
	// Deletes the EBO
	void Delete();
};