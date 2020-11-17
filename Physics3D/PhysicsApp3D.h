#pragma once
#include <Application.h>
#include <Input.h>
#include <glm/mat4x4.hpp>

class PhysicsApp3D : public aie::Application
{
public:
	PhysicsApp3D() {}
	~PhysicsApp3D() {}

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:
	aie::Input* m_input = nullptr;

	// camera
	glm::mat4 m_viewMatrix = glm::mat4(1);
	glm::mat4 m_projectionMatrix = glm::mat4(1);
};