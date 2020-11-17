#include "BlankApp.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include <Gizmos.h>
#include "Analytic.h"

bool BlankApp::startup()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	m_input = aie::Input::getInstance();
	m_renderer = std::make_unique<aie::Renderer2D>();

	return true;
}

void BlankApp::shutdown()
{
	aie::Gizmos::destroy();
}

void BlankApp::update(float deltaTime)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	m_scene.fixedUpdate(deltaTime);
}

void BlankApp::draw()
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