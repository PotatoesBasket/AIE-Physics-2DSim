#include "Plane.h"
#include <Gizmos.h>

void Plane::draw()
{
	glm::vec2 centerPoint = normal * distance;
	glm::vec2 parallel = glm::vec2(normal.y, -normal.x);
	glm::vec2 startPoint = centerPoint + (parallel * visualHalfLength);
	glm::vec2 endPoint = centerPoint - (parallel * visualHalfLength);

	aie::Gizmos::add2DLine(startPoint, endPoint, color);
}