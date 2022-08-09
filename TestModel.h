#ifndef TEST_MODEL_CORNEL_BOX_H
#define TEST_MODEL_CORNEL_BOX_H
// File was taken from the previous DH2323 Rendering Labs and modified
// 
// Defines a simple test model: The Cornel Box
#include <glm/glm.hpp>
#include <vector>

// Used to describe a triangular surface:
class Triangle
{
public:
	glm::vec3 v0;
	glm::vec3 v1;
	glm::vec3 v2;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 uv0;
	glm::vec2 uv1;
	glm::vec2 uv2;
	glm::vec3 tangent;
	glm::vec3 bitangent;
	Triangle( glm::vec3 v0, glm::vec3 v1, glm::vec3 v2, glm::vec3 color, glm::vec2 uv0, glm::vec2 uv1, glm::vec2 uv2 )
		: v0(v0), v1(v1), v2(v2), color(color), uv0(uv0), uv1(uv1), uv2(uv2)
	{
		ComputeTBN();
	}

	void ComputeTBN()
	{
		glm::vec3 e1 = v1-v0;
		glm::vec3 e2 = v2-v0;
		normal = -glm::normalize( glm::cross( e2, e1 ) );

		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;
		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent.x = f * (deltaUV2.y * e1.x - deltaUV1.y * e2.x);
		tangent.y = f * (deltaUV2.y * e1.y - deltaUV1.y * e2.y);
		tangent.z = f * (deltaUV2.y * e1.z - deltaUV1.y * e2.z);

		bitangent.x = f * (-deltaUV2.x * e1.x + deltaUV1.x * e2.x);
		bitangent.y = f * (-deltaUV2.x * e1.y + deltaUV1.x * e2.y);
		bitangent.z = f * (-deltaUV2.x * e1.z + deltaUV1.x * e2.z);
	}
};

// Loads the Cornell Box. It is scaled to fill the volume:
// -1 <= x <= +1
// -1 <= y <= +1
// -1 <= z <= +1
void LoadTestModel( std::vector<Triangle>& triangles )
{
	using glm::vec2;
	using glm::vec3;

	// Defines colors:
	vec3 red(    0.75f, 0.15f, 0.15f );
	vec3 yellow( 0.75f, 0.75f, 0.15f );
	vec3 green(  0.15f, 0.75f, 0.15f );
	vec3 cyan(   0.15f, 0.75f, 0.75f );
	vec3 blue(   0.15f, 0.15f, 0.75f );
	vec3 purple( 0.75f, 0.15f, 0.75f );
	vec3 white(  0.75f, 0.75f, 0.75f );

	triangles.clear();
	triangles.reserve( 5*2*3 );

	// ---------------------------------------------------------------------------
	// Room

	float L = 555;			// Length of Cornell Box side.

	vec3 A(L,0,0);
	vec3 B(0,0,0);
	vec3 C(L,0,L);
	vec3 D(0,0,L);

	vec3 E(L,L,0);
	vec3 F(0,L,0);
	vec3 G(L,L,L);
	vec3 H(0,L,L);

	// tex coordinates
	vec2 a(0.0f, 0.0f);
	vec2 b(1.0f, 0.0f);
	vec2 c(0.0f, 1.0f);
	vec2 d(1.0f, 1.0f);

	// Floor:
	triangles.push_back( Triangle( C, B, A, green, c, b, a) );
	triangles.push_back( Triangle( C, D, B, green, c, d, b) );

	// Left wall
	triangles.push_back( Triangle( A, E, C, purple, a, c, b) );
	triangles.push_back( Triangle( C, E, G, purple, b, c, d) );

	// Right wall
	triangles.push_back( Triangle( F, B, D, yellow , d, b, a) );
	triangles.push_back( Triangle( H, F, D, yellow, c, d, a) );

	// Ceiling
	triangles.push_back( Triangle( E, F, G, cyan, a, b, c) );
	triangles.push_back( Triangle( F, H, G, cyan, b, d, c) );

	// Back wall
	triangles.push_back( Triangle( G, D, C, white, c, b, a) );
	triangles.push_back( Triangle( G, H, D, white, c, d, b) );

	// ---------------------------------------------------------------------------
	// Short block

	A = vec3(290,0,114);
	B = vec3(130,0, 65);
	C = vec3(240,0,272);
	D = vec3( 82,0,225);

	E = vec3(290,165,114);
	F = vec3(130,165, 65);
	G = vec3(240,165,272);
	H = vec3( 82,165,225);

	// Front
	triangles.push_back( Triangle(E,B,A,red, c, b, a) );
	triangles.push_back( Triangle(E,F,B,red, c, d, b) );

	// Front (Right)
	triangles.push_back( Triangle(F,D,B,red, c, b,a) );
	triangles.push_back( Triangle(F,H,D,red, c, d, b) );

	// BACK
	triangles.push_back( Triangle(H,C,D,red, c, b, a) );
	triangles.push_back( Triangle(H,G,C,red, c, d, b) );

	// LEFT
	triangles.push_back( Triangle(G,E,C,red, c, d, a) );
	triangles.push_back( Triangle(E,A,C,red, d, b, a) );

	// TOP
	triangles.push_back( Triangle(G,F,E,red, c, b, a) );
	triangles.push_back( Triangle(G,H,F,red, c, d, b) );

	// ---------------------------------------------------------------------------
	// Tall block

	A = vec3(423,0,247);
	B = vec3(265,0,296);
	C = vec3(472,0,406);
	D = vec3(314,0,456);

	E = vec3(423,330,247);
	F = vec3(265,330,296);
	G = vec3(472,330,406);
	H = vec3(314,330,456);

	// Front
	triangles.push_back(Triangle(E, B, A, blue, c, b, a));
	triangles.push_back(Triangle(E, F, B, blue, c, d, b));

	// Front (Right)
	triangles.push_back(Triangle(F, D, B, blue, c, b, a));
	triangles.push_back(Triangle(F, H, D, blue, c, d, b));

	// BACK
	triangles.push_back(Triangle(H, C, D, blue, c, b, a));
	triangles.push_back(Triangle(H, G, C, blue, c, d, b));

	// LEFT
	triangles.push_back(Triangle(G, E, C, blue, c, d, a));
	triangles.push_back(Triangle(E, A, C, blue, d, b, a));

	// TOP
	triangles.push_back(Triangle(G, F, E, blue, c, b, a));
	triangles.push_back(Triangle(G, H, F, blue, c, d, b));


	// ----------------------------------------------
	// Scale to the volume [-1,1]^3

	for( size_t i=0; i<triangles.size(); ++i )
	{
		triangles[i].v0 *= 2/L;
		triangles[i].v1 *= 2/L;
		triangles[i].v2 *= 2/L;

		triangles[i].v0 -= vec3(1,1,1);
		triangles[i].v1 -= vec3(1,1,1);
		triangles[i].v2 -= vec3(1,1,1);

		triangles[i].v0.z *= -1;
		triangles[i].v1.z *= -1;
		triangles[i].v2.z *= -1;

		triangles[i].ComputeTBN();
	}
}

#endif