#pragma once

#include <glad/glad.h>		// GLFW와 순서 주의!
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader/shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// glm (math)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, Shader& shader);

// settings
constexpr unsigned int SCR_WIDTH = 800;
constexpr unsigned int SCR_HEIGHT = 600;

float value = 0.2f;

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

	// Depth Test On
	glEnable(GL_DEPTH);
	
	// shaer file load
	Shader ourShader("Shader/vertex_shader.vs", "Shader/fragment_shader.fs", nullptr);

	float vertices[] = {
		// 위치				// 컬러				// 텍스쳐 좌표
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f,   // 우측 상단
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f,   // 우측 하단
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 좌측 하단
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f    // 좌측 상단
	};

	unsigned int indices[] = {
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
	};

	unsigned int VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// 위치 Attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// 컬러 Attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// 텍스쳐 uv Attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// wireframe polygons로 그리기
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// 텍스쳐 좌표
	unsigned int texture1, texture2;
	// Texture1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// s: x축, t: y축
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture Filtering, Mipmap, 텍스쳐 픽셀 및 밉맵 보간으로 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// 확대(Magnification) 필터 설정
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texrue" << std::endl;
	}
	stbi_image_free(data);

	// Texture2
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	ourShader.use();
	//glUniform1i(glGetUniformLocation(ourShader.shaderID, "texture1"), 0);
	ourShader.setInt("texture1", 0);
	ourShader.setInt("texture2", 1);
	ourShader.setFloat("value", value);

	glm::mat4 proj(1.0f);
	proj = glm::perspective(glm::radians(45.0f), (float)(SCR_WIDTH/ SCR_HEIGHT), 0.1f, 100.f);
	unsigned int projectionMat = glGetUniformLocation(ourShader.shaderID, "projection");
	glUniformMatrix4fv(projectionMat, 1, GL_FALSE, glm::value_ptr(proj));

	glm::mat4 view(1.0f);
	// 카메라를 뒤로 뺀다는 느낌
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
	unsigned int viewMat = glGetUniformLocation(ourShader.shaderID, "view");
	glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(view));

	glm::mat4 model(1.0f);
	model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	unsigned int modelMat = glGetUniformLocation(ourShader.shaderID, "model");
	glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model));

	// Loop이 시작될때마다 GLFW가 종료되었는지 확인
	while (!glfwWindowShouldClose(window)) {
		processInput(window, ourShader);		// 입력

		// -------- Rendering 영역 --------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);	// window Clear Color 세팅 (Default Color)
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// 현재 color로 Color, Depth buffer clear

		// 텍스쳐 바인드
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		ourShader.use();
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);	// color buffer를 교체, single buffer 사용시 
		glfwPollEvents();			// 키보드, 마우스 입력 이벤트 확인
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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

void processInput(GLFWwindow* window, Shader& shader) {
	// ESC 눌렀을때 window 종료
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		std::cout << "key down up" << std::endl;
		if (value < 1.0f)
			value += 0.01f;
		shader.setFloat("value", value);
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		std::cout << "key down down" << std::endl;
		if (value > 0.0f)
			value -= 0.01f;
		shader.setFloat("value", value);
	}
}
