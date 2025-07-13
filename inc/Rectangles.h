#pragma once

#include <glm/glm.hpp>
#include <glad.h>
#include <vector>

class RectangleManager {

public:

	enum class Corners : unsigned int {
		TopLeft = 0,
		TopRight = 1,
		BottomLeft = 2,
		BottomRight = 3,
		All = 4
	};

	RectangleManager();
	~RectangleManager();

	int AddRectangle(float x, float y, float height, float width, glm::vec3 color);
	int Render();

	bool SetVertexColor(int rectIndex, RectangleManager::Corners corner, glm::vec3 color);




private:

	struct Rectangle {

		glm::vec3 topLeft;
		glm::vec3 topLeftColor;
		glm::vec3 topRight;
		glm::vec3 topRightColor;
		glm::vec3 bottomLeft;
		glm::vec3 bottomLeftColor;
		glm::vec3 bottomRight;
		glm::vec3 bottomRightColor;

	};

	GLuint m_VAO = 0;
	GLuint m_VBO = 0;
	GLuint m_EBO = 0;

	std::vector<Rectangle> m_vertices;
	std::vector<GLuint> m_indices;

	unsigned int m_numRectangles = 0;

};