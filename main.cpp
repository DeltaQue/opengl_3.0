#pragma once

#include <glad/glad.h>		// GLFW와 순서 주의!
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
	// glfw 초기화
	glfwInit();
	// OpenGL 3.3 버전 세팅
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// OpenGL Core Profile 사용 선언
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	// window 사이즈 변경 callback 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// GLAD : OpenGL용 함수 포인터 관리
	// glfwGetProcAdress : 컴파일 OS 환경별 올바른 함수 정의
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}
	
	// shaer file load
	Shader ourShader("Shader/vertex_shader.vs", "Shader/fragment_shader.fs", nullptr);

	float vertices[] = {
		// 위치				// 컬러
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 우측 하단
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 좌측 하단
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 위 
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// 위치 Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 컬러 Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// wireframe polygons로 그리기
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Loop이 시작될때마다 GLFW가 종료되었는지 확인
	while (!glfwWindowShouldClose(window)) {
		processInput(window);		// 입력

		// -------- Rendering 영역 --------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// window Clear Color 세팅 (Default Color)
		glClear(GL_COLOR_BUFFER_BIT);			// 현재 color로 window clear

		ourShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		int offset_x = glGetUniformLocation(ourShader.shaderID, "offset");
		glUniform1f(offset_x, 0.5f);

		// [1] Vertext Shader
		// 하나의 정점을 입력받음

		// [2] Geometry Shader
		// 입력으로 들어온 정점들의 집합을 primitive를 구성하고, 새로운 정점을 방출하여 새로운(또는 다른) primitive를 형성하여 다른 도형으로 변환될 수 있는 과정

		// [3] Rasterization (pixel로 변환)
		// 화면의 적절한 위치의 픽셀과 매핑

		// [4] Fragment Shader (=Pixel Shader)

		// [5] Blending
		// -------- Rendering 영역 --------

		glfwSwapBuffers(window);	// color buffer를 교체, single buffer 사용시 
		glfwPollEvents();			// 키보드, 마우스 입력 이벤트 확인
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	//glDeleteBuffers(1, &EBO);
	glDeleteProgram(ourShader.shaderID);

	// 할당되었던 모든 자원 정리 및 삭제
	glfwTerminate();
	return 0;
}

// window의 사이즈가 변경될때마다 호출
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	std::cout << "framebuffer_size_callback resize width: " << width << "height: " << height << std::endl;
}

void processInput(GLFWwindow* window) {
	// ESC 눌렀을때 window 종료
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
