#include <glad.h>
#include <glfw3.h>
#include <stdio.h>
#include <time.h>

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
        "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}

long timediff(clock_t t1, clock_t t2) {
    long elapsed;
    elapsed = ((double)t2 - t1) / CLOCKS_PER_SEC * 1000;
    return elapsed;
}

float vertRect1[] = {
    -0.15f, 0.85f, 0.0f,  // top right
    -0.15f, 0.15f, 0.0f,  // bottom right
    -0.85f, 0.15f, 0.0f,  // bottom left
    -0.85f, 0.85f, 0.0f   // top left 
};
unsigned int indRect1[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};

float vertRect2[] = {
    0.85f, -0.15f, 0.0f,  // top right
    0.85f, -0.85f, 0.0f,  // bottom right
    0.15f, -0.85f, 0.0f,  // bottom left
    0.15f, -0.15f, 0.0f   // top left 
};
unsigned int indRect2[] = {  // note that we start from 0!
    0, 1, 3,  // first Triangle
    1, 2, 3   // second Triangle
};


int main(void){

    if(!glfwInit()){
        printf("glfw cannot Init");
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learning", NULL, NULL);
    if(window == NULL){
        printf("Could Not Open Window");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        printf("Could not init GLAD");
        glfwTerminate();
        return -1;
    }
    
    glViewport(0,0,800,600);

    unsigned int VBO[2];
    unsigned int VAO[2];
    unsigned int EBO[2];

    glGenVertexArrays(2, VAO);
    glGenBuffers(2, VBO);
    glGenBuffers(2, EBO);

    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertRect1), vertRect1, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indRect1), indRect1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    // resetting/unbinding, not usually used
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertRect2), vertRect2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indRect2), indRect2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n%s\n",infoLog);
    }


    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        printf("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n%s\n",infoLog);
    }

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("ERROR::SHADER::LINKING_FAILED\n%s\n",infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader); 

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); 
    clock_t startTime, endTime;
    long diff;
    while(!glfwWindowShouldClose(window)){
        startTime = clock();
        processInput(window);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO[0]);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glBindVertexArray(VAO[1]);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
        endTime = clock();
        diff = timediff(startTime, endTime);
        printf("Frame time: %f\r", 1000.0f/(double)diff);
    }

    glDeleteVertexArrays(2, VAO);
    glDeleteBuffers(2, VBO);
    glDeleteBuffers(2, EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
    
    return 1;
}