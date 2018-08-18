#pragma once

#include "Plane.h"

namespace engine {

	enum EPlane : U8
	{
		TOP = 0,
		BOTTOM = 1,
		LEFT = 2,
		RIGHT = 3,
		NEAR = 4,
		FAR = 5
	};

	enum class EPlacement : U8 
	{ 
		OUTSIDE, 
		INTERSECT, 
		INSIDE 
	};
	
	class Frustum
	{
	public:
		F32 m_Fov;
		F32 m_AspectRatio;
		F32 m_Near;
		F32 m_Far;

		Plane planes[6];

		EPlacement pointInFrustum(const Vec3& p);
		EPlacement sphereInFrustum(const Vec3& p, const F32& radius);
	};

}