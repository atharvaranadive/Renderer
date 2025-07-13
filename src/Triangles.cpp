#include "Triangles.h"
#include <glad.h>

Triangles::Triangles(void) {

	glGenVertexArrays(1, &m_VAO);
	glGenBuffers(1, &m_VBO);

	//m_vertices.resize(2);
	m_vertices.resize(32);

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices), (void*)(&m_vertices[0]), GL_DYNAMIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

Triangles::~Triangles(void) {

	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_VBO);

}

bool Triangles::AddTriangle(Triangle& tri) {

	if (m_numTriangles == m_vertices.capacity()) {
		m_vertices.resize(m_numTriangles * 2);
	}

	m_vertices[m_numTriangles] = tri;
	m_numTriangles++;
	return true;

}

bool Triangles::Render(void) {
	
	if (m_vertices.size() == 0) return false;

	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Triangle) * m_vertices.size(), (void*)(&m_vertices[0]), GL_STATIC_DRAW);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_vertices.size() * 3);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}