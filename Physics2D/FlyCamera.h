#pragma once
#include "Camera.h"
#include <GLFW/glfw3.h>

class FlyCamera : public Camera
{
public:
	FlyCamera(GLFWwindow* window) : m_window(window) {}
	~FlyCamera() {}

	void update(float deltaTime);
	void setSpeed(float speed) { m_speed = speed; }

private:
	GLFWwindow* m_window = nullptr;
	float m_speed = 5.0f;
};