#pragma once
#include <glm/glm.hpp>
#include "PhysicsObject.h"

class Plane : public PhysicsObject
{
public:
	Plane() : normal(0), distance(0), PhysicsObject(ShapeType::PLANE) {}
	Plane(float normalX, float normalY, float normalZ, float dist) :
		normal(glm::vec3(normalX, normalY, normalZ)), distance(dist), PhysicsObject(ShapeType::PLANE) {}
	Plane(glm::vec3 normal, float dist) : normal(normal), distance(dist), PhysicsObject(ShapeType::PLANE) {}
	Plane(glm::vec4 plane) : normal(plane), distance(plane.w), PhysicsObject(ShapeType::PLANE) {}
	~Plane() {}

	void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override {}
	void draw() override;

public:
	glm::vec3 normal;
	float distance; // from world origin

	// draw info
	float visualHalfLength = 1000;
	glm::vec4 color = glm::vec4(1, 1, 1, 1);
};