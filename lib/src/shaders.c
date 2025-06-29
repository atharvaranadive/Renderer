#include <shaders.h>
#include <stdio.h>
#include <stdlib.h>

int OpenShaderFiles(const char* vertexFilePath, const char* fragmentFilePath, char** vertexCode, char** fragCode);

/**
 * @brief Create a Shader object
 * 
 * @param [out] shader 
 * @param [in] vertexFilePath 
 * @param [in] fragmentFilePath 
 * @return int SHADER_ERR
 */
int CreateShader(Shader* shader, const char* vertexFilePath, const char* fragmentFilePath){

    char* vertexCode;
    char* fragmentCode;
    shader->m_ID = 0;
    shader->m_linked = false;
    shader->m_using = false;

    SHADER_ERR err = OpenShaderFiles(vertexFilePath, fragmentFilePath, &vertexCode, &fragmentCode);

    if(err != SHADER_ERR_SUCCESS){
        return err;
    }

    unsigned int vertex, fragment;
    int success;

    // try creating vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, (char const* const*) &vertexCode, NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success){
        free(vertexCode);
        free(fragmentCode);
        return SHADER_ERR_NOT_COMPILED;
    }

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, (char const* const*) &fragmentCode, NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success){
        free(vertexCode);
        free(fragmentCode);
        return SHADER_ERR_NOT_COMPILED;
    }

    shader->m_ID = glCreateProgram();
    glAttachShader(shader->m_ID, vertex);
    glAttachShader(shader->m_ID, fragment);
    glLinkProgram(shader->m_ID);
    glGetProgramiv(shader->m_ID, GL_LINK_STATUS, &success);
    if(!success){
        free(vertexCode);
        free(fragmentCode);
        return SHADER_ERR_LINKING_FAILED;
    }

    shader->m_linked = true;

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    free(vertexCode);
    free(fragmentCode);

    return SHADER_ERR_SUCCESS;
}

/**
 * @brief Actives the shader for use in future draw calls
 * 
 * @param [in] shader 
 * @return int SHADER_ERR
 */
int UseShader(Shader* shader){

    if(shader->m_linked == false || shader->m_ID == 0){
        return SHADER_ERR_ACTIVE_FAILED;
    }

    glUseProgram(shader->m_ID);
    shader->m_using = true;
    return SHADER_ERR_SUCCESS;

}

/**
 * @brief Deletes previously created shader
 * 
 * @param shader 
 * @return int 
 */
int DeleteShader(Shader* shader){
    glDeleteProgram(shader->m_ID);
    shader->m_using = false;
    shader->m_linked = false;
    shader->m_ID = 0;
    return SHADER_ERR_SUCCESS;
}

/**
 * @brief Set a Bool uniform related to shader
 * 
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
int SetBool(const Shader* shader, const char* name, bool value){

    if(shader->m_linked == false) return SHADER_ERR_LINKING_FAILED;

    GLint loc = glGetUniformLocation(shader->m_ID, name);
    if(loc == GL_INVALID_VALUE) return SHADER_ERR_NOT_COMPILED;
    if(loc == GL_INVALID_OPERATION) return SHADER_ERR_UNIFORM_NOT_FOUND;

    glUniform1i(loc, (int)value);

    return SHADER_ERR_SUCCESS;

}

/**
 * @brief Set a Int uniform related to shader
 * 
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
int SetInt(const Shader* shader, const char* name, int value){

    if(shader->m_linked == false) return SHADER_ERR_LINKING_FAILED;

    GLint loc = glGetUniformLocation(shader->m_ID, name);
    if(loc == GL_INVALID_VALUE) return SHADER_ERR_NOT_COMPILED;
    if(loc == GL_INVALID_OPERATION) return SHADER_ERR_UNIFORM_NOT_FOUND;

    glUniform1i(loc, value);

    return SHADER_ERR_SUCCESS;

}

/**
 * @brief Set a float uniform related to shader
 * 
 * @param [in] Shader shader
 * @param [in] name name of uniform
 * @param [in] value value to set to
 * @return int SHADER_ERR
 */
int SetFloat(const Shader* shader, const char* name, float value){

    if(shader->m_linked == false) return SHADER_ERR_LINKING_FAILED;

    GLint loc = glGetUniformLocation(shader->m_ID, name);
    if(loc == GL_INVALID_VALUE) return SHADER_ERR_NOT_COMPILED;
    if(loc == GL_INVALID_OPERATION) return SHADER_ERR_UNIFORM_NOT_FOUND;

    glUniform1f(loc, value);

    return SHADER_ERR_SUCCESS;

}

int SetFloat3(const Shader *shader, const char *name, float value1, float value2, float value3){
    
    if(shader->m_linked == false) return SHADER_ERR_LINKING_FAILED;

    GLint loc = glGetUniformLocation(shader->m_ID, name);
    if(loc == GL_INVALID_VALUE) return SHADER_ERR_NOT_COMPILED;
    if(loc == GL_INVALID_OPERATION) return SHADER_ERR_UNIFORM_NOT_FOUND;

    glUniform3f(loc, value1, value2, value3);

    return SHADER_ERR_SUCCESS;

}

/**
 * @brief Opens shader files and heap allocates strings to hold code. Must be freed by user if successful.
 * 
 * @param [in] vertexFilePath 
 * @param [in] fragmentFilePath 
 * @param [out] vertexCode 
 * @param [out] fragCode 
 * @return int SHADER_ERR
 */
int OpenShaderFiles(const char* vertexFilePath, const char* fragmentFilePath, char** vertexCode, char** fragCode){

    // Open both files
    FILE* vertexFile = fopen(vertexFilePath, "rb+");
    if(vertexFile == NULL){
        return SHADER_ERR_FILE_NOT_FOUND;
    }

    FILE* fragmentFile = fopen(fragmentFilePath, "rb+");
    if(fragmentFile == NULL){
        return SHADER_ERR_FILE_NOT_FOUND;
    }

    // Find size of both files
    fseek(vertexFile, 0U, SEEK_END);
    size_t vertexFileSize = ftell(vertexFile);
    rewind(vertexFile);

    fseek(fragmentFile, 0U, SEEK_END);
    size_t fragmentFileSize = ftell(fragmentFile);
    rewind(fragmentFile);

    // Allocate heap to hold full string ( with /0)
    *vertexCode = (char*) malloc((sizeof(char) * vertexFileSize) + 1);
    if(!*vertexCode){
        fclose(vertexFile);
        fclose(fragmentFile);
        return SHADER_ERR_NO_RAM;
    }

    *fragCode = (char*) malloc((sizeof(char) * fragmentFileSize) + 1);
    if(!*fragCode){
        fclose(vertexFile);
        fclose(fragmentFile);
        free(*vertexCode);
        return SHADER_ERR_NO_RAM;
    }

    size_t temp = fread(*vertexCode, 1U, vertexFileSize, vertexFile);
    if(vertexFileSize != temp){
        fclose(vertexFile);
        fclose(fragmentFile);
        free(*vertexCode);
        free(*fragCode);
        return SHADER_ERR_NOT_READ_FULL_FILE;
    }
    (*vertexCode)[vertexFileSize] = 0;

    temp = fread(*fragCode, 1U, fragmentFileSize, fragmentFile);
    if(fragmentFileSize != temp){
        fclose(vertexFile);
        fclose(fragmentFile);
        free(*vertexCode);
        free(*fragCode);
        return SHADER_ERR_NOT_READ_FULL_FILE;
    }
    (*fragCode)[fragmentFileSize] = 0;

    fclose(vertexFile);
    fclose(fragmentFile);

    return SHADER_ERR_SUCCESS;

}