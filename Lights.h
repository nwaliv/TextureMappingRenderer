#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shaderClass.h"
class Lights
{

	
public:
	glm::vec3 Position;
	// Constuctor that stores the position of the lights
	Lights(glm::vec3 position);
	// Exports the light position to a shader doing light calculations - used with shaderProgram
	void exportPosition(Shader& shader, const char* uniform);
	// Updates the light position matrix within a shader - used only with lightShader
	void updateLightModel(Shader& shader, const char* uniform);

};

