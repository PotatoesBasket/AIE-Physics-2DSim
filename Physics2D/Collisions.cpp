#include "Collisions.h"
#include "Plane.h"
#include "Circle.h"
#include "Box.h"

bool Collisions::plane2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return false;
}

bool Collisions::plane2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Circle* circle = dynamic_cast<Circle*>(obj2);

	if (plane != nullptr && circle != nullptr)
	{
		// collision detection
		glm::vec2 collisionNormal = plane->normal;
		float circleToPlaneNormal = glm::dot(circle->position, plane->normal) - plane->distance;

		/*	--- uncomment for planes to work from both sides
			--- comment for a stronger barrier */

		//if (circleToPlaneNormal < 0) // if circle is behind plane, flip normal
		//{
		//	collisionNormal *= -1;
		//	circleToPlaneNormal *= -1;
		//}

		/* --- */

		float intersection = circle->radius - circleToPlaneNormal;

		// collision resolution
		if (intersection > 0)
		{
			glm::vec2 contact = circle->position + (collisionNormal * -circle->radius);
			
			float elasticity = Rigidbody::combinedElasticity(plane->elasticity, circle->elasticity);

			glm::vec2 forceVector = -1 * circle->getMass() * collisionNormal * (glm::dot(collisionNormal, elasticity * circle->getVelocity()));

			// separate sphere from plane
			circle->position = circle->position + collisionNormal * intersection;

			// apply force
			//circle->applyForce(forceVector, contact);

			circle->resolveCollision(plane, contact, &-collisionNormal);

			return true;
		}
	}

	return false;
}

bool Collisions::plane2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Plane* plane = dynamic_cast<Plane*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (plane != nullptr && box != nullptr)
	{
		int noOfContacts = 0;
		glm::vec2 contact = glm::vec2(0);
		float contactVel = 0;
		float radius = 0.5f * std::fminf(box->extents.x * 2, box->extents.y * 2);
		float penetration = 0;

		// find side of plane box's centre of mass (COM) is
		glm::vec2 planePos = plane->normal * plane->distance;
		float COMToPlane = glm::dot(box->position - planePos, plane->normal);

		// check all 4 corners of box
		for (float x = -box->extents.x; x < box->extents.x * 2; x += box->extents.x * 2)
		{
			for (float y = -box->extents.y; y < box->extents.y * 2; y += box->extents.y * 2)
			{
				glm::vec2 cornerPos = box->position + x * box->localX + y * box->localY;
				float cornerToPlane = glm::dot(cornerPos - planePos, plane->normal);

				// total velocity of corner
				float velocityToPlane = glm::dot(box->getVelocity() + box->getAngularVelocity() *
					(-y * box->localX + x * box->localY), plane->normal);

				// if cornerPos is on the opposide side of plane from centerFromPlane,
				// and is still moving in, resolve the collision
				if ((cornerToPlane > 0 && COMToPlane < 0 && velocityToPlane >= 0) ||
					(cornerToPlane < 0 && COMToPlane > 0 && velocityToPlane <= 0))
				{
					++noOfContacts;
					contact += cornerPos;
					contactVel += velocityToPlane;

					if (COMToPlane >= 0)
					{
						if (penetration > cornerToPlane)
						{
							penetration = cornerToPlane;
						}
					}
					else
					{
						if (penetration < cornerToPlane)
							penetration = cornerToPlane;
					}

				}
			}
		}

		if (noOfContacts > 0)
		{
			// separate box from plane
			box->position -= plane->normal * penetration;

			// calculate force

			float e = Rigidbody::combinedElasticity(plane->elasticity, box->elasticity);
			
			// average linear + angular velocity of contact points
			float collisionVel = contactVel / (float)noOfContacts;
			
			// acceleration required to cancel out velocity going into plane
			glm::vec2 acceleration = -plane->normal * (1.0f + e * collisionVel);

			// point to apply force
			glm::vec2 localContact = (contact / (float)noOfContacts) - box->position;

			// torque = F * r
			float r = glm::dot(localContact, glm::vec2(plane->normal.y, -plane->normal.x));

			// how much point velocity will change with new force (effective mass)
			float eMass = 1.0f / (1.0f / box->getMass() + (r * r) / box->getAngularMass());

			//box->applyForce(acceleration * eMass, localContact);

			box->resolveCollision(plane, contact, &plane->normal);
		}
	}

	return false;
}

bool Collisions::circle2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2Circle(obj2, obj1);
}

bool Collisions::circle2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Circle* circle1 = dynamic_cast<Circle*>(obj1);
	Circle* circle2 = dynamic_cast<Circle*>(obj2);

	if (circle1 != nullptr && circle2 != nullptr)
	{
		glm::vec2 delta = circle2->position - circle1->position;
		float deltaDistance = glm::length(delta);

		float intersection = circle1->radius + circle2->radius - deltaDistance;

		if (intersection > 0) // collision detected
		{
			glm::vec2 contact = (circle1->position + circle2->position) * 0.5f;
			glm::vec2 collisionNormal = glm::normalize(delta);

			// separate circles
			applyContactForces(circle1, circle2, collisionNormal, intersection);

			// resolve collision
			circle1->resolveCollision(circle2, contact, &collisionNormal);

			return true;
		}
	}

	return false;
}

