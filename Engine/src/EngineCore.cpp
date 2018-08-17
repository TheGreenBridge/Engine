//------------------------------------------------------------------------------
// EngineCore.cpp
//
// Implements the core of the engine
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#include "EngineCore.h"

namespace engine {

	using namespace engine::memory;
	
	// STATIC
	/////////////////////////////////////////////////////////////
	MemoryManager Engine::gMemoryManager;
	EntityManager Engine::m_entityMgr;
	ComponentManager Engine::m_componentMgr(&gMemoryManager);
	SystemManager Engine::m_systemMgr;
	
	// TODO(Som): Will get into ResourceManager
	TextureManager Engine::gTextureManager(10, 10);
	ShaderManager Engine::gShaderManager(20);
	BufferManager Engine::gBufferManager(&gMemoryManager);

	ResourceManager Engine::gResourceManager(&gMemoryManager);
	/////////////////////////////////////////////////////////////

	//--------------------------------------------------------------------------
	void Engine::Initialize()
	{
		m_systemMgr.startUp();
	}

	//--------------------------------------------------------------------------
	void Engine::Update()
	{
		m_systemMgr.update();
	}

	//--------------------------------------------------------------------------
	void Engine::Terminate()
	{
		// Clean MemoryManager and everything else
		m_systemMgr.shutDown();
	}
	
	//--------------------------------------------------------------------------
	EntityManager * Engine::getEntityManager() 
	{
		return &m_entityMgr;
	}

	//--------------------------------------------------------------------------
	ComponentManager * engine::Engine::getComponentManager()
	{
		return &m_componentMgr;
	}

	//--------------------------------------------------------------------------
	SystemManager * Engine::getSystemManager() 
	{
		return &m_systemMgr;
	}
}
