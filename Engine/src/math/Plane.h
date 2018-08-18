//------------------------------------------------------------------------------
// File Name: Plane.h
// Description: Represents a mathematical plane
//
// Author: Sommerauer Christian
// Created: 18.08.2018
// Changed: 18.08.2018
//------------------------------------------------------------------------------
//



#pragma once

#include <math\Vec3.h>


namespace engine {

	class Plane
	{
	public:
		Plane();
		Plane(const Vec3& v1, const Vec3& v2, const Vec3& v3);
		
		F32 distance(const Vec3& p) const;
		void setPoints(const Vec3& v1, const Vec3& v2, const Vec3& v3);
		Vec3 point;
		Vec3 normal;
		F32 d;

	private:
	};

}