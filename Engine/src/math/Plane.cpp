//------------------------------------------------------------------------------
// File Name: Plane.cpp
// Description: Implementation of the plane
//
// Author: Sommerauer Christian
// Created: 18.08.2018
// Changed: 18.08.2018
//------------------------------------------------------------------------------
//


#include "Plane.h"

namespace engine {

	Plane::Plane()
	{

	}

	Plane::Plane(const Vec3 & v1, const Vec3 & v2, const Vec3 & v3)
	{
		setPoints(v1, v2, v3);
	}

	void Plane::setPoints(const Vec3 & v1, const Vec3 & v2, const Vec3 & v3)
	{
		Vec3 aux1, aux2;

		aux1 = v1 - v2;
		aux2 = v3 - v2;

		normal = Vec3::crossProduct(aux2, aux1);

		normal.normalize();
		point = v2;
		d = -Vec3::dotProduct(normal, point);
	}

	F32 Plane::distance(const Vec3 & p) const
	{
		return (d + Vec3::dotProduct(normal, p));
	}
}