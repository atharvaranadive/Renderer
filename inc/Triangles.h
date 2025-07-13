#pragma once

#include <vector>
#include <array>

struct Triangle {
	float vertex1[3];
	float color1[3];
	float vertex2[3];
	float color2[3];
	float vertex3[3];
	float color3[3];
};

class Triangles {

public:

	Triangles();
	~Triangles();

	bool AddTriangle(Triangle& tri);

	bool Render();

//private:
	unsigned int m_VBO = 0;
	unsigned int m_VAO = 0;

	std::vector<Triangle> m_vertices;

	size_t m_numTriangles = 0;

	//std::array<Triangle,1> m_vertices;
};