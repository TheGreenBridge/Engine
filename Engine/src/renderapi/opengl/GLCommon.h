//------------------------------------------------------------------------------
// GLCommon.h
//
// Common stuff for the gl implementations
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 21.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <GL/glew.h>
#include <common\common.h>
#include <graphics\api\Context.h>
#include <utils\Log.h>

#define GLCall(x) x; Context::getErrors(__FILE__, __LINE__); 

