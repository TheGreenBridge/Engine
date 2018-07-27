//------------------------------------------------------------------------------
// iVec2.h
//
// represents a vector in 2D with integers as elements
//
// Author: Sumi
// Created: 18.07.18
// Changed: 18.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

struct iVec2 {
	U32 x, y;
	iVec2(const U32 x, const U32 y) : x(x), y(y) {}
	iVec2() : x(0), y(0) {}
};