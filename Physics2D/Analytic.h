#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <Gizmos.h>
#include "Rigidbody.h"

class Analytic
{
public:
	Analytic(glm::vec2 gravity, glm::vec2 initPos, glm::vec2 initVel, float startTime, float endTime, float fixedDeltaTime, glm::vec4 color);
	~Analytic() {}

	void draw();
	glm::vec2 analyze(float time);

private:
	glm::vec2 m_gravity;
	glm::vec2 m_initPos;
	glm::vec2 m_initVel;

	glm::vec4 m_color;
	std::vector<glm::vec2> m_samples;
};

class Integrator
{
public:
	Integrator(Rigidbody* body, glm::vec2 gravity, float startTime, float endTime, float fixedDeltaTime, glm::vec4 color);
	~Integrator() {}

	void draw();
	glm::vec2 analyze();

private:
	Rigidbody* m_body;
	glm::vec2 m_gravity;
	float m_fixedDeltaTime;

	glm::vec4 m_color;
	std::vector<glm::vec2> m_samples;
};