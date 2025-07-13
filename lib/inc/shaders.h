#ifndef _SHADERS_H_
#define _SHADERS_H_

#include <glad.h>

#include <stdbool.h>

typedef enum {
   SHADER_ERR_SUCCESS = 0,
   SHADER_ERR_FILE_NOT_FOUND = 1,
   SHADER_ERR_NO_RAM = 2,
   SHADER_ERR_NOT_READ_FULL_FILE = 3,
   SHADER_ERR_NOT_COMPILED = 4,
   SHADER_ERR_LINKING_FAILED = 5,
   SHADER_ERR_ACTIVE_FAILED = 6,
   SHADER_ERR_UNIFORM_NOT_FOUND = 7
} SHADER_ERR;

typedef struct {
    unsigned int m_ID;
    bool m_linked;
    bool m_using;

} Shader;

SHADER_ERR CreateShader(Shader* shader, const char* vertexFilePath, const char* fragmentFilePath);
SHADER_ERR UseShader(Shader* shader);
SHADER_ERR DeleteShader(Shader* shader);

SHADER_ERR SetBool(const Shader* shader, const char* name, bool value);
SHADER_ERR SetInt(const Shader* Shader, const char* name, int value);
SHADER_ERR SetFloat(const Shader* shader, const char* name, float value);

SHADER_ERR SetFloat3(const Shader* shader, const char* name, float value1, float value2, float value3);

#endif // SHADERS_H