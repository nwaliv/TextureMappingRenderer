#pragma once

#include <glad/glad.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "shaderClass.h"
#include "Lights.h"

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	// Angles for x and y rotation

	float yaw = 0.0f;
	float pitch = 0.0f;

	// Stores the width and height of the window

	int width;
	int height;

	// Adjust the speed of the camera
	float speed = 0.001f;

	// Camera constructor to set up initial values
	Camera(int width, int height, glm::vec3 position);

	// Updates the camera matrix
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	// Updates camera and lights position and orientation on user input
	void Inputs(SDL_Window* window, Lights& lights);

	// Outputs camera position to console -for debugging
	void cameraInfo();
};
