#pragma once
#include <thread>

class Worker {
private:
	std::thread m_Thread;

public:
	Worker();
	~Worker();
	void doWork(void (*)());
	void join();
};