#pragma once
#include <Application.h>
#include <Input.h>
#include <Renderer2D.h>
#include <memory>
#include <vector>
#include "PhysicsScene.h"
#include "Spring.h"
#include "Plane.h"
#include "Circle.h"

class BallsInABoxApp : public aie::Application
{
public:
	BallsInABoxApp() {}
	~BallsInABoxApp() {}

	bool startup() override;
	void shutdown() override;

	void update(float deltaTime) override;
	void draw() override;

protected:
	aie::Input* m_input = nullptr;
	std::unique_ptr<aie::Renderer2D> m_renderer;

	PhysicsScene m_scene = PhysicsScene(glm::vec2(0, -500));

	Circle m_ball1 = Circle(glm::vec2(-100, 300),	50, 40, glm::vec4(1, 0, 0, 1));
	Circle m_ball2 = Circle(glm::vec2(100, 300),	50, 40, glm::vec4(0, 1, 0, 1));
	Circle m_ball3 = Circle(glm::vec2(-250, 300),	50, 40, glm::vec4(1, 0, 1, 1));
	Circle m_ball4 = Circle(glm::vec2(250, 300),	50, 40, glm::vec4(0, 0, 1, 1));
	Circle m_ball5 = Circle(glm::vec2(-400, 300),	50, 40, glm::vec4(1, 1, 0, 1));
	Circle m_ball6 = Circle(glm::vec2(400, 300),	50, 40, glm::vec4(0, 1, 1, 1));

	Circle m_ball7 = Circle(glm::vec2(0, 0),		20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball8 = Circle(glm::vec2(-50, 10),		20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball9 = Circle(glm::vec2(-100, 20),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball10 = Circle(glm::vec2(-150, 30),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball11 = Circle(glm::vec2(-200, 40),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball12 = Circle(glm::vec2(-250, 50),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball13 = Circle(glm::vec2(-300, 60),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball14 = Circle(glm::vec2(50, 10),		20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball15 = Circle(glm::vec2(100, 20),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball16 = Circle(glm::vec2(150, 30),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball17 = Circle(glm::vec2(200, 40),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball18 = Circle(glm::vec2(250, 50),	20, 10, glm::vec4(1, 1, 1, 1));
	Circle m_ball19 = Circle(glm::vec2(300, 60),	20, 10, glm::vec4(1, 1, 1, 1));

	// mid to right
	Spring m_spring1 = Spring(&m_ball7, &m_ball8,	 3000, 200, 10);
	Spring m_spring2 = Spring(&m_ball8, &m_ball9,	 3000, 200, 10);
	Spring m_spring3 = Spring(&m_ball9, &m_ball10, 	 3000, 200, 10);
	Spring m_spring4 = Spring(&m_ball10, &m_ball11,  3000, 200, 10);
	Spring m_spring5 = Spring(&m_ball11, &m_ball12,  3000, 200, 10);
	Spring m_spring6 = Spring(&m_ball12, &m_ball13,  3000, 200, 10);
	// mid to left										
	Spring m_spring7 = Spring(&m_ball7, &m_ball14,	 3000, 200, 10);
	Spring m_spring8 = Spring(&m_ball14, &m_ball15,  3000, 200, 10);
	Spring m_spring9 = Spring(&m_ball15, &m_ball16,  3000, 200, 10);
	Spring m_spring10 = Spring(&m_ball16, &m_ball17, 3000, 200, 10);
	Spring m_spring11 = Spring(&m_ball17, &m_ball18, 3000, 200, 10);
	Spring m_spring12 = Spring(&m_ball18, &m_ball19, 3000, 200, 10);

	Plane m_plane1 = Plane(glm::vec3(0, 1, 0), -361);
	Plane m_plane2 = Plane(glm::vec3(0, -1, 0), -360);
	Plane m_plane3 = Plane(glm::vec3(1, 0, 0), -641);
	Plane m_plane4 = Plane(glm::vec3(-1, 0, 0), -640);

	float camXOffset = 0;
	float camYOffset = 0;
	float camSpeed = 500;

	bool flipGravity = false;
};