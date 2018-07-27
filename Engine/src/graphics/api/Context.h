//------------------------------------------------------------------------------
// Context.h
//
// Represents a context of the render api
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 21.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

class Context {
private:
public:
	static const BOOL init();
	static const void setViewport(const int width, const int height);
	static const void clear();
	static const void getErrors(const char* file, U32 line);
};
