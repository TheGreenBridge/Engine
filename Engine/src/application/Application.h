//------------------------------------------------------------------------------
// Application.h
//
// Represents one application
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <platform\windows\window.h>

namespace engine {
	class Application {
	protected:
		Window window;

		Application(const char* title, U32 width, U32 height);

	public:
		Application() = delete;
		~Application();

		void runApp();
		void init();
		void pause();
		void stop();

	protected: 

		virtual void run_() = 0;
		virtual void init_() = 0;
		virtual void pause_() = 0;
		virtual void stop_() = 0;
	};
}
