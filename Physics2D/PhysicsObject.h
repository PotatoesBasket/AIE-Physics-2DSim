#pragma once
#include <glm/glm.hpp>

enum class ShapeType
{
	SPRING = -1,
	PLANE,
	CIRCLE,
	BOX,
	COUNT
};

class PhysicsObject
{
public:
	PhysicsObject(ShapeType type) : m_shapeType{ type } {}
	virtual ~PhysicsObject() {}

public:
	virtual void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) = 0;
	virtual void draw() = 0;

	const ShapeType getShapeType() { return m_shapeType; }

	bool isKinematic = false;

protected:
	const ShapeType m_shapeType;
};