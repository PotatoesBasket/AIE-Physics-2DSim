#include "Spring.h"
#include <Gizmos.h>
#include <iostream>

Spring::Spring(Rigidbody* body1, Rigidbody* body2, float springyness, float damping, float restLength) : PhysicsObject(ShapeType::SPRING)
{
	this->body1 = body1;
	this->body2 = body2;
	springCoefficient = springyness;
	this->damping = damping;
	this->restLength = restLength;
}

void Spring::fixedUpdate(float fixedTimeStep, const glm::vec2& gravity)
{
	if (isBroken)
		return;

	if (snapped())
		isBroken = true;

	float length = getDistance();
	const glm::vec2 springVec = glm::normalize(body2->position - body1->position);
	
	// force = -springyness * distance from rest position - damper * relative velocity
	// (F = -kx - bv)

	const float x = restLength - length;
	const glm::vec2 v = body2->getVelocity() - body2->getVelocity();

	glm::vec2 force = springVec * springCoefficient * x - damping * v;

	body1->applyForce(-force * fixedTimeStep, glm::vec2(0));
	body2->applyForce(force * fixedTimeStep, glm::vec2(0));
}

void Spring::draw()
{
	if (isBroken || noOfPoints == 0 || width <= 0)
		return; // don't draw springs that are broken or have invalid draw info

	glm::vec2 springVec = body2->position - body1->position;
	glm::vec2 springDiv = springVec / (float)noOfPoints;
	glm::vec2 prevPoint = body1->position;

	for (int i = 1; i <= noOfPoints; ++i)
	{
		glm::vec2 direction = i % 2 == 0 ?
			glm::normalize(glm::vec2(-springDiv.y, springDiv.x)) :
			glm::normalize(glm::vec2(springDiv.y, -springDiv.x));

		glm::vec2 nextPoint = body1->position + springDiv * (float)i + direction * width;

		if (i == noOfPoints)
			nextPoint = body2->position;

		aie::Gizmos::add2DLine(prevPoint, nextPoint, color);

		prevPoint = nextPoint;
	}
}

bool Spring::snapped() const
{
	if (getDistance() / restLength < breakForce)
		return true;

	return false;
}