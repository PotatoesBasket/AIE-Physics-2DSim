#pragma once
#include "PhysicsObject.h"
#include <glm/glm.hpp>

class Rigidbody : public PhysicsObject
{
public:
	Rigidbody(ShapeType type, const glm::vec2& position, float rotation,
		const glm::vec2& initialVelocity = glm::vec2(0), float initialRotVel = 0);
	~Rigidbody() {}

	virtual void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override;

	virtual void resolveCollision(Rigidbody* other, const glm::vec2& contact, glm::vec2* collisionNormal);

	void applyForce(const glm::vec2& force, const glm::vec2& contact);

	const glm::vec2& getVelocity() { return m_velocity; }
	const float getAngularVelocity() { return m_angularVelocity; }

	const float getMass() { return isKinematic() ? 1000000000 : m_mass; }
	const float getAngularMass() { return isKinematic() ? 1000000000 : m_angularMass; }

	void setMass(float mass) { if (mass > 0) m_mass = mass; }
	void setAngularMass(float aMass) { if (aMass > 0) m_angularMass = aMass; }

	static float combinedElasticity(float e1, float e2);
	static float circleAngularMass(float mass, float radius);
	static float boxAngularMass(float mass, const glm::vec2& extents);

	// draw stuff for debugging
	void addDebugContactPoint(const glm::vec2& contact, const glm::vec2& normal);

protected:
	void drawDebug();

public:
	glm::vec2 position = glm::vec2(0);
	float rotation = 0;

	float linearDrag = 0.3f;
	float angularDrag = 10.0f;

	float elasticity = 0.5f;

protected:
	glm::vec2 m_velocity = glm::vec2(0);
	float m_angularVelocity = 0;

	float m_mass = 1000000000;
	float m_angularMass = 1000000000;

	// debug draw stuff
	bool m_contactDraw = false;
	glm::vec2 m_debugContact = glm::vec2(0);
	glm::vec2 m_debugCollNorm = glm::vec2(0);
};