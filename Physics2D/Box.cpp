#include "Box.h"
#include <Gizmos.h>

Box::Box(const glm::vec2& position, float mass, float width, float height, const glm::vec4& color, const glm::vec2& initialVelocity) :
	Rigidbody(ShapeType::BOX, position, mass, initialVelocity), m_width(width), m_height(height), color(color) {}

void Box::draw()
{
	aie::Gizmos::add2DAABBFilled(position, glm::vec2(m_width * 0.5f, m_height * 0.5f), color);
}

//bool Box::checkCollision(PhysicsObject* other)
//{
//	if (other->getShapeType() == ShapeType::BOX)
//	{
//		Box* box = static_cast<Box*>(other);
//
//		return !(m_position.x + (m_width * 0.5f) < box->getPosition().x - (box->getWidth() * 0.5f) ||
//			m_position.y + (m_height * 0.5f) < box->getPosition().y - (box->getHeight() * 0.5f) ||
//			m_position.x - (m_width * 0.5f) > box->getPosition().x + (box->getHeight() * 0.5f) ||
//			m_position.y - (m_height * 0.5f) > box->getPosition().y + (box->getHeight() * 0.5f));
//	}
//
//	return false;
//}