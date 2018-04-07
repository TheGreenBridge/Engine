#pragma once
#include <thread>

class Worker {
private:
	std::thread worker;
	void doWork();
public:
	Worker();
};