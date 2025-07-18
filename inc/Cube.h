#pragma once

#include <glm/glm.hpp>
#include <glad.h>
#include <array>
#include <vector>

class CubeManager {

public:

	CubeManager();
	~CubeManager();

	void AddCube(float width);
	int Render();

private:

	struct CubeVertex {
		glm::vec3 position;
		glm::vec3 color;
	};

	struct Cube {
		CubeVertex frontTopLeft = {glm::vec3(0.0f), glm::vec3(1.0f)};
		CubeVertex frontTopRight = { glm::vec3(0.0f), glm::vec3(1.0f) };
		CubeVertex frontBottomLeft = { glm::vec3(0.0f), glm::vec3(1.0f) };
		CubeVertex frontBottomRight = { glm::vec3(0.0f), glm::vec3(1.0f) };

		CubeVertex backTopLeft = { glm::vec3(0.0f), glm::vec3(1.0f) };
		CubeVertex backTopRight = { glm::vec3(0.0f), glm::vec3(1.0f) };
		CubeVertex backBottomLeft = { glm::vec3(0.0f), glm::vec3(1.0f) };
		CubeVertex backBottomRight = { glm::vec3(0.0f), glm::vec3(1.0f) };
	};

	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_EBO = 0;

	//std::vector<Cube> m_vertices;
	//std::vector<GLuint> m_indices;

	std::array < glm::vec3, 72 > m_vertices = { glm::vec3(0.0f) };

	unsigned int m_numCubes = 0;

};