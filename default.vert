#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Normals (not normalised)
layout (location = 1) in vec3 aNormal;
// Colors
layout (location = 2) in vec3 aColor;
// Texture Coordinates
layout (location = 3) in vec2 aTex;
// Tangent (not normalised)
layout (location = 4) in vec3 aTangent;
// Bitangent (not normalised)
layout (location = 5) in vec3 aBitangent;

// Outputs the current position for the fragment shader
out vec3 crntPos;
// Outputs the Normal for the Fragment Shader
out vec3 Normal;
// Outputs the color for the Fragment Shader
out vec3 color;
// Outputs the texture coordinates to the fragment shader
out vec2 texCoord;

// Outputs the light position, camera position and current position in tangent space to the fragment shader
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

// Imports the camera matrix from the main function
uniform mat4 camMatrix;
// Imports the model matrix from the main function
uniform mat4 model;

void main()
{
	// Calculates current position (vertex is translated to world view)
	crntPos = vec3(model * vec4(aPos, 1.0f));
	// Assigns the normal from the vertex data to "normal"
	Normal = aNormal;
	// Assigns the colors from the Vertex Data to "color"
	color = aColor;
	// Assigns the texture coordinates from the Vertex Data to "texCoord"
	texCoord = aTex;

	vec3 T = normalize(vec3(model * vec4(aTangent, 0.0f)));
	vec3 B = normalize(vec3(model * vec4(aBitangent, 0.0f)));
	vec3 N = normalize(vec3(model * vec4(aNormal, 0.0f)));

	mat3 TBN = transpose(mat3(T, B, N));
	TangentLightPos = TBN * lightPos;
	TangentViewPos = TBN * camPos;
	TangentFragPos = TBN * vec3(model * vec4(aPos, 1.0f));

	// Outputs the positions/coordinates of all vertices
	gl_Position = camMatrix * vec4(crntPos, 1.0f);
}