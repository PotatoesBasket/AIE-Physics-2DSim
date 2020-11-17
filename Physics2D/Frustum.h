#pragma once
#include "FrustumPlane.h"

class Frustum
{
public:
	Frustum() {}
	~Frustum() {}

	union
	{
		struct
		{
			FrustumPlane right, left;
			FrustumPlane top, bottom;
			FrustumPlane farPlane, nearPlane;
		};

		FrustumPlane planes[6];
	};
};