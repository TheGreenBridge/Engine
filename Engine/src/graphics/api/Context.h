#pragma once

#include <common\types.h>

class Context {
private:
public:
	static const BOOL init();
	static const void setViewport(const int width, const int height);
	static const void clear();
};
