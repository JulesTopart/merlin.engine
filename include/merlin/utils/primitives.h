#pragma once
#include "merlin/graphics/mesh.h"

namespace Merlin {
	class Primitives {
	public:
		// Load a model from the specified file and return a pointer to a new Mesh object
		static shared<Mesh> createCircle(float r, int res = 20);
		static shared<Mesh> createOutlinedCircle(float r, int res = 20);
		static shared<Mesh> createRectangle(float x, float y);
		static shared<Mesh> createQuadRectangle(float x, float y, bool centered = true);
		static shared<Mesh> createFloor(const int groundNumTiles, const float groundTileSize);
		static shared<Mesh> createPoint();
		static shared<Mesh> createLine(float length, glm::vec3 dir = glm::vec3(1, 0, 0));
		static shared<Mesh> createCoordSystem();
		static shared<Mesh> createQuadCube(float w, bool centered = true);
		static shared<Mesh> createQuadCube(float x, float y, float z, bool centered = true);
		static shared<Mesh> createCube(float w);
		static shared<Mesh> createCube(float x, float y, float z);
		static shared<Mesh> createSphere(float r, int hres = 10, int vres = 10);
		static shared<Mesh> createFromQuad(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, GLuint mode = GL_TRIANGLES);
		static shared<Mesh> createCone(float r, float h, int res);
		static shared<Mesh> createCylinder(float r, float h, int res);

	};

}
