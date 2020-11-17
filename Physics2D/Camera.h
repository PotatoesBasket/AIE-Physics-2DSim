#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Frustum.h"

class Camera
{
public:
	Camera();
	~Camera() {}

	virtual void update(float deltaTime) = 0;

	void setPerspective(float FOV, float aspectRatio, float near, float far);
	void setLookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up);
	void setPosition(const glm::vec3& position);
	void setView(const glm::mat4& matrix);
	void setRotation(const glm::vec3& axis, float radians);

	const glm::mat4 getWorldTransform() const { return m_worldTransform; }
	const glm::mat4 getView() const { return m_viewTransform; }
	const glm::mat4 getProjection() const { return m_projectionTransform; }
	const glm::mat4 getProjectionView() const { return m_projectionViewTransform; }

	const glm::vec3 getRight() const { return glm::vec3(m_worldTransform[0]); }
	const glm::vec3 getUp() const { return glm::vec3(m_worldTransform[1]); }
	const glm::vec3 getForward() const { return glm::vec3(m_worldTransform[2]); }
	const glm::vec3 getPosition() const { return glm::vec3(m_worldTransform[3]); }

	const Frustum getFrustum() { updateFrustumPlanes(m_frustum); return m_frustum; }

private:
	void updateProjectionViewTransform();
	void updateFrustumPlanes(Frustum frustum);

protected:
	glm::mat4 m_worldTransform = glm::mat4(1);
	glm::mat4 m_viewTransform = glm::mat4(1);
	glm::mat4 m_projectionTransform = glm::mat4(1);
	glm::mat4 m_projectionViewTransform = glm::mat4(1);

	Frustum m_frustum;
};