#ifndef _POINTS_H_
#define _POINTS_H_

#include <shaders.h>
#include <glad.h>
#include <glfw3.h>
#include <stdlib.h>
#include <cglm/cglm.h>

typedef struct {
    float x;
    float y;
    float z;
} Point;

typedef struct {

    Shader m_shader;
    unsigned int m_VAO;
    unsigned int m_VBO;

    size_t m_numPoints;
    size_t m_maxPoints;

    float* m_vertices;

} PointsDatabase;

typedef PointsDatabase* PointsManager;

void createManager(PointsManager man, Shader shader);
void AddPoint(PointsManager man, Point point);
void RenderPoints(PointsManager man);

void UpdatePoint(PointsManager man, uint32_t index, vec3 translate);


#endif // _POINTS_H_