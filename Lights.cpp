#include "Lights.h"

Lights::Lights(glm::vec3 position) {
	Position = position;
}

void Lights::exportPosition(Shader& shader, const char* uniform) {
	glUniform3f(glGetUniformLocation(shader.ID, uniform), Position.x, Position.y, Position.z);
}

void Lights::updateLightModel(Shader& shader, const char* uniform) {
	glm::mat4 lightMatrix = glm::mat4(1.0f);
	lightMatrix = glm::translate(lightMatrix, Position);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(lightMatrix));
}