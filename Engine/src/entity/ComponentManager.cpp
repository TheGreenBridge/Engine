#include "ComponentManager.h"
#include <EngineCore.h>

namespace engine {

	memory::MemoryManager *ComponentManager::m_memory = &Engine::m_memoryMgr;

	U32 ComponentManager::TypeCounter = 0;

	U32 ComponentManager::GetTypeCounter() {
		return TypeCounter++;
	}

	ComponentManager::ComponentManager()
		
	{
	}

	ComponentManager::~ComponentManager()
	{
	}

}

