#pragma once

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	// shader�� file���� �а� ����
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath, const GLchar* geometryPath = nullptr);
	Shader() = default;

public:
	// Shader Program ID
	unsigned int shaderID;

	// shader�� Ȱ��ȭ �ϰ� ���
	void use();

	// Uniform ��ƿ��Ƽ �Լ���
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	void shaderCompile(const char* vertexCode, const char* framentCode, const char* geometryCode = nullptr);
	void checkCompileErrors(GLuint shader, std::string type);
};