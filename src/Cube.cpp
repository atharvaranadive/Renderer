//#include "D:\Programs\Renderer\inc\Cube.h"
//#include "rectangles"
//#include <glad.h>
//#include <iostream>
//
//CubeManager::CubeManager() {
//
//	glGenVertexArrays(1, &m_VAO);
//	glGenBuffers(1, &m_VBO);
//	glGenBuffers(1, &m_EBO);
//
//	m_vertices.resize(1);
//	m_indices.resize(1 * 36);
//
//	glBindVertexArray(m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//
//	// position attribute
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	// color attribute
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindVertexArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//}
//
//CubeManager::~CubeManager() {
//
//	glDeleteVertexArrays(1, &m_VAO);
//	glDeleteBuffers(1, &m_VBO);
//	glDeleteBuffers(1, &m_EBO);
//
//}
//
//int CubeManager::AddRectangle(float x, float y, float width)
//{
//	if (m_numCubes == m_vertices.capacity()) {
//		m_vertices.resize(m_numCubes * 2);
//		m_indices.resize(m_numCubes * 2 * 36);
//	}
//
//	static constexpr unsigned int sizeRect = sizeof(Cube) / sizeof(glm::vec3);
//
//	m_vertices[m_numRectangles].topLeft = glm::vec3(x, y, 1.0f);
//	m_vertices[m_numRectangles].topRight = glm::vec3(x + width, y, 1.0f);
//	m_vertices[m_numRectangles].bottomLeft = glm::vec3(x, y - height, 1.0f);
//	m_vertices[m_numRectangles].bottomRight = glm::vec3(x + width, y - height, 1.0f);
//
//	m_vertices[m_numRectangles].topLeftColor = color;
//	m_vertices[m_numRectangles].topRightColor = color;
//	m_vertices[m_numRectangles].bottomLeftColor = color;
//	m_vertices[m_numRectangles].bottomRightColor = color;
//
//	// Triangle 1 - Top left -> top right -> bottom left
//	m_indices[(m_numRectangles * 6) + 0] = (m_numRectangles * sizeRect) + 0;
//	m_indices[(m_numRectangles * 6) + 1] = (m_numRectangles * sizeRect) + 2;
//	m_indices[(m_numRectangles * 6) + 2] = (m_numRectangles * sizeRect) + 4;
//
//	// Triangle 2 - Bottom left -> Bottom right -> Top right
//	m_indices[(m_numRectangles * 6) + 3] = (m_numRectangles * sizeRect) + 4;
//	m_indices[(m_numRectangles * 6) + 4] = (m_numRectangles * sizeRect) + 6;
//	m_indices[(m_numRectangles * 6) + 5] = (m_numRectangles * sizeRect) + 2;
//
//	m_numRectangles++;
//
//	return m_numRectangles - 1;
//}
//
//int RectangleManager::Render()
//{
//
//	glBindVertexArray(m_VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(Rectangle) * m_vertices.size(), (void*)(&m_vertices[0]), GL_STATIC_DRAW);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_indices.size(), (void*)(&m_indices[0]), GL_STATIC_DRAW);
//
//	glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//	return 0;
//}
//
//bool RectangleManager::SetVertexColor(int rectIndex, RectangleManager::Corners corner, glm::vec3 color) {
//
//	if (rectIndex >= m_numRectangles) return false;
//
//	switch (corner) {
//	case(Corners::TopLeft):
//		m_vertices[rectIndex].topLeftColor = color;
//		break;
//	case(Corners::TopRight):
//		m_vertices[rectIndex].topRightColor = color;
//		break;
//	case(Corners::BottomLeft):
//		m_vertices[rectIndex].bottomLeftColor = color;
//		break;
//	case(Corners::BottomRight):
//		m_vertices[rectIndex].bottomRightColor = color;
//		break;
//	case(Corners::All):
//		m_vertices[rectIndex].topLeftColor = color;
//		m_vertices[rectIndex].topRightColor = color;
//		m_vertices[rectIndex].bottomLeftColor = color;
//		m_vertices[rectIndex].bottomRightColor = color;
//		break;
//	default:
//		return false;
//	}
//
//	return true;
//}