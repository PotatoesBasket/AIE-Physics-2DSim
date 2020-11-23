#include "RigidBody.h"
#include <glm/glm.hpp>
#include <Gizmos.h>
#include <iostream>

static float MIN_LINEAR_THRESHOLD = 0.1f;
static float MIN_ROTATION_THRESHOLD = 0.01f;

Rigidbody::Rigidbody(ShapeType type, const glm::vec2& position, float rotation, const glm::vec2& initialVelocity, float initialRotVel) :
	PhysicsObject(type), position(position), rotation(rotation), m_velocity(initialVelocity), m_angularVelocity(initialRotVel) {}

void Rigidbody::fixedUpdate(float fixedTimeStep, const glm::vec2& gravity)
{
	if (isKinematic())
	{
		m_velocity = glm::vec2(0);
		m_angularVelocity = 0;
		return;
	}

	// apply gravity
	m_velocity += gravity * fixedTimeStep;

	// update position and rotation
	position += m_velocity * fixedTimeStep;
	rotation += m_angularVelocity * fixedTimeStep;

	// apply drag
	m_velocity -= m_velocity * linearDrag * fixedTimeStep;
	m_angularVelocity -= m_angularVelocity * angularDrag * fixedTimeStep;

	// cancel out values that are too small
	if (glm::length(m_velocity) < MIN_LINEAR_THRESHOLD)
		m_velocity = glm::vec2(0);

	if (glm::abs(m_angularVelocity) < MIN_ROTATION_THRESHOLD)
		m_angularVelocity = 0;
}

void Rigidbody::resolveCollision(Rigidbody* other, const glm::vec2& contact, glm::vec2* collisionNormal)
{
	glm::vec2 normal = collisionNormal ? *collisionNormal : other->position - position;

	if (glm::length(normal) < 0.1f)
		return;

	normal = glm::normalize(normal);

	// calculate if bodies are moving into each other
	glm::vec2 perp = glm::vec2(normal.y, -normal.x);

	float r1 = glm::dot(contact - position, -perp);
	float r2 = glm::dot(contact - other->position, perp);

	float v1 = glm::dot(m_velocity, normal) - r1 * getAngularVelocity();
	float v2 = glm::dot(other->m_velocity, normal) + r2 * other->getAngularVelocity();

	if (v1 > v2) // they are, calculate and apply force
	{
		float mass1 = 1.0f / (1.0f / getMass() + (r1 * r1) / getAngularMass());
		float mass2 = 1.0f / (1.0f / other->getMass() + (r2 * r2) / other->getAngularMass());

		float e = Rigidbody::combinedElasticity(elasticity, other->elasticity);

		glm::vec2 force = (1.0f + e) * mass1 * mass2 / (mass1 + mass2) * (v1 - v2) * normal;

		// apply force to both
		if (!isKinematic())
		{
			applyForce(-force, contact - position);
			addDebugContactPoint(contact, -force);
		}
		if (!other->isKinematic())
		{
			other->applyForce(force, contact - other->position);
			other->addDebugContactPoint(contact, force);
		}
	}
}

void Rigidbody::applyForce(const glm::vec2& force, const glm::vec2& contact)
{
	m_velocity += force / getMass();
	m_angularVelocity += (force.y * contact.x - force.x * contact.y) / getAngularMass();
}

float Rigidbody::combinedElasticity(float e1, float e2)
{
	return (e1 + e2) / 2.0f;
}

float Rigidbody::circleAngularMass(float mass, float radius)
{
	return 0.5f * mass * radius * radius;
}

float Rigidbody::boxAngularMass(float mass, const glm::vec2& extents)
{
	return 1.0f / 12.0f * mass * (extents.x * 2) * (extents.y * 2);
}

void Rigidbody::addDebugContactPoint(const glm::vec2& contact, const glm::vec2& normal)
{
	m_contactDraw = true;
	m_debugContact = contact;
	m_debugCollNorm = normal;
}

void Rigidbody::drawDebug()
{
	if (m_contactDraw == true)
	{
		aie::Gizmos::add2DCircle(m_debugContact, 5, 12, glm::vec4(1, 0, 0, 1));
		aie::Gizmos::add2DLine(m_debugContact, m_debugCollNorm + m_debugContact, glm::vec4(0, 0, 1, 1));
		m_contactDraw = false;
	}
}