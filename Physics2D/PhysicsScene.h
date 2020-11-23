#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;
class Rigidbody;

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

	void checkForCollisions();

public:
	float timeStep = 0.01f;
	glm::vec2 gravity = glm::vec2();

protected:
	std::vector<PhysicsObject*> m_actors;
	std::vector<PhysicsObject*> m_pendingRemovals;
};