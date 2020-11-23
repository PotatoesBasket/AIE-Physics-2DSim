#pragma once
#include "Rigidbody.h"

class Box : public Rigidbody
{
public:
	Box();
	Box(const glm::vec2& position, float rotation, float mass, glm::vec2 extents, const glm::vec4& color,
		const glm::vec2& initialVelocity = glm::vec2(0), float initialRotVel = 0);
	~Box() {}

	void fixedUpdate(float fixedTimeStep, const glm::vec2& gravity) override;
	void draw() override;

	bool checkCorners(const Box& other, glm::vec2& contact, int& noOfContacts, float& penetration, glm::vec2& edgeNormal);

protected:
	void updateLocalAxes();

public:
	glm::vec2 extents;
	glm::vec4 color;

	glm::vec2 localX = glm::vec2(0);
	glm::vec2 localY = glm::vec2(0);
};