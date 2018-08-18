//------------------------------------------------------------------------------
// File Name: Frustum.cpp
// Description: Implements the frustum
//
// Author: Sommerauer Christian
// Created: 18.08.2018
// Changed: 18.08.2018
//------------------------------------------------------------------------------
//

#include "Frustum.h"
#include <utils\Log.h>

namespace engine {

	EPlacement Frustum::pointInFrustum(const Vec3 & p)
	{
		EPlacement result = EPlacement::INSIDE;
		for (int i = 0; i < 6; i++) {
			if (planes[i].distance(p) < 0)
			{
				return EPlacement::OUTSIDE;
			}
		}
		return result;
	}

	EPlacement Frustum::sphereInFrustum(const Vec3 & p, const F32 & radius)
	{
		EPlacement result = EPlacement::INSIDE;
		float distance;

		for (int i = 0; i < 6; i++) {
			distance = planes[i].distance(p);
			if (distance < -radius)
				return EPlacement::OUTSIDE;
			else if (distance < radius)
				result = EPlacement::INTERSECT;
		}
		return(result);
	}
}
