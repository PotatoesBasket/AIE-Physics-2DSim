#pragma once
#include "Rigidbody.h"

class Spring : public PhysicsObject
{
public:
	Spring(Rigidbody* body1, Rigidbody* body2, float springyness = 1000.0f, float damping = 100.0f, float restLength = 500.0f);
	~Spring() {}

	void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override;
	void draw() override;

	float getDistance() const { return glm::length(body1->position - body2->position); }
	bool snapped() const;

public:
	Rigidbody* body1 = nullptr;
	Rigidbody* body2 = nullptr;

	glm::vec2 contact1 = glm::vec2(0);
	glm::vec2 contact2 = glm::vec2(0);

	float springCoefficient = 1000.0f; // springyness
	float damping = 100.0f;
	float restLength = 0;
	float breakForce = 0;

	bool isBroken = false;

	// for drawing
	unsigned int noOfPoints = 20;
	float width = 30.0f;
	glm::vec4 color = glm::vec4(1, 1, 0, 1);
};