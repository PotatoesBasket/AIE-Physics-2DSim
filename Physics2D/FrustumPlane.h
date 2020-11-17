#pragma once
#include <glm/glm.hpp>

class FrustumPlane
{
public:
	FrustumPlane() : normal(0), dist(0) {}
	FrustumPlane(float normalX, float normalY, float normalZ, float dist) :
		normal(glm::vec3(normalX, normalY, normalZ)), dist(dist) {}
	FrustumPlane(glm::vec3 normal, float dist) : normal(normal), dist(dist) {}
	FrustumPlane(glm::vec4 plane) : normal(plane), dist(plane.w) {}
	~FrustumPlane() {}

public:
	glm::vec3 normal;
	float dist; //distance from world center
};