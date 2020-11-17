#include "SpringsApp.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include <Gizmos.h>
#include "Analytic.h"

bool SpringsApp::startup()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	m_input = aie::Input::getInstance();
	m_renderer = std::make_unique<aie::Renderer2D>();

	ball2.isKinematic = true;

	m_scene.addActor(&ball1);
	m_scene.addActor(&ball2);
	m_scene.addActor(&spring);

	return true;
}

void SpringsApp::shutdown()
{
	aie::Gizmos::destroy();
}

void SpringsApp::update(float deltaTime)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	static int mouseX;
	static int mouseY;

	m_input->getMouseXY(&mouseX, &mouseY);

	ball2.position = glm::vec2(mouseX - getWindowWidth() * 0.5f, mouseY - getWindowHeight() * 0.5f);

	m_scene.fixedUpdate(deltaTime);
}

void SpringsApp::draw()
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