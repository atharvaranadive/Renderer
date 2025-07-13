#pragma once

#include <cstdint>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {

public:

	enum class Err : uint8_t {
		SUCCESS = 0,
		FILE_NOT_FOUND = 1,
		NO_RAM = 2,
		NOT_READ_FULL_FILE = 3,
		NOT_COMPILED = 4,
		LINKING_FAILED = 5,
		ACTIVE_FAILED = 6,
		UNIFORM_NOT_FOUND = 7
	};
	Shader(const char* vertexFilePath, const char* fragmentFilePath);

	Shader::Err Use();
	Shader::Err Delete();

	unsigned int GetID() { return m_ID; }

	Shader::Err SetBool(const char* name, bool value);
	Shader::Err SetInt(const char* name, int value);
	Shader::Err SetFloat(const char* name, float value);

	Shader::Err SetFloat3(const char* name, float value1, float value2, float value3);

	Shader::Err SetMat4f(const char* name, glm::mat4 mat);

	bool GetCompilationSuccess() { return m_compiled;  }

private:

	unsigned int m_ID = 0;
	bool m_compiled = false;
	bool m_using = false;

	Shader::Err OpenShaderFiles(const char* vertexPath, const char* fragmentPath, std::string& vertexCode, std::string& fragCode);
};