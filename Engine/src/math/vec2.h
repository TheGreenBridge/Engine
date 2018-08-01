//------------------------------------------------------------------------------
// Vec2.h
//
// represents a vector in 2D with floats as elements
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

struct Vec2 {
	F32 x, y;
	Vec2(float const x, float const y) : x(x), y(y) {}
	Vec2() : x(0), y(0) {}
}; 
