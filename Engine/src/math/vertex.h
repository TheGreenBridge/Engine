#pragma once

#include "vec2.h"
#include "vec3.h"

struct vertex {
	vertex(vec3 position, vec3 normal, vec2 uv)
		:position(position), normal(normal), uv(uv) {}

	vertex() : position(0, 0, 0), normal(0, 0, 0), uv(0, 0) {}

	vec3 position;
	vec3 normal;
	vec2 uv;
};