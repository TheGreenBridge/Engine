#pragma once

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

	long long getDelta()const;
	long long getPastTime() const;
};