#pragma once
#include <Application.h>
#include <Input.h>
#include <Renderer2D.h>
#include <memory>
#include <vector>
#include "PhysicsScene.h"
#include "Circle.h"
#include "Spring.h"

class SpringsApp : public aie::Application
{
public:
	SpringsApp() {}
	~SpringsApp() {}

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:
	aie::Input* m_input = nullptr;
	std::unique_ptr<aie::Renderer2D> m_renderer;

	PhysicsScene m_scene = PhysicsScene(glm::vec2(0, -500));

	Circle ball1 = Circle(glm::vec2(-250, 150), 10, 40, glm::vec4(1, 0, 1, 1));
	Circle ball2 = Circle(glm::vec2(100, 0), 10, 40, glm::vec4(0, 1, 1, 1));
	Spring spring = Spring(&ball1, &ball2, 500, 50, 200);
};