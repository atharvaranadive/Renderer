#pragma once

#include <glm/glm.hpp>
#include <glad.h>
#include <vector>

class CubeManager {

public:

	CubeManager();
	~CubeManager();

	int AddCube(float x, float y, float width);
	int Render();

private:

	struct CubeVertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	struct Cube {
		CubeVertex vertices[8] = {glm::vec3(0.0f), glm::vec3(1.0f)};
	};

	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_EBO = 0;

	std::vector<Cube> m_vertices;
	std::vector<GLuint> m_indices;

	unsigned int m_numCubes = 0;

};