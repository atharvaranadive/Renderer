#include "Shaders.h"
#include <fstream>
#include <sstream>
#include <iostream>

#include "glad.h"


/**
 * @brief Create a Shader object
 *
 * @param [in] vertexFilePath
 * @param [in] fragmentFilePath
 * @return int Shader::Err
 */
Shader::Shader(const char* vertexPath, const char* fragmentPath) {

    std::string vertexCode, fragmentCode;

    Shader::Err err = OpenShaderFiles(vertexPath, fragmentPath, vertexCode, fragmentCode);

    if (err != Shader::Err::SUCCESS) {
        return;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;
    int success;

    // try creating vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (char const* const*)&vShaderCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        return;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (char const* const*)&fShaderCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        return;
    }

    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertex);
    glAttachShader(m_ID, fragment);
    glLinkProgram(m_ID);
    glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
    if (!success) {
        return;
    }

    m_compiled = true;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return;


}

/**
 * @brief Actives the shader for use in future draw calls
 *
 * @return int SHADER_ERR
 */
Shader::Err Shader::Use() {

    if (m_compiled == false || m_ID == 0) {
        return Shader::Err::ACTIVE_FAILED;
    }

    glUseProgram(m_ID);
    m_using = true;
    return Shader::Err::SUCCESS;

}

/**
 * @brief Deletes previously created shader
 *
 * @return int
 */
Shader::Err Shader::Delete() {
    glDeleteProgram(m_ID);
    m_using = false;
    m_compiled = false;
    m_ID = 0;
    return Shader::Err::SUCCESS;
}

/**
 * @brief Set a Bool uniform related to shader
 *
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
Shader::Err Shader::SetBool(const char* name, bool value) {

    if (m_compiled == false) return Shader::Err::LINKING_FAILED;

    GLint loc = glGetUniformLocation(m_ID, name);
    if (loc == GL_INVALID_VALUE) return Shader::Err::NOT_COMPILED;
    if (loc == GL_INVALID_OPERATION) return Shader::Err::UNIFORM_NOT_FOUND;

    glUniform1i(loc, (int)value);

    return Shader::Err::SUCCESS;

}

/**
 * @brief Set a Int uniform related to shader
 *
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
Shader::Err Shader::SetInt(const char* name, int value) {

    if (m_compiled == false) return Shader::Err::LINKING_FAILED;

    GLint loc = glGetUniformLocation(m_ID, name);
    if (loc == GL_INVALID_VALUE) return Shader::Err::NOT_COMPILED;
    if (loc == GL_INVALID_OPERATION) return Shader::Err::UNIFORM_NOT_FOUND;

    glUniform1i(loc, value);

    return Shader::Err::SUCCESS;

}

/**
 * @brief Set a float uniform related to shader
 *
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
Shader::Err Shader::SetFloat(const char* name, float value) {

    if (m_compiled == false) return Shader::Err::LINKING_FAILED;

    GLint loc = glGetUniformLocation(m_ID, name);
    if (loc == GL_INVALID_VALUE) return Shader::Err::NOT_COMPILED;
    if (loc == GL_INVALID_OPERATION) return Shader::Err::UNIFORM_NOT_FOUND;

    glUniform1f(loc, value);

    return Shader::Err::SUCCESS;

}

Shader::Err Shader::SetFloat3(const char* name, float value1, float value2, float value3) {

    if (m_compiled == false) return Shader::Err::LINKING_FAILED;

    GLint loc = glGetUniformLocation(m_ID, name);
    if (loc == GL_INVALID_VALUE) return Shader::Err::NOT_COMPILED;
    if (loc == GL_INVALID_OPERATION) return Shader::Err::UNIFORM_NOT_FOUND;

    glUniform3f(loc, value1, value2, value3);

    return Shader::Err::SUCCESS;

}

Shader::Err Shader::SetMat4f(const char* name, glm::mat4 mat) {

    if (m_compiled == false) return Shader::Err::LINKING_FAILED;

    GLint loc = glGetUniformLocation(m_ID, name);
    if (loc == GL_INVALID_VALUE) return Shader::Err::NOT_COMPILED;
    if (loc == GL_INVALID_OPERATION) return Shader::Err::UNIFORM_NOT_FOUND;

    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(mat));

    return Shader::Err::SUCCESS;

}

/*****************************************************************************************************************************************
* PRIVATE
*****************************************************************************************************************************************/

/**
 * @brief Opens shader files and reads into strings
 *
 * @param [in] vertexFilePath
 * @param [in] fragmentFilePath
 * @param [out] vertexCode
 * @param [out] fragCode
 * @return int SHADER_ERR
 */
Shader::Err Shader::OpenShaderFiles(const char* vertexPath, const char* fragmentPath, std::string& vertexCode, std::string& fragCode) {

    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragCode = fShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    return Shader::Err::SUCCESS;
}

