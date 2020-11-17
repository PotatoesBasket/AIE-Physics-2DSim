#include "Analytic.h"

Analytic::Analytic(glm::vec2 gravity, glm::vec2 initPos, glm::vec2 initVel, float startTime, float endTime, float fixedDeltaTime, glm::vec4 color) : m_gravity(gravity), m_initPos(initPos), m_initVel(initVel), m_color(color)
{
	m_samples.reserve(20);
	for (; startTime < endTime; startTime += fixedDeltaTime)
		m_samples.push_back(analyze(startTime));
}

void Analytic::draw()
{
	for (int i = 1; i < m_samples.size(); ++i)
	{
		auto beg = m_samples[i - 1];
		auto end = m_samples[i];
		aie::Gizmos::add2DLine(beg, end, glm::vec4(1, 0, 0, 1));
	}
}

glm::vec2 Analytic::analyze(float t)
{
	float x = m_initPos.x + m_initVel.x * t;
	float y = m_initPos.y + m_initVel.y * t + m_gravity.y * 0.5f * t * t;
	return glm::vec2(x, y);
}

Integrator::Integrator(Rigidbody* body, glm::vec2 gravity, float startTime, float endTime, float fixedDeltaTime, glm::vec4 color) : m_body(body), m_gravity(gravity), m_fixedDeltaTime(fixedDeltaTime), m_color(color)
{
	m_samples.reserve(20);
	for (; startTime < endTime; startTime += fixedDeltaTime)
		m_samples.push_back(analyze());
}

void Integrator::draw()
{
	for (int i = 1; i < m_samples.size(); ++i)
	{
		auto beg = m_samples[i - 1];
		auto end = m_samples[i];
		aie::Gizmos::add2DLine(beg, end, m_color);
	}
}

glm::vec2 Integrator::analyze()
{
	glm::vec2 pos = m_body->position;
	m_body->fixedUpdate(m_fixedDeltaTime, m_gravity);

	return pos;
}