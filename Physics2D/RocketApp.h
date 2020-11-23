#pragma once
#include <Application.h>
#include <Input.h>
#include <Renderer2D.h>
#include <memory>
#include <vector>
#include "PhysicsScene.h"
#include "Circle.h"
#include "Box.h"

class RocketApp : public aie::Application
{
public:
	RocketApp() {}
	~RocketApp() {}

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:
	aie::Input* m_input = nullptr;
	std::unique_ptr<aie::Renderer2D> m_renderer;

	PhysicsScene m_scene = PhysicsScene(glm::vec2(0, -500));

	Box m_rocket = Box(glm::vec2(0, 0), 0, 1000, glm::vec2(75, 125), glm::vec4(1, 0, 0, 1));
	std::vector<Circle*> m_particles;
	std::vector<Circle*>::iterator m_it;
	float m_thrust = 700;
	float m_fuel = 1;
};