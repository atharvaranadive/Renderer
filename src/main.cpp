#include "glad.h"
#include "glfw3.h"
#include <glm/glm.hpp>
#include <cstdlib>
#include <iostream>
#include <array>
#include "Shaders.h"
#include "Triangles.h"
#include "Rectangles.h"
#include "RoundedRect.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

float raf(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main(void) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, 800, 600);

    Shader shader("D:\\Programs\\RendererVS\\shaders\\vertexShader.glsl", "D:\\Programs\\RendererVS\\shaders\\fragmentShader.glsl");
    if (!shader.GetCompilationSuccess()) {
        return -1;
    }

    Triangle tri = {
        // Position                 // color
        { -0.85f, 0.85f, 0.0f }, {  1.0f, 0.0f, 0.0f }, // top left  
        { -0.85f, 0.15f, 0.0f }, {  0.0f, 1.0f, 0.0f },// bottom left 
        { -0.15f, 0.85f, 0.0f }, {  0.0f, 0.0f, 1.0f }, // top right
    };

    Triangle tri2 = {
        // Position                 // color
        { -0.15f, 0.85f, 0.0f }, {  1.0f, 0.0f, 0.0f },// top right
        { -0.15f, 0.15f, 0.0f }, {  0.0f, 1.0f, 0.0f },// bottom right
        { -0.85f, 0.15f, 0.0f }, {  0.0f, 0.0f, 1.0f },// bottom left // color
    };

    Triangles col;
    col.AddTriangle(tri);
    //col.AddTriangle(tri2);

    RectangleManager recMan;

    for (int i = 0; i < 100; i++) {

        recMan.AddRectangle(raf(-1.0f, 1.0f), \
            raf(-1.0f, 1.0f), \
            raf(0.15f, 0.25f), \
            raf(0.15f, 0.25f), \
            { raf(0.0f, 1.0f), raf(0.0f, 1.0f), raf(0.0f, 1.0f)} );


    }

    RoundedRectManager round;
    float rad = 0.05f;

    //std::array<glm::vec3, 4> centers = round.GetCenters({ 1.5f, 1.0f }, rad);
    //round.AddCircle(centers[0], rad, 128, {1.0f, 0.0f, 0.0f});
    //round.AddCircle(centers[1], rad, 128, { 0.0f, 1.0f, 0.0f });
    //round.AddCircle(centers[2], rad, 128, { 0.0f, 0.0f, 1.0f });
    //round.AddCircle(centers[3], rad, 128, { 1.0f, 1.0f, 1.0f });
    round.AddRoundedRect({ -0.75f, 0.75f, 1.0f }, { 0.25f, 0.25f }, 0.05f, 8, { 1.0f, 1.0f, 1.0f });
    round.AddRoundedRect({ 0.0f, 0.0f, 1.0f }, { 0.25f, 0.25f }, 0.05f, 32, { 1.0f, 1.0f, 1.0f });
    round.AddRoundedRect({ 0.75f, -0.75f, 1.0f }, { 0.25f, 0.25f }, 0.05f, 64, { 1.0f, 1.0f, 1.0f });
    round.AddCircle({ -0.75f, -0.75f, 1.0f }, 0.1f, 3, { 1.0f, 1.0f, 1.0f });


    ////recMan.AddRectangle(-0.85f, 0.85f, 0.75f, 0.75f, { 1.0f, 0.0f, 0.0f });
    //recMan.AddRectangle(0.15f, -0.15f, 0.75f, 0.75f, { 0.0f, 1.0f, 0.0f });
    //recMan.AddRectangle(0.15f, 0.85f, 0.75f, 0.75f, { 0.0f, 0.0f, 1.0f });
    //recMan.AddRectangle(-0.85f, -0.15f, 0.75f, 0.75f, { 1.0f, 1.0f, 1.0f });



    while (!glfwWindowShouldClose(window))
    {   
        glClearColor(61.0f/255.0f, 61.0f/255.0f, 61.0f/255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();
        glm::mat4 trans = glm::mat4(1.0f);
        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetMat4f("transform", trans);
        round.Render();
        //for (int i = 0; i < 100; i++) {

        //    recMan.SetVertexColor(i, RectangleManager::Corners::All, { raf(0.0f, 1.0f), raf(0.0f, 1.0f), raf(0.0f, 1.0f)});


        //}

        //recMan.Render();
        //col.Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}