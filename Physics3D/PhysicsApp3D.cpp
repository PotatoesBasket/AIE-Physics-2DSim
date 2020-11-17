#include "PhysicsApp3D.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>

bool PhysicsApp3D::startup()
{	
	m_input = aie::Input::getInstance();

	setBackgroundColour(0.25f, 0.25f, 0.25f);

	aie::Gizmos::create(10000, 10000, 10000, 10000);

	m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	return true;
}

void PhysicsApp3D::shutdown()
{
	aie::Gizmos::destroy();
}

void PhysicsApp3D::update(float deltaTime)
{
	aie::Gizmos::clear();

	// draw a simple grid with gizmos
	glm::vec4 white(1);
	glm::vec4 black(0, 0, 0, 1);

	for (int i = 0; i < 21; ++i)
	{
		aie::Gizmos::addLine(
			glm::vec3(-10 + i, 0, 10),
			glm::vec3(-10 + i, 0, -10),
			i == 10 ? white : black);

		aie::Gizmos::addLine(
			glm::vec3(10, 0, -10 + i),
			glm::vec3(-10, 0, -10 + i),
			i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	aie::Gizmos::addTransform(glm::mat4(1));

	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void PhysicsApp3D::draw()
{
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	aie::Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}