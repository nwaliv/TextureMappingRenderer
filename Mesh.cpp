#include "Mesh.h"

Mesh::Mesh(std::vector <Vertex>& vertices, std::vector <GLuint>& indices, std::vector <Texture>& textures)
{
	Mesh::vertices = vertices;
	Mesh::indices = indices;
	Mesh::textures = textures;

	// Bind the VAO first to allow access to the VBO and EBO
	VAO.Bind();
	// Generates Vertex Buffer Object and links it to vertices
	VBO VBO(vertices);
	// Generates Element Buffer Object and links it to indices
	EBO EBO(indices);
	// Links VBO attributes such as coordinates and color to VAO
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0); // coordinates
	VAO.LinkAttrib(VBO, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float))); // normal vector
	VAO.LinkAttrib(VBO, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float))); // color
	VAO.LinkAttrib(VBO, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float))); // tex coordinates
	VAO.LinkAttrib(VBO, 4, 3, GL_FLOAT, sizeof(Vertex), (void*)(11 * sizeof(float))); // tangent vector
	VAO.LinkAttrib(VBO, 5, 3, GL_FLOAT, sizeof(Vertex), (void*)(14 * sizeof(float))); // bitangent vector

	// Unbind the VAO, VBO and EBO to prevent any further modification
	VAO.Unbind();
	VBO.Unbind();
	EBO.Unbind();
}


void Mesh::Draw(Shader& shader, Camera& camera)
{
	// Bind shader to be able to access uniforms
	shader.Activate();
	// VAO is binded to enable drawing of vertices
	VAO.Bind();

	// Load each mesh texture, assigns a texture unit to them each and bind them
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		std::string type = textures[i].type;
		textures[i].texUnit(shader, type.c_str(), i);
		textures[i].Bind();
	}
	// Exporting the camera position to the shader - camMatrix is used for translating coordinates to camera space
	glUniform3f(glGetUniformLocation(shader.ID, "camPos"), camera.Position.x, camera.Position.y, camera.Position.z);
	camera.Matrix(shader, "camMatrix");

	// Draw the mesh of the object
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}