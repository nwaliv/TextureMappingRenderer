#version 330 core

// Outputs colors
out vec4 FragColor;

// Imports the current Position from the Vertex Shader
in vec3 crntPos;
// Imports the normal from the Vertex Shader
in vec3 Normal;
// Imports the color from the Vertex Shader
in vec3 color;
// Imports the texture coordinates from the Vertex Shader
in vec2 texCoord;

// Imports the light position, camera position and current position in tangent space from the Vertex Shader
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;


// Gets the Texture type from a mesh object
uniform sampler2D diffuseMap;
uniform sampler2D normalMap;
uniform sampler2D displacementMap;
uniform sampler2D specularMap;
// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

void main()
{
	// Ambient lighting variable
	float ambient = 0.2f;
	
	// To turn off normal mapping, use the previous viewDirection instead
	//vec3 viewDirection = normalize(camPos - crntPos);
	vec3 viewDirection = normalize(TangentViewPos - TangentFragPos);
	
	// Parallax Mapping----------------------------------------------------

	// Variables that control parallax occlusion mapping quality
	float heightScale = 0.2f;
	const float numLayers = 30.0f;

	float layerDepth = 1.0f / numLayers;
	float currentLayerDepth = 0.0f;

	// The amount to shift texture coordinates per layer from vector P
	vec2 P = viewDirection.xy / viewDirection.z * heightScale;
	vec2 deltaTexCoords = P / numLayers;

	// get initial values
	vec2 currentTexCoords = texCoord;
	float currentDepthMapValue = texture(displacementMap, currentTexCoords).r;

	//Loop until the point on the depthmap is "hit"
	while (currentLayerDepth < currentDepthMapValue) {
	// shift texture coordinates along direction of P
		currentTexCoords -= deltaTexCoords;
		// get depthmap value at current texture coordinates
		currentDepthMapValue = texture(displacementMap, currentTexCoords).r;
		// get depth of next layer;
		currentLayerDepth += layerDepth;
	}
	
	// Interpolation section - applying occlusion

	//	Get texture coordinates before collision
	vec2 prevTexCoords = currentTexCoords + deltaTexCoords;
	//	Get depth before and after collision for linear interpolation
	float afterDepth = currentDepthMapValue - currentLayerDepth;
	float beforeDepth = texture(displacementMap, prevTexCoords).r - currentLayerDepth + layerDepth;
	// interpolation of texture coordinates
	float weight = afterDepth / (afterDepth - beforeDepth);
	vec2 finalTexCoords = prevTexCoords * weight + currentTexCoords * (1.0f - weight);
	
	// Diffuse lighting ------------------------------------------------------------------------
	vec3 normal = normalize(Normal);

	// obtain normal from normal map in range [0,1] - Comment out these two statements to turn off normal mapping
	normal = texture(normalMap, finalTexCoords).rgb;
	// transform normal to range [-1,1]
	normal = normalize(normal * 2.0 - 1.0);

	// Use the other lightDirection to turn off normal mapping
	//vec3 lightDirection = normalize(lightPos - crntPos);
	vec3 lightDirection = normalize(TangentLightPos - TangentFragPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	// Specular lighting ------------------------------------------------------
	float specularLight = 0.20f;
	
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 128);
	float specular = specAmount * specularLight;

	// outputs final color - Use texCoord here instead of finalTexCoords to turn off Parallax Occlusion Mapping
	FragColor = texture(diffuseMap, finalTexCoords)* vec4(color, 1.0f) * lightColor * (diffuse + ambient) + texture(specularMap, finalTexCoords).r * specular;
}