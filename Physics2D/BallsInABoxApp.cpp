#include "BallsInABoxApp.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <Texture.h>
#include <Font.h>
#include <Input.h>
#include <Gizmos.h>

bool BallsInABoxApp::startup()
{
	aie::Gizmos::create(10000, 10000, 10000, 10000);

	m_input = aie::Input::getInstance();
	m_renderer = std::make_unique<aie::Renderer2D>();

	m_ball1.elasticity = 0.8f;
	m_ball2.elasticity = 0.8f;
	m_ball3.elasticity = 0.8f;
	m_ball4.elasticity = 0.8f;
	m_ball5.elasticity = 0.8f;
	m_ball6.elasticity = 0.8f;

	m_scene.addActor(&m_ball1);
	m_scene.addActor(&m_ball2);
	m_scene.addActor(&m_ball3);
	m_scene.addActor(&m_ball4);
	m_scene.addActor(&m_ball5);
	m_scene.addActor(&m_ball6);

	m_ball7.elasticity = 0.1f;
	m_ball8.elasticity = 0.1f;
	m_ball9.elasticity = 0.1f;
	m_ball10.elasticity = 0.1f;
	m_ball11.elasticity = 0.1f;
	m_ball12.elasticity = 0.1f;
	m_ball13.elasticity = 0.1f;
	m_ball14.elasticity = 0.1f;
	m_ball15.elasticity = 0.1f;
	m_ball16.elasticity = 0.1f;
	m_ball17.elasticity = 0.1f;
	m_ball18.elasticity = 0.1f;
	m_ball19.elasticity = 0.1f;

	m_ball13.isKinematic = true;
	m_ball19.isKinematic = true;

	m_scene.addActor(&m_ball7);
	m_scene.addActor(&m_ball8);
	m_scene.addActor(&m_ball9);
	m_scene.addActor(&m_ball10);
	m_scene.addActor(&m_ball11);
	m_scene.addActor(&m_ball12);
	m_scene.addActor(&m_ball13);
	m_scene.addActor(&m_ball14);
	m_scene.addActor(&m_ball15);
	m_scene.addActor(&m_ball16);
	m_scene.addActor(&m_ball17);
	m_scene.addActor(&m_ball18);
	m_scene.addActor(&m_ball19);

	m_spring1.width = 10;
	m_spring2.width = 10;
	m_spring3.width = 10;
	m_spring4.width = 10;
	m_spring5.width = 10;
	m_spring6.width = 10;
	m_spring7.width = 10;
	m_spring8.width = 10;
	m_spring9.width = 10;
	m_spring10.width = 10;
	m_spring11.width = 10;
	m_spring12.width = 10;

	m_scene.addActor(&m_spring1);
	m_scene.addActor(&m_spring2);
	m_scene.addActor(&m_spring3);
	m_scene.addActor(&m_spring4);
	m_scene.addActor(&m_spring5);
	m_scene.addActor(&m_spring6);
	m_scene.addActor(&m_spring7);
	m_scene.addActor(&m_spring8);
	m_scene.addActor(&m_spring9);
	m_scene.addActor(&m_spring10);
	m_scene.addActor(&m_spring11);
	m_scene.addActor(&m_spring12);

	m_scene.addActor(&m_plane1);
	m_scene.addActor(&m_plane2);
	m_scene.addActor(&m_plane3);
	m_scene.addActor(&m_plane4);

	return true;
}

void BallsInABoxApp::shutdown()
{
	aie::Gizmos::destroy();
}

void BallsInABoxApp::update(float deltaTime)
{
	if (m_input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	float xDelta = 0;
	float yDelta = 0;

	if (m_input->isKeyDown(aie::INPUT_KEY_RIGHT))
	{
		camXOffset += camSpeed * deltaTime;
		xDelta += camSpeed * deltaTime;
	}
	if (m_input->isKeyDown(aie::INPUT_KEY_LEFT))
	{
		camXOffset -= camSpeed * deltaTime;
		xDelta -= camSpeed * deltaTime;
	}
	if (m_input->isKeyDown(aie::INPUT_KEY_UP))
	{
		camYOffset += camSpeed * deltaTime;
		yDelta += camSpeed * deltaTime;
	}
	if (m_input->isKeyDown(aie::INPUT_KEY_DOWN))
	{
		camYOffset -= camSpeed * deltaTime;
		yDelta -= camSpeed * deltaTime;
	}

	if (m_input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		flipGravity = !flipGravity;
		m_scene.gravity = flipGravity ? glm::vec2(0, 500) : glm::vec2(0, -500);
	}

	m_plane1.distance += yDelta;
	m_plane2.distance -= yDelta;
	m_plane3.distance += xDelta;
	m_plane4.distance -= xDelta;

	m_scene.fixedUpdate(deltaTime);
}

void BallsInABoxApp::draw()
{
	clearScreen();
	aie::Gizmos::clear();
	m_renderer->begin();

	m_scene.draw();

	aie::Gizmos::draw2D(glm::ortho<float>(
		-(getWindowWidth() * 0.5f) + camXOffset, getWindowWidth() * 0.5f + camXOffset,
		-(getWindowHeight() * 0.5f) + camYOffset, getWindowHeight() * 0.5f + camYOffset,
		-1.0f, 1.0f));

	m_renderer->end();
}