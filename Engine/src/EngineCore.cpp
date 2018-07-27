#include "EngineCore.h"

namespace engine {
	
	EntityManager Engine::m_entityMgr;
	MemoryManager Engine::m_memoryMgr;
	ComponentManager Engine::m_componentMgr;
	SystemManager Engine::m_systemMgr;

	void Engine::Initialize()
	{
		m_systemMgr.startUp();
	}

	void Engine::Update()
	{
		m_systemMgr.update();
	}

	void Engine::Terminate()
	{
		// Clean MemoryManager and everything else
		m_systemMgr.shutDown();
	}
	
	EntityManager * Engine::getEntityManager() 
	{
		return &m_entityMgr;
	}

	
	ComponentManager * engine::Engine::getComponentManager()
	{
		return &m_componentMgr;
	}
	SystemManager * Engine::getSystemManager() 
	{
		return &m_systemMgr;
	}
}
