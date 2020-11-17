#include "RigidBody.h"
#include <glm/glm.hpp>
#include <exception>

static float MIN_LINEAR_THRESHOLD = 0.1f;

Rigidbody::Rigidbody(ShapeType type, const glm::vec2& position, float mass, const glm::vec2& initialVelocity) :
	PhysicsObject(type), position(position), mass(mass), m_velocity(initialVelocity)
{
	if (mass <= 0)
		throw std::exception("A rigidbody's mass cannot be <= 0");
}

void Rigidbody::fixedUpdate(float fixedTimeStep, const glm::vec2& gravity)
{
	if (isKinematic)
	{
		m_velocity = glm::vec2(0);
		return;
	}

	m_velocity -= m_velocity * linearDrag * fixedTimeStep;

	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
		m_velocity = glm::vec2(0);

	applyForce(gravity * mass * fixedTimeStep);
	position += m_velocity * fixedTimeStep;
}

void Rigidbody::applyForce(const glm::vec2& force)
{
	glm::vec2 acceleration = force / mass;
	m_velocity += acceleration;
}

void Rigidbody::applyForceToActors(Rigidbody* other, const glm::vec2& force)
{
	other->applyForce(force);
	applyForce(-force);
}