#pragma once
/*
DEBUG CONSOLE
*/

#include <threadding\Worker.h>

namespace engine {


	class Console
	{

	private:
		static Worker m_Worker;
	public:
		static bool m_IsRunning;
		Console();
		void checkConsole();
		void runConsole();
		void stopConsole();

	};

}