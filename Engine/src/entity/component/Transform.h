#pragma once

#include "../../math/Quaternion.h"
#include "../../math/Vec3.h"


struct Transform {
	Vec3 position;
	Quaternion rotation;	
	float scale;
	
	Transform(const Vec3 &position, const Quaternion &rotation, const float scale)
		: position(position), rotation(rotation), scale(scale) {}
	Transform() : position(Vec3(0,0,0)), rotation(Quaternion(0,0,0,1)), scale(1.0f) {}
};

struct TransformExt {
	Vec3 position;
	Quaternion rotation;
	Vec3 scale;

	TransformExt(const Vec3 &position, const Quaternion &rotation, const Vec3 scale)
		: position(position), rotation(rotation), scale(scale) {}
	TransformExt() : position(Vec3(0, 0, 0)), rotation(Quaternion(0, 0, 0, 1)), scale(Vec3(1.0f, 1.0f, 1.0f)) {}
};