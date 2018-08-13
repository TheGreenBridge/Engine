//------------------------------------------------------------------------------
// EngineCore.h
//
// Represents the core of the engine
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__
#pragma once

#include "entity\EntityManager.h"
#include "systems\SystemManager.h"
#include <graphics\BufferManager.h>
#include <graphics\TextureManager.h>
#include <graphics\ShaderManager.h>
#include <memory\MemoryManager.h>
#include "entity\ComponentManager.h"
#include <asset\ResourceManager.h>

namespace engine {

	using namespace engine::asset;
	using namespace engine::memory;
	using namespace engine::graphics;

	class Engine {
	public:
		static void Initialize();
		static void Update();
		static void Terminate();

		static MemoryManager gMemoryManager;

		static TextureManager gTextureManager;
		static ShaderManager gShaderManager;
		static BufferManager gBufferManager;
		static ResourceManager gResourceManager;

		static EntityManager* getEntityManager() ;
		static ComponentManager* getComponentManager() ;
		static SystemManager* getSystemManager() ;

		// Deleted Ctor
		Engine() = delete;
		Engine(const Engine&) = delete;
		Engine(Engine&&) = delete;
		Engine& operator= (const Engine&) = delete;
		Engine& operator= (Engine&&) = delete;

	private:
		
		static ComponentManager m_componentMgr;
		static EntityManager m_entityMgr;
		static SystemManager m_systemMgr;

	};

}

#endif
