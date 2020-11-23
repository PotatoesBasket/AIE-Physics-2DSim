#include "Box.h"
#include <Gizmos.h>

Box::Box() :
	Rigidbody(ShapeType::BOX, glm::vec2(0), 0, glm::vec2(0), 0),
	extents(glm::vec2(10)),
	color(glm::vec4(1))
{
	setMass(20);
	setAngularMass(Rigidbody::boxAngularMass(getMass(), extents));
	updateLocalAxes();
}

Box::Box(const glm::vec2& position, float rotation, float mass, glm::vec2 extents, const glm::vec4& color, const glm::vec2& initialVelocity, float initialRotVel) :
	Rigidbody(ShapeType::BOX, position, rotation, initialVelocity, initialRotVel),
	extents(extents),
	color(color)
{
	setMass(mass);
	setAngularMass(Rigidbody::boxAngularMass(getMass(), extents));
	updateLocalAxes();
}

void Box::fixedUpdate(float fixedTimeStep, const glm::vec2& gravity)
{
	Rigidbody::fixedUpdate(fixedTimeStep, gravity);
	updateLocalAxes();
}

void Box::draw()
{
	glm::vec2 p1 = position - localX * extents.x - localY * extents.y;
	glm::vec2 p2 = position + localX * extents.x - localY * extents.y;
	glm::vec2 p3 = position - localX * extents.x + localY * extents.y;
	glm::vec2 p4 = position + localX * extents.x + localY * extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, color);
	aie::Gizmos::add2DTri(p1, p4, p3, color);

	drawDebug();
}

bool Box::checkCorners(const Box& other, glm::vec2& contact, int& contactNum, float& penetration, glm::vec2& edgeNormal)
{
	float minX = 0, maxX = 0, minY = 0, maxY = 0;
	float otherWidth = other.extents.x * 2;
	float otherHeight = other.extents.y * 2;

	int noOfContacts = 0;
	glm::vec2 localContact = glm::vec2(0);

	bool first = true;
	for (float x = -other.extents.x; x < otherWidth; x += otherWidth)
	{
		for (float y = -other.extents.y; y < otherHeight; y += otherHeight)
		{
			// other box corner pos relative to world origin
			glm::vec2 worldPos = other.position + x * other.localX + y * other.localY;
			// other box corner pos relative to this box
			glm::vec2 relativePos = glm::vec2(
				glm::dot(worldPos - position, localX),
				glm::dot(worldPos - position, localY));

			if (first || relativePos.x < minX)
				minX = relativePos.x;
			if (first || relativePos.x > maxX)
				maxX = relativePos.x;
			if (first || relativePos.y < minY)
				minY = relativePos.y;
			if (first || relativePos.y > maxY)
				maxY = relativePos.y;

			if (relativePos.x >= -extents.x && relativePos.x <= extents.x &&
				relativePos.y >= -extents.y && relativePos.y <= extents.y)
			{
				++contactNum;
				localContact += relativePos;
			}

			first = false;
		}
	}

	if (maxX < -extents.x || minX > extents.x ||
		maxY < -extents.y || minY > extents.y)
		return false;

	if (contactNum == 0)
		return false;

	bool res = false;

	contact += position + (localContact.x * localX + localContact.y * localY) / (float)contactNum;
	++contactNum;

	float tempPen = extents.x - minX;
	if (tempPen > 0 && (tempPen < penetration || penetration == 0))
	{
		edgeNormal = localX;
		penetration = tempPen;
		res = true;
	}

	tempPen = maxX + extents.x;
	if (tempPen > 0 && (tempPen < penetration || penetration == 0))
	{
		edgeNormal = -localX;
		penetration = tempPen;
		res = true;
	}

	tempPen = extents.y - minY;
	if (tempPen > 0 && (tempPen < penetration || penetration == 0))
	{
		edgeNormal = localY;
		penetration = tempPen;
		res = true;
	}

	tempPen = maxY + extents.y;
	if (tempPen > 0 && (tempPen < penetration || penetration == 0))
	{
		edgeNormal = -localY;
		penetration = tempPen;
		res = true;
	}

	return res;
}

void Box::updateLocalAxes()
{
	float cs = cosf(rotation);
	float sn = sinf(rotation);
	localX = glm::normalize(glm::vec2(cs, sn));
	localY = glm::normalize(glm::vec2(-sn, cs));
}