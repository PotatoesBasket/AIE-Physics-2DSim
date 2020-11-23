#pragma once
#include "RigidBody.h"

class Circle : public Rigidbody
{
public:
	Circle();
	Circle(const glm::vec2& position, float rotation, float mass, float radius, const glm::vec4& color,
		const glm::vec2& initialVelocity = glm::vec2(0), float initialRotVel = 0);
	~Circle() {}

	void draw() override;

public:
	float radius;
	glm::vec4 color;
};