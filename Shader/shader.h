#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// shader를 file에서 읽고 생성
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	Shader() = default;

public:
	// Shader Program ID
	unsigned int shaderID;

	// shader를 활성화 하고 사용
	void use();

	// Uniform 유틸리티 함수들
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	void shaderCompile(const char* vertexCode, const char* framentCode, const char* geometryCode = nullptr);
	void checkCompileErrors(GLuint shader, std::string type);
};