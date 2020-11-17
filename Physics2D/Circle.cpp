#include "Circle.h"
#include <Gizmos.h>

Circle::Circle(const glm::vec2& position, float mass, float radius, const glm::vec4& color, const glm::vec2& initialVelocity) :
	Rigidbody(ShapeType::CIRCLE, position, mass, initialVelocity), radius(radius), color(color) {}

void Circle::draw()
{
	aie::Gizmos::add2DCircle(position, radius, 32, color);
}