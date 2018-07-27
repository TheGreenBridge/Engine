#include "Worker.h"
#include <iostream>


void Worker::doWork(void(*work)())
{
	m_Thread = std::thread(work);

	//m_Thread.join();
	//std::cout << "Thread finished" << std::endl;
}

void Worker::join()
{
	m_Thread.join();
}


Worker::Worker()
{

}

Worker::~Worker()
{
	join();
}
