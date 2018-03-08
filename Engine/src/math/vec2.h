#pragma once

struct vec2 {
	float x, y;
	vec2(float const x, float const y) : x(x), y(y) {}
	vec2() : x(0), y(0) {}
};