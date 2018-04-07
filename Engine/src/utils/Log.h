#pragma once

#pragma once

#ifndef LOGSYSTEM
#define LOGSYSTEM

#include "../math/mat4.h"
#include "../math/Quaternion.h"
#include <string>

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

void LOG(std::string title, const mat4 &matrix);

void LOG(const Quaternion &quat);

void LOG(const Vec3 &v);

void LOG(const std::string text);

void LOG(const std::string title, const std::string text);

void LOG(const char* title, const unsigned int number);

void LOG(const char* title, const float number);

void LOG(const char* title, const int number);

void LOG_ERROR(const char* text);

void HALT();

#endif
