#pragma once
#include "Rigidbody.h"

class Box : public Rigidbody
{
public:
	Box(const glm::vec2& position, float mass, float width, float height, const glm::vec4& color, const glm::vec2& initialVelocity = glm::vec2(0));
	~Box() {}

	void draw() override;

	float getWidth() { return m_width; }
	float getHeight() { return m_height; }

public:
	glm::vec4 color;

protected:
	float m_width;
	float m_height;
};