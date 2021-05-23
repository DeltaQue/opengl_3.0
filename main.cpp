#pragma once

#include <glad/glad.h>		// GLFW�� ���� ����!
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

int main()
{
	// glfw �ʱ�ȭ
	glfwInit();
	// OpenGL 3.3 ���� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL Core Profile ��� ����
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// window ������ ���� callback ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD : OpenGL�� �Լ� ������ ����
	// glfwGetProcAdress : ������ OS ȯ�溰 �ùٸ� �Լ� ����
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}
	
	// shaer file load
	Shader ourShader("Shader/vertex_shader.vs", "Shader/fragment_shader.fs", nullptr);

	float vertices[] = {
		// ��ġ				// �÷�
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ���� �ϴ�
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���� �ϴ�
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // �� 
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ��ġ Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// �÷� Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// wireframe polygons�� �׸���
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Loop�� ���۵ɶ����� GLFW�� ����Ǿ����� Ȯ��
	while (!glfwWindowShouldClose(window)) {
		processInput(window);		// �Է�

		// -------- Rendering ���� --------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// window Clear Color ���� (Default Color)
		glClear(GL_COLOR_BUFFER_BIT);			// ���� color�� window clear

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		int offset_x = glGetUniformLocation(ourShader.shaderID, "offset");
		glUniform1f(offset_x, 0.5f);

		// [1] Vertext Shader
		// �ϳ��� ������ �Է¹���

		// [2] Geometry Shader
		// �Է����� ���� �������� ������ primitive�� �����ϰ�, ���ο� ������ �����Ͽ� ���ο�(�Ǵ� �ٸ�) primitive�� �����Ͽ� �ٸ� �������� ��ȯ�� �� �ִ� ����

		// [3] Rasterization (pixel�� ��ȯ)
		// ȭ���� ������ ��ġ�� �ȼ��� ����

		// [4] Fragment Shader (=Pixel Shader)

		// [5] Blending
		// -------- Rendering ���� --------

		glfwSwapBuffers(window);	// color buffer�� ��ü, single buffer ���� 
		glfwPollEvents();			// Ű����, ���콺 �Է� �̺�Ʈ Ȯ��
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(ourShader.shaderID);

	// �Ҵ�Ǿ��� ��� �ڿ� ���� �� ����
	glfwTerminate();
	return 0;
}

// window�� ����� ����ɶ����� ȣ��
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "framebuffer_size_callback resize width: " << width << "height: " << height << std::endl;
}

void processInput(GLFWwindow* window) {
	// ESC �������� window ����
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
