#include "PhysicsScene.h"
#include <list>
#include <algorithm>
#include "Collisions.h"
#include "PhysicsObject.h"

void PhysicsScene::fixedUpdate(float deltaTime)
{
	// update on fixed timescale
	static float accumulatedTime = 0.0f;
	accumulatedTime += deltaTime;

	while (accumulatedTime >= timeStep)
	{
		checkForCollisions();

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
	if (m_pendingRemovals.empty())
		return;

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

typedef bool (*CollisionFunc)(PhysicsObject*, PhysicsObject*);

CollisionFunc collisionFuncArray[] =
{
	//plane						//circle						//box
	Collisions::plane2Plane,	Collisions::plane2Circle,		Collisions::plane2Box,		//plane
	Collisions::circle2Plane,	Collisions::circle2Circle,		Collisions::circle2Box,		//circle
	Collisions::box2Plane,		Collisions::box2Circle,			Collisions::box2Box			//box
};

void PhysicsScene::checkForCollisions()
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

			// skip any non-rigidbody shapes (negative IDs)
			if (shapeID1 < 0 || shapeID2 < 0)
				continue;

			// skip if both objects are kinematic
			if (obj1->isKinematic() && obj2->isKinematic())
				continue;

			int funcIdx = (shapeID1 * (int)ShapeType::COUNT) + shapeID2;
			CollisionFunc func = collisionFuncArray[funcIdx];

			if (func != nullptr)
				func(obj1, obj2);
		}
	}
}