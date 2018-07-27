//------------------------------------------------------------------------------
// vec2.h
//
// represents a vector in 2D with floats as elements
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: 18.07.18
//------------------------------------------------------------------------------
//

#pragma once

struct vec2 {
	float x, y;
	vec2(float const x, float const y) : x(x), y(y) {}
	vec2() : x(0), y(0) {}
};