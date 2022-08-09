#pragma once
#include <vector>
#include "Mesh.h"
#include "Texture.h"

// Loads a horizontal plane
void LoadFloorModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

// Loads a vertical plane
void LoadVerticalPlaneModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

// Loads a general light model into the renderer
void LoadLightModel(std::vector <Vertex>& vertices, std::vector <GLuint>& indices);

void LoadWoodTexture(std::vector <Texture>& textures);

void LoadMetalTexture(std::vector <Texture>& textures);

void LoadMosaicTexture(std::vector <Texture>& textures);