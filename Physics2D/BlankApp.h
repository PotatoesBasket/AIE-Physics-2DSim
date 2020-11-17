#pragma once
#include <Application.h>
#include <Input.h>
#include <Renderer2D.h>
#include <memory>
#include <vector>
#include "PhysicsScene.h"

class BlankApp : public aie::Application
{
public:
	BlankApp() {}
	~BlankApp() {}

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:
	aie::Input* m_input = nullptr;
	std::unique_ptr<aie::Renderer2D> m_renderer;

	PhysicsScene m_scene = PhysicsScene(glm::vec2(0, -500));
};