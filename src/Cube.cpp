#include "Cube.h"
#include <glad.h>
#include <iostream>

float rf(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

CubeManager::CubeManager() {

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//glGenBuffers(1, &m_EBO);


	//m_indices.resize(1 * 36);

	//
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

CubeManager::~CubeManager() {

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
	//glDeleteBuffers(1, &m_EBO);

}

void CubeManager::AddCube(float width)
{
	const float sz = width / 2.0f;
	m_vertices = {
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),

		glm::vec3(-sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
									   
		glm::vec3(-sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
									   
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
									    
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz, -sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
									   
		glm::vec3(-sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3( sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz,  sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
		glm::vec3(-sz,  sz, -sz), glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	};
























	//m_vertices = {
	//	// front face
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	//top face
	//	glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	// back face
	//	glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	// bottom face
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	// left face
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f, -0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	//right face
	//	glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f,  0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f)),
	//	glm::vec3(-0.5f,  0.5f, -0.5f),		glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f))
	//};




















































	//static constexpr unsigned int sizeCube = sizeof(Cube) / sizeof(CubeVertex);
	//const float halfSize = width / 2.0f;

	//m_vertices[m_numCubes].frontTopLeft.position = glm::vec3(-halfSize, halfSize, -halfSize);
	//m_vertices[m_numCubes].frontTopLeft.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].frontBottomLeft.position = glm::vec3(-halfSize, -halfSize, -halfSize);
	//m_vertices[m_numCubes].frontBottomLeft.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].frontTopRight.position = glm::vec3(halfSize, halfSize, -halfSize);
	//m_vertices[m_numCubes].frontTopRight.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].frontBottomRight.position = glm::vec3(halfSize, -halfSize, -halfSize);
	//m_vertices[m_numCubes].frontBottomRight.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].backTopLeft.position = glm::vec3(-halfSize, halfSize, halfSize);
	//m_vertices[m_numCubes].backTopLeft.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].backBottomLeft.position = glm::vec3(-halfSize, -halfSize, halfSize);
	//m_vertices[m_numCubes].backBottomLeft.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].backTopRight.position = glm::vec3(halfSize, halfSize, halfSize);
	//m_vertices[m_numCubes].backTopRight.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));
	//m_vertices[m_numCubes].backBottomRight.position = glm::vec3(halfSize, -halfSize, halfSize);
	//m_vertices[m_numCubes].backBottomRight.color = glm::vec3(rf(0.0f, 1.0f), rf(0.0f, 1.0f), rf(0.0f, 1.0f));

	////////////////////////////////////////////////////////////////////////////////////////////////////////


	//// Triangle 1 - Top left -> top right -> bottom left
	//m_indices[(m_numCubes * 6) + 0] = (m_numCubes * sizeRect) + 0;
	//m_indices[(m_numCubes * 6) + 1] = (m_numCubes * sizeRect) + 2;
	//m_indices[(m_numCubes * 6) + 2] = (m_numCubes * sizeRect) + 4;

	//// Triangle 2 - Bottom left -> Bottom right -> Top right
	//m_indices[(m_numCubes * 6) + 3] = (m_numCubes * sizeRect) + 4;
	//m_indices[(m_numCubes * 6) + 4] = (m_numCubes * sizeRect) + 6;
	//m_indices[(m_numCubes * 6) + 5] = (m_numCubes * sizeRect) + 2;

	//m_numRectangles++;

	//return m_numRectangles - 1;
}

int CubeManager::Render()
{

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), &m_vertices[0], GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return 0;
}