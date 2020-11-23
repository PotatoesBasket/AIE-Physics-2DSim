#include "Plane.h"
#include <Gizmos.h>

Plane::Plane() :
	Rigidbody(ShapeType::PLANE, glm::vec2(0), 0),
	normal(0),
	distance(0)
{
	m_isKinematic = true;
}

Plane::Plane(glm::vec2 normal, float dist) :
	Rigidbody(ShapeType::PLANE, glm::vec2(0), 0),
	normal(normal),
	distance(dist)
{
	m_isKinematic = true;
}

void Plane::draw()
{
	glm::vec2 centerPoint = normal * distance;
	glm::vec2 parallel = glm::vec2(normal.y, -normal.x);
	glm::vec2 startPoint = centerPoint + (parallel * visualHalfLength);
	glm::vec2 endPoint = centerPoint - (parallel * visualHalfLength);

	aie::Gizmos::add2DLine(startPoint, endPoint, color);
}

void Plane::resolveCollision(Rigidbody* other, const glm::vec2& contact, glm::vec2* collisionNormal)
{
	glm::vec2 collNormal = collisionNormal ? *collisionNormal : normal;

	// calculate force
	float e = Rigidbody::combinedElasticity(elasticity, other->elasticity);

	glm::vec2 forceVector = -1 * other->getMass() * collNormal * (glm::dot(e * other->getVelocity(), collNormal));

	// apply force
	other->applyForce(forceVector, contact - other->position);
}