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

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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


    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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

    Shader shader("D:\\Programs\\Renderer\\Renderer\\shaders\\vertexShader.glsl", "D:\\Programs\\Renderer\\Renderer\\shaders\\fragmentShader.glsl");
    if (!shader.GetCompilationSuccess()) {
        return -1;
    }

    RoundedRectManager round;
    round.AddRoundedRect({ 0.f, 0.f, 1.0f }, { 0.75f, 0.75f }, 0.05f, 32, { 1.0f, 1.0f, 1.0f });


    glm::mat4 view = glm::mat4(1.0f);
    // note that we're translating the scene in the reverse direction of where we want to move
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);










    // pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
    // -----------------------------------------------------------------------------------------------------------
    //glm::mat4 projection = glm::mat4(1.0f);
    //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);


    while (!glfwWindowShouldClose(window))
    {   
        glClearColor(61.0f/255.0f, 61.0f/255.0f, 61.0f/255.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.Use();

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        //glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        /*float radius = 10.0f;
        float camX = static_cast<float>(sin(glfwGetTime()) * radius);
        float camZ = static_cast<float>(cos(glfwGetTime()) * radius);
        view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));*/
        
        //glm::mat4 trans = glm::mat4(1.0f);
        ////trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
        ////trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
        shader.SetMat4f("view", view);
        shader.SetMat4f("model", model);
        shader.SetMat4f("projection", projection);
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