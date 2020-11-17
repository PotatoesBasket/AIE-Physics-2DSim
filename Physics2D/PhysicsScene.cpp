#include "PhysicsScene.h"

#include <list>
#include <algorithm>

#include "Plane.h"
#include "Circle.h"
#include "Box.h"

void PhysicsScene::fixedUpdate(float deltaTime)
{
	// update on fixed timescale
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= timeStep)
	{
		checkForCollision();

		for (auto& object : m_actors)
		{
			object->fixedUpdate(timeStep, gravity);
		}

		accumulatedTime -= timeStep;
	}
}

void PhysicsScene::draw()
{
	for (auto actor : m_actors)
	{
		actor->draw();
	}
}

void PhysicsScene::addActor(PhysicsObject* actor)
{
	m_actors.push_back(actor);
}

void PhysicsScene::removeActor(PhysicsObject* actor)
{
	m_pendingRemovals.push_back(actor);
}

void PhysicsScene::processPendingRemovals()
{
	auto it = m_actors.end();

	// move pending removals to the end of the vector
	for (auto actor : m_pendingRemovals)
	{
		auto i = std::remove(m_actors.begin(), m_actors.end(), actor);

		if (i != m_actors.end())
			it = i;
	}

	// erase the chunk of pending removals off the end of the vector
	m_actors.erase(it, m_actors.end());
	m_pendingRemovals.clear();
}

#pragma region Collisions

typedef bool (*CollisionFunc)(PhysicsObject*, PhysicsObject*);

static CollisionFunc collisionFuncArray[] =
{
	//plane						//circle						//aabb
	PhysicsScene::plane2Plane,	PhysicsScene::plane2Circle,		PhysicsScene::plane2AABB,	//plane
	PhysicsScene::circle2Plane,	PhysicsScene::circle2Circle,	PhysicsScene::circle2AABB,	//circle
	PhysicsScene::AABB2Plane,	PhysicsScene::AABB2Circle,		PhysicsScene::AABB2AABB		//aabb
};

void PhysicsScene::checkForCollision()
{
	int actorCount = m_actors.size();

	for (int outer = 0; outer < actorCount - 1; ++outer)
	{
		for (int inner = outer + 1; inner < actorCount; ++inner)
		{
			PhysicsObject* obj1 = m_actors[outer];
			PhysicsObject* obj2 = m_actors[inner];
			int shapeID1 = (int)obj1->getShapeType();
			int shapeID2 = (int)obj2->getShapeType();

			if (shapeID1 < 0 || shapeID2 < 0)
				continue;

			int funcIdx = (shapeID1 * (int)ShapeType::COUNT) + shapeID2;
			CollisionFunc func = collisionFuncArray[funcIdx];

			if (func != nullptr)
				func(obj1, obj2);
		}
	}
}

bool PhysicsScene::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// this is just to fill out the matrix i guess
	return false;
}

bool PhysicsScene::plane2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Circle* circle = dynamic_cast<Circle*>(obj2);

	if (plane != nullptr && circle != nullptr)
	{
		// collision detection
		glm::vec2 collisionNormal = plane->normal;
		float circleToPlane = glm::dot(circle->position, collisionNormal) - plane->distance;

		//if (circleToPlane < 0) // if circle is behind plane, flip normal
		//{
		//	collisionNormal *= -1;
		//	circleToPlane *= -1;
		//}

		float intersection = circle->radius - circleToPlane;

		// collision resolution
		if (intersection > 0)
		{
			// calculate force
			float elasticity = combinedElasticity(1.0f, circle->elasticity);

			glm::vec2 forceVector = -1 * circle->mass * collisionNormal * (glm::dot(collisionNormal, elasticity * circle->getVelocity()));
			
			// separate sphere from plane
			circle->position = circle->position + collisionNormal * intersection;

			// apply force
			circle->applyForce(forceVector * 2.0f);

			return true;
		}
	}

	return false;
}

bool PhysicsScene::plane2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// TO DO
	return false;
}

bool PhysicsScene::circle2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2Circle(obj2, obj1);
}

bool PhysicsScene::circle2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Circle* circle1 = dynamic_cast<Circle*>(obj1);
	Circle* circle2 = dynamic_cast<Circle*>(obj2);

	if (circle1 != nullptr && circle2 != nullptr)
	{
		// collision detection
		glm::vec2 delta = circle2->position - circle1->position;
		float deltaDistance = glm::length(delta);

		float intersection = circle1->radius + circle2->radius - deltaDistance;

		// collision resolution
		if (intersection > 0)
		{
			// calculate force
			glm::vec2 collisionNormal = glm::normalize(delta);
			glm::vec2 relativeVelocity = circle2->getVelocity() - circle1->getVelocity();
			float elasticity = combinedElasticity(circle1->elasticity, circle2->elasticity);

			float force = glm::dot(elasticity * relativeVelocity, collisionNormal) /
				glm::dot(collisionNormal, collisionNormal * ((1 / circle1->mass) + (1 / circle2->mass)));

			glm::vec2 forceVector = force * collisionNormal;

			// move spheres out of collision
			glm::vec2 separationVector = collisionNormal * intersection * 0.5f;

			if (!circle1->isKinematic)
				circle1->position -= separationVector * (circle2->isKinematic ? 2.0f : 1.0f);

			if (!circle2->isKinematic)
				circle2->position += separationVector * (circle1->isKinematic ? 2.0f : 1.0f);

			// apply force to both
			circle1->applyForceToActors(circle2, -forceVector * 2.0f);

			return true;
		}
	}

	return false;
}

bool PhysicsScene::circle2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// TO DO
	return false;
}

bool PhysicsScene::AABB2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2AABB(obj1, obj2);
}

bool PhysicsScene::AABB2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return circle2AABB(obj1, obj2);
}

bool PhysicsScene::AABB2AABB(PhysicsObject* obj1, PhysicsObject* obj2)
{
	// TO DO
	return false;
}

#pragma endregion

float PhysicsScene::combinedElasticity(float e1, float e2)
{
	return (e1 + e2) / 2.0f;
}