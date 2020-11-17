#include "FlyCamera.h"

void FlyCamera::update(float deltaTime)
{
	//right (pan)
	if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		glm::vec3 pos = getPosition() + getRight() * m_speed * deltaTime;
		setPosition(pos);
	}
	//left (pan)
	if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		glm::vec3 pos = getPosition() + getRight() * -m_speed * deltaTime;
		setPosition(pos);
	}

	//up (pan)
	if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		glm::vec3 pos = getPosition() + getUp() * m_speed * deltaTime;
		setPosition(pos);
	}
	//down (pan)
	if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		glm::vec3 pos = getPosition() + getUp() * -m_speed * deltaTime;
		setPosition(pos);
	}

	////backward (zoom)
	//if (glfwGetKey(m_window, GLFW_KEY_Q) == GLFW_PRESS)
	//{
	//	glm::vec3 pos = getPosition() + getForward() * m_speed * deltaTime;
	//	setPosition(pos);
	//}
	////forward (zoom)
	//if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
	//{
	//	glm::vec3 pos = getPosition() + getForward() * -m_speed * deltaTime;
	//	setPosition(pos);
	//}

	////orbit up
	//if (glfwGetKey(m_window, GLFW_KEY_UP) == GLFW_PRESS)
	//{
	//	setRotation(getRight(), m_speed * deltaTime);
	//}
	////orbit down
	//if (glfwGetKey(m_window, GLFW_KEY_DOWN) == GLFW_PRESS)
	//{
	//	setRotation(getRight(), -m_speed * deltaTime);
	//}

	////orbit right
	//if (glfwGetKey(m_window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	//{
	//	setRotation(getUp(), -m_speed * deltaTime);
	//}
	////orbit left
	//if (glfwGetKey(m_window, GLFW_KEY_LEFT) == GLFW_PRESS)
	//{
	//	setRotation(getUp(), m_speed * deltaTime);
	//}
}