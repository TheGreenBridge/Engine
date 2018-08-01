#include "EngineCore.h"

namespace engine {
	
	MemoryManager Engine::gMemoryManager;
	EntityManager Engine::m_entityMgr;
	ComponentManager Engine::m_componentMgr;
	SystemManager Engine::m_systemMgr;
	
	TextureManager Engine::gTextureManager(10, 10);
	ShaderManager Engine::gShaderManager(10);
	BufferManager Engine::gBufferManager(10, 10, 10);

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
