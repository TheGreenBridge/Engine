#pragma once

#pragma once

#ifndef LOGSYSTEM
#define LOGSYSTEM

#include "../math/mat4.h"
#include "../math/Quaternion.h"
#include <string>

#include <common\types.h>

#define DEBUG

#define LOG_ERROR(x) logError(x, __FILE__, __LINE__);
#define LOG_DEBUG(x) 

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void LOG(std::string title, const mat4 &matrix);

void LOG(const Quaternion &quat);

void LOG(const Vec3 &v);

void LOG(const std::string text);

void LOG(const std::string title, const std::string text);

void LOG(const char* title, const unsigned int number);

void LOG(const char* title, const float number);

void LOG(const char* title, const int number);

void logError(const char* text, const char* file, U32 line);

void logDebug(const char* text, const char* file, U32 line);

void HALT();

#endif
