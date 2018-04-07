#pragma once

#include "vec2.h"
#include "Vec3.h"

struct vertex {
	vertex(Vec3 position, Vec3 normal, vec2 uv)
		:position(position), normal(normal), uv(uv) {}

	vertex() : position(0, 0, 0), normal(0, 0, 0), uv(0, 0) {}

	Vec3 position;
	Vec3 normal;
	vec2 uv;
};