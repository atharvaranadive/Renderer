#include <points.h>
#include <string.h>

void createManager(PointsManager man, Shader shader){

    // if(shader.m_linked == false) return;

    // man->m_shader = shader;
    // man->m_maxPoints = 100;
    // man->m_numPoints = 0;

    // man->m_vertices = calloc(man->m_maxPoints, sizeof(Point));

    // if(man->m_vertices == NULL) return;

    // glGenVertexArrays(1, &(man->m_VAO));
    // glGenBuffers(1, &(man->m_VBO));

    // glBindVertexArray(man->m_VAO);

    // glBindBuffer(GL_ARRAY_BUFFER, man->m_VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(man->m_vertices), man->m_vertices, GL_DYNAMIC_DRAW);

    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Point), (GLvoid*)0);
    // glEnableVertexAttribArray(0);

    // glBindVertexArray(0);

    // man->m_created = true;
}

void AddPoint(PointsManager man, Point point){

    // if(!man->m_created) return;

    // if(man->m_numPoints == man->m_maxPoints){
    //     man->m_maxPoints *= 2;
    //     float* tempPtr = realloc(man->m_vertices, man->m_maxPoints * sizeof(Point));
    //     if(tempPtr == NULL){
    //         return;
    //     }
    //     else{
    //         man->m_vertices = tempPtr;
    //         glBindVertexArray(man->m_VAO);
    //         glBufferData(GL_ARRAY_BUFFER, sizeof(man->m_vertices), man->m_vertices, GL_DYNAMIC_DRAW);
    //         glBindVertexArray(0);
    //     }
    // }

    // uint32_t offset = man->m_numPoints * sizeof(Point);
    // memcpy(&(man->m_vertices[offset]), &point, sizeof(Point));
    // man->m_numPoints++;


}


void RenderPoints(PointsManager man){

    // if(!man->m_created) return;
    // UseShader(&(man->m_shader));

    // glBindVertexArray(man->m_VAO);
    // glDrawArrays(GL_POINT, 0, man->m_numPoints);

}

void UpdatePoint(PointsManager man, uint32_t index, vec3 translate){

    // if(!man->m_created) return;
    // if(index >= man->m_numPoints) return;
    // uint32_t offset = index * sizeof(Point);
    // man->m_vertices[offset + 0] += translate[0];
    // man->m_vertices[offset + 1] += translate[1];
    // man->m_vertices[offset + 2] += translate[2];
    // glBindBuffer(GL_ARRAY_BUFFER, man->m_VBO);
    // glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(Point), &(man->m_vertices[offset]));
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DeletePoints(PointsManager man){

    // if(man->m_vertices != NULL){
    //     free(man->m_vertices);
    // }
    // man->m_numPoints = 0;
    // man->m_maxPoints = 0;
    // man->m_created = false;
    // glDeleteBuffers(1, &(man->m_VBO));
    // glDeleteVertexArrays(1, &(man->m_VAO));
}