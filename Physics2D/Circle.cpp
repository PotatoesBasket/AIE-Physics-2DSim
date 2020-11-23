#include "Circle.h"
#include <Gizmos.h>

Circle::Circle() :
	Rigidbody(ShapeType::CIRCLE, glm::vec2(0), 0, glm::vec2(0), 0),
	radius(10),
	color(glm::vec4(1))
{
	setMass(20);
	setAngularMass(Rigidbody::circleAngularMass(getMass(), radius));
}

Circle::Circle(const glm::vec2& position, float rotation, float mass, float radius, const glm::vec4& color, const glm::vec2& initialVelocity, float initialRotVel) :
	Rigidbody(ShapeType::CIRCLE, position, rotation, initialVelocity, initialRotVel),
	radius(radius),
	color(color)
{
	setMass(mass);
	setAngularMass(Rigidbody::circleAngularMass(getMass(), radius));
}

void Circle::draw()
{
	glm::vec2 end = glm::vec2(std::cos(rotation), std::sin(rotation)) * radius;
	aie::Gizmos::add2DCircle(position, radius, 32, color);
	aie::Gizmos::add2DLine(position, position + end, glm::vec4(0, 0, 0, 1));

	drawDebug();
}