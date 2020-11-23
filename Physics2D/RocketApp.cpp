#include "RocketApp.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include <Gizmos.h>

bool RocketApp::startup()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	m_input = aie::Input::getInstance();
	m_renderer = std::make_unique<aie::Renderer2D>();

	m_scene.addActor(&m_rocket);

	for (int i = 0; i != 50; ++i)
		m_particles.push_back(new Circle(glm::vec2(-1000, -1000), 0, 1, 10, glm::vec4(0.3f, 0.3f, 0.3f, 1)));

	for (auto& particle : m_particles)
		m_scene.addActor(particle);

	m_it = m_particles.begin();

	return true;
}

void RocketApp::shutdown()
{
	for (auto& particle : m_particles)
		delete particle;

	aie::Gizmos::destroy();
}

void RocketApp::update(float deltaTime)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	if (m_input->isKeyDown(aie::INPUT_KEY_UP) && m_rocket.getMass() > 1)
	{
		glm::vec2 force = glm::vec2(0, m_thrust);
		m_rocket.applyForce(force, glm::vec2(0));

		float newMass = m_rocket.getMass() - m_fuel;

		if (newMass > 1)
			m_rocket.setMass(newMass);
		else
			m_rocket.setMass(1);

		if (m_it == m_particles.end())
			m_it = m_particles.begin();

		(*m_it)->position = glm::vec2(m_rocket.position.x, m_rocket.position.y - m_rocket.extents.y);
		(*m_it)->applyForce(glm::vec2(0, -1), glm::vec2(0));
		++m_it;
	}

	m_scene.fixedUpdate(deltaTime);
}

void RocketApp::draw()
{
	clearScreen();
	aie::Gizmos::clear();
	m_renderer->begin();

	m_scene.draw();

	aie::Gizmos::draw2D(glm::ortho<float>(
		-(getWindowWidth() * 0.5f), getWindowWidth() * 0.5f,
		-(getWindowHeight() * 0.5f), getWindowHeight() * 0.5f,
		-1.0f, 1.0f));

	m_renderer->end();
}