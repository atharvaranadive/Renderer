#include "RoundedRect.h"
#include <array>

CircleGenerator::CircleGenerator(float radius, uint32_t quality)
	: m_radius{ radius },
	  m_quality{ quality },
	  m_dAngle{ (2.0f * static_cast<float>(M_PI)) / static_cast<float>(quality) } {}

glm::vec2 CircleGenerator::getPoint(uint32_t i) const 
{
	float const angle = m_dAngle * static_cast<float>(i);
	return m_radius * glm::vec2{ cos(angle), sin(angle) };
}

RoundedRectManager::RoundedRectManager()
{
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
}

RoundedRectManager::~RoundedRectManager()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);
}

unsigned int RoundedRectManager::AddCircle(glm::vec3 position, float radius, uint32_t quality, glm::vec3 color)
{
	CircleGenerator const gen{ radius, quality };
	m_startingIndices.push_back(static_cast<GLsizei>(m_vertices.size()));
	m_countPerRect.push_back(static_cast<GLsizei>(quality));
	glm::vec3 pointPos;
	glm::vec2 rawPos;

	for (uint32_t i = 0; i < quality; i++) {
		//Create point by offsetting it from center position
		rawPos = gen.getPoint(i);
		pointPos = glm::vec3{ position[0] + rawPos[0], position[1] + rawPos[1], position[2] };
		m_vertices.push_back({ pointPos, color });
	}


	return 0;
}


bool RoundedRectManager::Render()
{
	if (m_vertices.size() == 0) return false;

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Point) * m_vertices.size(), (void*)(&m_vertices[0]), GL_STATIC_DRAW);

	glMultiDrawArrays(GL_TRIANGLE_FAN,					    // MODE
		(&m_startingIndices[0]),						    // first
		(&m_countPerRect[0]),							    // count per fan
		static_cast<GLsizei>(m_startingIndices.size()));	// size of first/count per fan

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;

}

RoundedRectangleGenerator::RoundedRectangleGenerator(glm::vec2 size, float radius, uint32_t quality)
   : m_size{ size },
	m_centers{
	   {    (size.x / 2) - radius  ,   ((size.y / 2) - radius) },	// Top Right
	   { -((size.x / 2) - radius) ,   ((size.y / 2) - radius) },	// Top left
	   { -((size.x / 2) - radius) , -((size.y / 2) - radius) },  // Bottom Left
	   {    (size.x/2) - radius  , - ((size.y/2) - radius) },	// Bottom right
		
		
		
	},
	m_quality{ quality / 4},
	gen{ radius, quality - 4 } {}

glm::vec2 RoundedRectangleGenerator::getPoint(uint32_t i) const
{
	uint32_t const cornerIdx = i / m_quality;
	glm::vec2 cornerPos = gen.getPoint(i - cornerIdx);
	return m_centers[cornerIdx] + cornerPos;
}


unsigned int RoundedRectManager::AddRoundedRect(glm::vec3 position, glm::vec2 size, float radius, uint32_t quality, glm::vec3 color)
{
	RoundedRectangleGenerator const gen{ size, radius, quality };
	m_startingIndices.push_back(static_cast<GLsizei>(m_vertices.size()));
	m_countPerRect.push_back(static_cast<GLsizei>(quality));
	glm::vec3 pointPos;
	glm::vec2 rawPos;

	for (uint32_t i = 0; i < quality; i++) {
		//Create point by offsetting it from center position
		rawPos = gen.getPoint(i);
		pointPos = glm::vec3{ position[0] + rawPos[0], position[1] + rawPos[1], position[2] };
		m_vertices.push_back({ pointPos, color });
	}


	return 0;
}

std::array<glm::vec3, 4> RoundedRectManager::GetCenters(glm::vec2 size, float radius) {

	std::array<glm::vec3, 4> cen;
	cen[0] = { (size.x / 2) - radius  , -((size.y / 2) - radius), 1.0f };
	cen[1] = { -((size.x / 2) - radius) , -((size.y / 2) - radius), 1.0f };
	cen[2] = { -((size.x / 2) - radius) ,   ((size.y / 2) - radius), 1.0f };
	cen[3] = { (size.x / 2) - radius  ,   ((size.y / 2) - radius), 1.0f };

	return cen;
}