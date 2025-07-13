#pragma once
#define _USE_MATH_DEFINES
#include <glm/glm.hpp>
#include <glad.h>
#include <vector>

class CircleGenerator {

private:
	float const m_radius = 0.0f;
	// Number of points to use
	uint32_t const m_quality = 0;
	// Angle variation between two points
	float const m_dAngle = 0.0f;

public:

	CircleGenerator(float radius, uint32_t quality);

	/**
	* @brief Returns the ith point in perimeter
	*/
	glm::vec2 getPoint(uint32_t i) const;


};

class RoundedRectangleGenerator {

private:

	glm::vec2 const m_size = { 0.0f, 0.0f };
	glm::vec2 const m_centers[4];
	uint32_t const m_quality = 0;
	CircleGenerator const gen;

public:

	RoundedRectangleGenerator(glm::vec2 size, float radius, uint32_t quality);

	/**
	* @brief Returns the ith point in perimeter
	*/
	glm::vec2 getPoint(uint32_t i) const;

};



class RoundedRectManager {

public:

	RoundedRectManager();
	~RoundedRectManager();

	unsigned int AddCircle(glm::vec3 position, float radius, uint32_t quality, glm::vec3 color);
	unsigned int AddRoundedRect(glm::vec3 position, glm::vec2 size, float radius, uint32_t quality, glm::vec3 color);

	std::array<glm::vec3, 4> GetCenters(glm::vec2 size, float radius);

	bool Render();

private:

	struct Point {
		glm::vec3 position;
		glm::vec3 color;
	};

	unsigned int m_VBO = 0;
	unsigned int m_VAO = 0;

	std::vector<GLint> m_startingIndices;
	std::vector<GLsizei> m_countPerRect;

	std::vector<Point> m_vertices;


};
