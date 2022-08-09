#pragma once

#include<glad/glad.h>
#include"VBO.h"

// The VAO (Vertex Array Object) stores an array of attribute pointers in memory 
//	that link to vertex information in the VBO by a certain layout. 
// The layout specifies the arrangement of attrib pointers in the VAO

class VAO
{
public:
	// ID reference for the Vertex Array Object
	GLuint ID;
	// Constructor that generates a VAO ID
	VAO();

	// Links a VBO to the VAO using a certain layout
	void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
	// Binds the VAO
	void Bind();
	// Unbinds the VAO
	void Unbind();
	// Deletes the VAO
	void Delete();
};