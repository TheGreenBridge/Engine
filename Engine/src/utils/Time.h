#pragma once

#include <common\types.h>
// std
#include <chrono>

typedef std::chrono::time_point<std::chrono::steady_clock> timepoint;

class Time {
private:
	long long m_Dt;
	long long m_PastTime;
	timepoint m_LastTime;
public:
	Time();

	void measureTime();
	void init();
	void start();

	void erasePastTime();

	U64 getDelta() const;
	F32 getDeltaF32() const;
	U64 getPastTime() const;
};