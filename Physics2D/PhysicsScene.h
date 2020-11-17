#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;

class PhysicsScene
{
public:
	PhysicsScene(const glm::vec2& gravity) : gravity{ gravity } {}
	~PhysicsScene() {}

	void fixedUpdate(float deltaTime);
	void draw();

	void addActor(PhysicsObject* actor);
	void removeActor(PhysicsObject* actor);
	void processPendingRemovals();

	void checkForCollision();
	static bool plane2Plane(PhysicsObject* plane1, PhysicsObject* plane2);
	static bool plane2Circle(PhysicsObject* plane, PhysicsObject* circle);
	static bool plane2AABB(PhysicsObject* plane, PhysicsObject* AABB);
	static bool circle2Plane(PhysicsObject* circle, PhysicsObject* plane);
	static bool circle2Circle(PhysicsObject* circle1, PhysicsObject* circle2);
	static bool circle2AABB(PhysicsObject* circle, PhysicsObject* AABB);
	static bool AABB2Plane(PhysicsObject* AABB, PhysicsObject* plane);
	static bool AABB2Circle(PhysicsObject* AABB, PhysicsObject* circle);
	static bool AABB2AABB(PhysicsObject* AABB1, PhysicsObject* AABB2);

	static float combinedElasticity(float e1, float e2);

public:
	float timeStep = 0.01f;
	glm::vec2 gravity = glm::vec2();

protected:
	std::vector<PhysicsObject*> m_actors;
	std::vector<PhysicsObject*> m_pendingRemovals;
};