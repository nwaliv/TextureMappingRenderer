#include "Models.h"
#include "TestModel.h"

// Global Variables

const unsigned int SCREEN_HEIGHT = 480;
const unsigned int SCREEN_WIDTH = 640;
SDL_Window* window = nullptr;
SDL_GLContext context = nullptr;
bool quit = false;

//Function Declarations

// Initialises SDL, OpenGL and GLAD
void InitialiseProgram();
// Polls for user input
void Input();

// Outputs Control Info for Camera, Lights, etc
void UserControlInfo();
int main(int argc, char *argv[]) {

	InitialiseProgram();

	// Generates Shader object using shaders default.vert and default.frag
	Shader shaderProgram("default.vert", "default.frag");
	
	// Store mesh data in vectors for the mesh
	
	// vertex data for a loaded model
	std::vector <Vertex> vertices;
	// numbers associated with the vertices, allows for vertex reuse when drawing to screen
	std::vector <GLuint> indices;
	// texture data
	std::vector <Texture> textures;
	int input;


	std::cout << "Current Models Available: Horizontal Plane - 1, Vertical Plane - 2, Cornell Box Model - 3" << std::endl;
	
	bool valid = false;
	

	while (!valid) {
		std::cout << "Please choose 1, 2, or 3 to load: " << std::endl;
		std::cin >> input;
		if (input == 1) { 
			LoadFloorModel(vertices, indices);
			std::cout << "Hoizontal Plane Selected" << std::endl;
			std::cout << "Note: The camera will need to be rotated to see the horizontal plane" << std::endl;
			valid = true;
		}
		if (input == 2) { 
			LoadVerticalPlaneModel(vertices, indices);
			std::cout << "Vertical Plane Selected" << std::endl;
			valid = true;
		}
		if (input == 3) {
			std::cout << "Cornell Box Model Selected" << std::endl;
			valid = true;
			std::vector <Triangle> triangles;
			LoadTestModel(triangles);
			vertices.clear();
			vertices.reserve(30 * 3);

			for (int i = 0; i < triangles.size(); ++i) {
				vertices.push_back(Vertex{ triangles[i].v0, triangles[i].normal, triangles[i].color, triangles[i].uv0, triangles[i].tangent, triangles[i].bitangent });
				vertices.push_back(Vertex{ triangles[i].v1, triangles[i].normal, triangles[i].color, triangles[i].uv1, triangles[i].tangent, triangles[i].bitangent });
				vertices.push_back(Vertex{ triangles[i].v2, triangles[i].normal, triangles[i].color, triangles[i].uv2, triangles[i].tangent, triangles[i].bitangent });
			}

			indices =
			{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
				31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60,
				61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
			};
		}
	}

	valid = false;
	std::cout << "Current Texture Packs Available: Wooden Deck Boards - 1,  Metal Plate - 2, Blue Mosaic Pool Tiles - 3" << std::endl;

	while (!valid) {
		std::cout << "Please choose 1, 2, or 3 to load: " << std::endl;
		std::cin >> input;
		if (input == 1) {
			LoadWoodTexture(textures);
			std::cout << "Wooden Deck Boards Texture Selected" << std::endl;

			valid = true;
		}
		if (input == 2) {
			LoadMetalTexture(textures);
			std::cout << "Metal Plate Texture Selected" << std::endl;

			valid = true;
		}
		if (input == 3) {
			LoadMosaicTexture(textures);
			std::cout << "Blue Mosaic Pool Tiles Selected" << std::endl;

			valid = true;
		}
	}


	// The loaded model to be rendered
	Mesh model(vertices, indices, textures);

	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");

	// Store mesh data in vectors for the mesh
	std::vector <Vertex> lightVertices;
	std::vector <GLuint> lightIndices;

	LoadLightModel(lightVertices, lightIndices);

	// The light model, textures is a placeholder and won't be rendered
	Mesh light(lightVertices, lightIndices, textures);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 1.5f);
	// Matrix containing the position of the light model
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	glm::vec3 objectPos = glm::vec3(0.0f, 0.0f, 0.0f);
	// Matrix containing the position of the object model
	glm::mat4 objectModel = glm::mat4(1.0f);
	objectModel = glm::translate(objectModel, objectPos);

	// Provide access for the Shaders to the object and light model position and color through uniform variables
	// Shaders must be activated before exporting uniforms to them
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	shaderProgram.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "model"), 1, GL_FALSE, glm::value_ptr(objectModel));
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the depth buffer
	glEnable(GL_DEPTH_TEST);

	// Storing the camera and light position to enable the change of positions by user

	Camera camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 75.0f));
	Lights lights(lightPos);

	UserControlInfo();
	while (!quit) {

		//Specify the color of the background
		glClearColor(0.02f, 0.f, 0.3f, 1.f);
		// Clean the back buffer and assign new color to it
		glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

		// Handles camera Inputs
		camera.Inputs(window, lights);
		lightShader.Activate();
		lights.updateLightModel(lightShader, "model");

		shaderProgram.Activate();
		lights.exportPosition(shaderProgram, "lightPos");

		camera.updateMatrix(90.0f,0.1f,200.0f);

		model.Draw(shaderProgram, camera);
		light.Draw(lightShader, camera);

		//Update the screen, swap the back buffer with the front buffer
		SDL_GL_SwapWindow(window);

		Input(); // Polling for Events
	}

	// Clean Up
	shaderProgram.Delete();
	lightShader.Delete();
	SDL_Quit();
	SDL_DestroyWindow(window);

	return 0;
}

void InitialiseProgram() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		std::cout << "SDL2 could not initialise video subsystem\n" << std::endl;
		exit(1);
	}
	// OpenGL 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	// Create an OpenGL graphics window
	window = SDL_CreateWindow("OpenGL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		std::cout << "SDLWindow was not able to be created\n" << std::endl;
		exit(1);
	}
	// Create an OpenGL graphics context
	context = SDL_GL_CreateContext(window);

	if (context == nullptr) {
		std::cout << "OpenGL context not created\n" << std::endl;
		exit(1);
	}

	// intialise the GLAD library
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) {
		std::cout << "GLAD was not initialised" << std::endl;
		exit(1);
	}
	// Specify the viewport of OpenGL in the window
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	std::cout << "Successful SDL2, GLAD and OpenGL Initilisation\n" << std::endl;
}


void Input() {
	SDL_Event e;
	while (SDL_PollEvent(&e) != 0) {
		if (e.type == SDL_QUIT) {
			std::cout << "\nTerminating Program... " << std::endl;
			quit = true;
		}
	}
}

void UserControlInfo() {
	std::cout << "Camera Controls:" << std::endl;
	std::cout << " Use the WASD keys to move the camera up, down left, and right." << std::endl;
	std::cout << " Use the IJKL keys to rotate the camera up, down left, and right." << std::endl;
	std::cout << " Use the SPACE key to move the camera forward, and the LCTRL key to move backward." << std::endl;
	std::cout << " \nLight Controls:" << std::endl;
	std::cout << " Use the arrow keys to move the light source up, down left, and right." << std::endl;
	std::cout << " Use the 0 key to move the light source forward, and the 9 key to move backward." << std::endl;
	std::cout << "\n Click the X button in the top right corner to terminate the program." << std::endl;
}