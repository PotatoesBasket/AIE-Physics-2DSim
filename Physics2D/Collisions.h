#pragma once
#include <glm/glm.hpp>

class PhysicsObject;
class Rigidbody;

static class Collisions
{
public:
	static bool plane2Plane(PhysicsObject* plane1, PhysicsObject* plane2);
	static bool plane2Circle(PhysicsObject* plane, PhysicsObject* circle);
	static bool plane2Box(PhysicsObject* plane, PhysicsObject* box);
	static bool circle2Plane(PhysicsObject* circle, PhysicsObject* plane);
	static bool circle2Circle(PhysicsObject* circle1, PhysicsObject* circle2);
	static bool circle2Box(PhysicsObject* circle, PhysicsObject* box);
	static bool box2Plane(PhysicsObject* box, PhysicsObject* plane);
	static bool box2Circle(PhysicsObject* box, PhysicsObject* circle);
	static bool box2Box(PhysicsObject* box1, PhysicsObject* box2);
	static void applyContactForces(Rigidbody* body1, Rigidbody* body2, const glm::vec2& norm, float pen);
};