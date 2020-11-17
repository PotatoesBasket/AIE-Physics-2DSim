#include "Camera.h"

Camera::Camera()
{
	// set defaults
	setLookAt(glm::vec3(10, 10, 10), glm::vec3(0), glm::vec3(0, 1, 0));
	setPerspective(glm::quarter_pi<float>(), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

void Camera::setPerspective(float FOV, float aspectRatio, float near, float far)
{
	m_projectionTransform = glm::perspective(FOV, aspectRatio, near, far);
	updateProjectionViewTransform();
}

void Camera::setLookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up)
{
	m_viewTransform = glm::lookAt(from, to, up);
	m_worldTransform = glm::inverse(m_viewTransform);
	updateProjectionViewTransform();
}

void Camera::setPosition(const glm::vec3& position)
{
	m_worldTransform[3] = glm::vec4(position, 1);
	m_viewTransform = glm::inverse(m_worldTransform);
	updateProjectionViewTransform();
}

void Camera::setView(const glm::mat4& matrix)
{
	m_worldTransform = glm::translate(getPosition()) * matrix;
	m_viewTransform = glm::inverse(m_worldTransform);
	updateProjectionViewTransform();
}

void Camera::setRotation(const glm::vec3& axis, float radians)
{
	m_viewTransform = glm::rotate(m_viewTransform, radians, axis);
	m_worldTransform = glm::inverse(m_viewTransform);
	updateProjectionViewTransform();
}

void Camera::updateProjectionViewTransform()
{
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}

void Camera::updateFrustumPlanes(Frustum frustum)
{
	glm::mat4 t = m_projectionViewTransform;

	frustum.right = glm::vec4(
		t[0][3] - t[0][0],
		t[1][3] - t[1][0],
		t[2][3] - t[2][0],
		t[3][3] - t[3][0]);

	frustum.left = glm::vec4(
		t[0][3] + t[0][0],
		t[1][3] + t[1][0],
		t[2][3] + t[2][0],
		t[3][3] + t[3][0]);

	frustum.top = glm::vec4(
		t[0][3] - t[0][1],
		t[1][3] - t[1][1],
		t[2][3] - t[2][1],
		t[3][3] - t[3][1]);

	frustum.bottom = glm::vec4(
		t[0][3] + t[0][1],
		t[1][3] + t[1][1],
		t[2][3] + t[2][1],
		t[3][3] + t[3][1]);

	frustum.farPlane = glm::vec4(
		t[0][3] - t[0][2],
		t[1][3] - t[1][2],
		t[2][3] - t[2][2],
		t[3][3] - t[3][2]);

	frustum.nearPlane = glm::vec4(
		t[0][3] + t[0][2],
		t[1][3] + t[1][2],
		t[2][3] + t[2][2],
		t[3][3] + t[3][2]);

	// normalise planes
	for (int i = 0; i < 6; ++i)
	{
		float length = glm::length(frustum.planes[i].normal);
		frustum.planes[i].normal /= length;
	}
}