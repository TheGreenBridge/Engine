//------------------------------------------------------------------------------
// Application.cpp
//
// Represents one application
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: xx.xx.xx
//------------------------------------------------------------------------------
//

#include "Application.h"
#include <EngineCore.h>

namespace engine {

	Application::Application(const char* title, U32 width, U32 height) :
		window(title, width, height)
	{
	}

	Application::~Application() 
	{
		window.shutDown();
	}

	void Application::runApp()
	{
		while (!window.isClosed())
		{
			window.clear();
			Engine::Update();
			run_();
			window.update();
		}
		stop();
	}

	void Application::init()
	{
		Engine::Initialize();
		init_();
	}

	void Application::pause()
	{
		pause_();
	}

	void Application::stop()
	{
		stop_();
		// TODO: call all destructors!
		window.shutDown();
	}
}