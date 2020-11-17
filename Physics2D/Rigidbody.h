#pragma once
#include "PhysicsObject.h"
#include <glm/glm.hpp>

class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType type, const glm::vec2& position, float mass, const glm::vec2& initialVelocity = glm::vec2(0));
	~Rigidbody() {}

	void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override;

	void applyForce(const glm::vec2& force);
	void applyForceToActors(Rigidbody* other, const glm::vec2& force);

	const glm::vec2& getVelocity() { return m_velocity; }

public:
	glm::vec2 position;
	float mass;

	float linearDrag = 0.3f;
	float elasticity = 0.5f;

protected:
	glm::vec2 m_velocity;
};