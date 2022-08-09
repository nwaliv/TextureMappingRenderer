#include "Models.h"
void LoadFloorModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices) {
	
	// positions
	glm::vec3 pos1(-1.0f, 0.0f, 1.0f);
	glm::vec3 pos2(-1.0f, 0.0f, -1.0f);
	glm::vec3 pos3(1.0f, 0.0f, -1.0f);
	glm::vec3 pos4(1.0f, 0.0f, 1.0f);

	// tex coordinates
	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(0.0f, 1.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(1.0f, 0.0f);

	// normal vector
	glm::vec3 nm(0.0f, 1.0f, 0.0f);

	// calculating tangent/bitangent of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	vertices = {
		//Position// normal //		color	// texcoord // tangent// bitangent //
		Vertex{pos1, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv1, tangent1, bitangent1},
		Vertex{pos2, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv2, tangent1, bitangent1},
		Vertex{pos3, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv3, tangent1, bitangent1},

		Vertex{pos1, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv1, tangent2, bitangent2},
		Vertex{pos3, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv3, tangent2, bitangent2},
		Vertex{pos4, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv4, tangent2, bitangent2}
	};

	indices =
	{
		0, 1, 2,
		3, 4, 5
	};
}

void LoadVerticalPlaneModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices) {
	// positions
	glm::vec3 pos1(-1.0f, -1.0f, 0.0f);
	glm::vec3 pos2(1.0f, -1.0f, 0.0f);
	glm::vec3 pos3(1.0f, 1.0f, 0.0f);
	glm::vec3 pos4(-1.0f, 1.0f, 0.0f);

	// tex coordinates
	glm::vec2 uv1(0.0f, 0.0f);
	glm::vec2 uv2(0.0f, 1.0f);
	glm::vec2 uv3(1.0f, 1.0f);
	glm::vec2 uv4(1.0f, 0.0f);

	// normal vector
	glm::vec3 nm(0.0f, 0.0f, 1.0f);
	// calculating tangent/bitangent of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;

	// triangle 1
	// ----------
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;
	float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);

	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	// triangle 2
	// ----------
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;

	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);


	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);

	vertices = {
		//Position// normal //		color	// texcoord // tangent// bitangent //
		Vertex{pos1, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv1, tangent1, bitangent1},
		Vertex{pos2, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv2, tangent1, bitangent1},
		Vertex{pos3, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv3, tangent1, bitangent1},

		Vertex{pos1, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv1, tangent2, bitangent2},
		Vertex{pos3, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv3, tangent2, bitangent2},
		Vertex{pos4, nm, glm::vec3(1.0f, 1.0f, 1.0f), uv4, tangent2, bitangent2}
	};

	indices =
	{
		0, 1, 2,
		3, 4, 5
	};
}

void LoadLightModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices) {
	vertices =
	{ //     COORDINATES     //
		Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
		Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
		Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
	};

	indices =
	{
		0, 1, 2,
		0, 2, 3,
		0, 4, 7,
		0, 7, 3,
		3, 7, 6,
		3, 6, 2,
		2, 6, 5,
		2, 5, 1,
		1, 5, 4,
		1, 4, 0,
		4, 5, 6,
		4, 6, 7
	};

}

void LoadWoodTexture(std::vector <Texture>& textures) {
	textures = {
		Texture("wooden_deck_boards_texture_texturise_DIFFUSE.jpg", "diffuseMap", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("wooden_deck_boards_texture_texturise_NORMAL.jpg", "normalMap", 1, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("wooden_deck_boards_texture_texturise_DISP.jpg", "displacementMap", 2, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("wooden_deck_boards_texture_texturise_SPECULAR.jpg", "specularMap", 3, GL_RED, GL_UNSIGNED_BYTE)
	};
}

void LoadMetalTexture(std::vector <Texture>& textures) {
	textures = {
		Texture("Seamless_Metal_Plate_Texture.jpg", "diffuseMap", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Seamless_Metal_Plate_Texture_NORMAL.jpg", "normalMap", 1, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Seamless_Metal_Plate_Texture_DISP.jpg", "displacementMap", 2, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Seamless_Metal_Plate_Texture_SPECULAR.jpg", "specularMap", 3, GL_RED, GL_UNSIGNED_BYTE)
	};
}

void LoadMosaicTexture(std::vector <Texture>& textures) {
	textures = {
		Texture("Tileable_Blue_Mosaic_Pool_Tiles_Texture.jpg", "diffuseMap", 0, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Tileable_Blue_Mosaic_Pool_Tiles_Texture_NORMAL.jpg", "normalMap", 1, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Tileable_Blue_Mosaic_Pool_Tiles_Texture_DISP.jpg", "displacementMap", 2, GL_RGB, GL_UNSIGNED_BYTE),
		Texture("Tileable_Blue_Mosaic_Pool_Tiles_Texture_SPECULAR.jpg", "specularMap", 3, GL_RED, GL_UNSIGNED_BYTE)
	};
}