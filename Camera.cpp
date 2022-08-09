#include"Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	Orientation = glm::vec3(-glm::sin(yaw) * glm::cos(pitch), 
							glm::sin(pitch), 
							-glm::cos(pitch) * glm::cos(yaw));

	Right = glm::vec3(glm::cos(yaw), 0.0f, -glm::sin(yaw));
	Up = glm::cross(Right, Orientation);
	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform) {
	// Exports the camera matrix to the Vertex Shader
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

void Camera::Inputs(SDL_Window* window, Lights& lights) {
	Uint8* keystate = const_cast <Uint8*> (SDL_GetKeyboardState(NULL));
	if (keystate[SDL_SCANCODE_W]) {
		Position += speed * Up;
	}

	if (keystate[SDL_SCANCODE_S]) {
		Position += speed * -Up;
	}

	if (keystate[SDL_SCANCODE_A]) {
		Position += speed * -Right;
	}

	if (keystate[SDL_SCANCODE_D]) {
		Position += speed * Right;
	}

	if (keystate[SDL_SCANCODE_SPACE]) {
		Position += speed * Orientation;
	}

	if (keystate[SDL_SCANCODE_LCTRL]) {
		Position += speed * -Orientation;
	}

	if (keystate[SDL_SCANCODE_L]) {
		yaw -= 0.0001f;
	}

	if (keystate[SDL_SCANCODE_J]) {
		yaw += 0.0001f;
	}

	if (keystate[SDL_SCANCODE_I]) {
		pitch += 0.0001f;
	}

	if (keystate[SDL_SCANCODE_K]) {
		pitch -= 0.0001f;
	}

	if (keystate[SDL_SCANCODE_UP]) {
		lights.Position += speed * Up;
	}

	if (keystate[SDL_SCANCODE_DOWN]) {
		lights.Position += speed * -Up;
	}

	if (keystate[SDL_SCANCODE_LEFT]) {
		lights.Position += speed * -Right;
	}

	if (keystate[SDL_SCANCODE_RIGHT]) {
		lights.Position += speed * Right;
	}

	if (keystate[SDL_SCANCODE_9]) {
		lights.Position += speed * -Orientation;
	}

	if (keystate[SDL_SCANCODE_0]) {
		lights.Position += speed * Orientation;
	}
}

void Camera::cameraInfo() {
	std::cout << "Camera Information" << std::endl;
	std::cout << "Position: " << Position.x << " " << Position.y << " " << Position.z << std::endl;
}