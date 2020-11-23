#pragma once
#include "Rigidbody.h"

class Plane : public Rigidbody
{
public:
	Plane();
	Plane(glm::vec2 normal, float dist);
	~Plane() {}

	void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override {}
	void draw() override;

	void resolveCollision(Rigidbody* other, const glm::vec2& contact, glm::vec2* collisionNormal) override;

public:
	glm::vec2 normal;
	float distance; // from world origin

	// draw info
	float visualHalfLength = 1000;
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
};