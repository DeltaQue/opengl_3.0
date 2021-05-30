#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	// Singleton
	static Camera& Get()
	{
		static Camera* instance = new Camera();
		return *instance;
	}

	enum ProjectionType : unsigned int {
		Orthographic,
		Perspective
	};

private:
	Camera()
		:projectionType(Perspective), fov(glm::radians(45.0f)), 
		nearFar(glm::vec2(0.1f, 100.0f)), viewPort(glm::vec4(0.0f, 0.0f, -3.0f, 0.0f)) {}
	~Camera() = default;

	ProjectionType projectionType;
	float fov;
	glm::vec2 nearFar;
	glm::vec4 viewPort;


public:
	void SetProjection(ProjectionType type) { projectionType = type; }
	ProjectionType GetProjection() { return projectionType; }

	void SetFov(float fov) { this->fov = fov; }
	float GetFov() { return fov; }

	void SetClipping(const glm::vec2& nf) { nearFar = nf; }
	void SetClipping(glm::vec2& nf) { nearFar = std::move(nf); }
	const glm::vec2& GetClipping() { return nearFar; }

	void SetViewPort(const glm::vec4& vp) { viewPort = vp; }
	void SetViewPort(glm::vec4& vp) { viewPort = std::move(vp); }
	const glm::vec4& GetViewPort() { return viewPort; }

};