bool Collisions::circle2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Circle* circle = dynamic_cast<Circle*>(obj1);
	Box* box = dynamic_cast<Box*>(obj2);

	if (circle != nullptr && box != nullptr)
	{
		int noOfContacts = 0;
		glm::vec2 contact = glm::vec2(0);

		// circle pos relative to box pos
		glm::vec2 relCirclePos = circle->position - box->position;
		glm::vec2* direction = nullptr;

		// check all corners of box to see if any are in circle
		for (float x = -box->extents.x; x <= box->extents.x; x += box->extents.x * 2)
		{
			for (float y = -box->extents.y; y <= box->extents.y; y += box->extents.y * 2)
			{
				glm::vec2 cornerLocalPos = x * box->localX + y * box->localY;
				glm::vec2 cornerRelToLocalCircle = cornerLocalPos - relCirclePos;

				if (cornerRelToLocalCircle.x * cornerRelToLocalCircle.x + cornerRelToLocalCircle.y * cornerRelToLocalCircle.y <
					circle->radius * circle->radius)
				{
					++noOfContacts;
					contact += glm::vec2(x, y);
					direction = new glm::vec2(box->position - circle->position);

					if (*direction != glm::vec2(0))
						glm::normalize(*direction);
				}
			}
		}

		glm::vec2 localPos = glm::vec2(
			glm::dot(box->localX, relCirclePos),
			glm::dot(box->localY, relCirclePos));

		if (localPos.y < box->extents.y && localPos.y > -box->extents.y)
		{
			if (localPos.x > 0 && localPos.x < box->extents.x + circle->radius)
			{
				++noOfContacts;
				contact += glm::vec2(box->extents.x, localPos.y);
				direction = new glm::vec2(box->localX);
			}
			if (localPos.x < 0 && localPos.x > -(box->extents.x + circle->radius))
			{
				++noOfContacts;
				contact += glm::vec2(-box->extents.x, localPos.y);
				direction = new glm::vec2(-box->localX);
			}
		}
		if (localPos.x < box->extents.x && localPos.x > -box->extents.x)
		{
			if (localPos.y > 0 && localPos.y < box->extents.y + circle->radius)
			{
				++noOfContacts;
				contact += glm::vec2(localPos.x, box->extents.y);
				direction = new glm::vec2(box->localY);
			}
			if (localPos.y < 0 && localPos.y > -(box->extents.y + circle->radius))
			{
				++noOfContacts;
				contact += glm::vec2(localPos.x, -box->extents.y);
				direction = new glm::vec2(-box->localY);
			}
		}

		if (noOfContacts > 0)
		{
			// average contact points and convert back to world space
			contact = box->position + (1.0f / noOfContacts) * (box->localX * contact.x + box->localY * contact.y);

			// resolve collision
			box->resolveCollision(circle, contact, direction);

			// separate circle and box
			float intersection = circle->radius - glm::length(contact - circle->position);
			glm::vec2 norm = glm::normalize(circle->position - contact);

			if (direction != nullptr)
				applyContactForces(box, circle, norm, intersection);
		}

		delete direction;
	}

	return false;
}

bool Collisions::box2Plane(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return plane2Box(obj2, obj1);
}

bool Collisions::box2Circle(PhysicsObject* obj1, PhysicsObject* obj2)
{
	return circle2Box(obj2, obj1);
}

bool Collisions::box2Box(PhysicsObject* obj1, PhysicsObject* obj2)
{
	Box* box1 = dynamic_cast<Box*>(obj1);
	Box* box2 = dynamic_cast<Box*>(obj2);

	if (box1 != nullptr && box2 != nullptr)
	{
		glm::vec2 collisionNormal = glm::vec2(0);
		glm::vec contact = glm::vec2(0);
		float intersection = 0;
		int noOfContacts = 0;

		glm::vec2 relativePos = box2->position - box1->position;

		box1->checkCorners(*box2, contact, noOfContacts, intersection, collisionNormal);

		if (box2->checkCorners(*box1, contact, noOfContacts, intersection, collisionNormal))
			collisionNormal = -collisionNormal;

		if (intersection > 0)
		{
			applyContactForces(box1, box2, collisionNormal, intersection);
			box1->resolveCollision(box2, contact, &collisionNormal);
		}
		
		return true;
	}

	return false;
}

void Collisions::applyContactForces(Rigidbody* body1, Rigidbody* body2, const glm::vec2& norm, float pen)
{
	float separation = body1->isKinematic() ?
		(body2->isKinematic() ? 0.0f : 1.0f) : (body2->isKinematic() ? 1.0f : 0.5f);

	if (!body1->isKinematic()) body1->position -= separation * norm * pen;
	if (!body2->isKinematic()) body2->position += separation * norm * pen;
}