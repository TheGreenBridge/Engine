//------------------------------------------------------------------------------
// ComponentManager.cpp
//
// Implemenation of the component manager
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#include "ComponentManager.h"
#include <memory\allocator\IAllocator.h>

namespace engine {
	// STATIC
	/////////////////////////////////////////////
	U32 ComponentManager::TypeCounter = 0;
	/////////////////////////////////////////////

	//----------------------------------------------------------------------
	U32 ComponentManager::GetTypeCounter() 
	{
		return TypeCounter++;
	}

	//----------------------------------------------------------------------
	ComponentManager::ComponentManager(memory::IAllocator* allocator)
		: m_memory(allocator)
	{

	}

	//----------------------------------------------------------------------
	ComponentManager::~ComponentManager()
	{

	}

}