#ifndef __ENGINE_CORE_H__
#define __ENGINE_CORE_H__
#pragma once

#include "entity\ComponentManager.h"
#include "entity\EntityManager.h"
#include "systems\SystemManager.h"
#include <memory\MemoryManager.h>
#include <graphics\BufferManager.h>
#include <graphics\TextureManager.h>
#include <graphics\ShaderManager.h>

namespace engine {

	class Engine {
	private:
		
		static ComponentManager m_componentMgr;
		static EntityManager m_entityMgr;
		static SystemManager m_systemMgr;

		Engine() = delete;
		Engine(const Engine&) = delete;
		Engine& operator= (const Engine&) = delete;


	public:
		static void Initialize();
		static void Update();
		static void Terminate();

		static MemoryManager gMemoryManager;

		static TextureManager gTextureManager;
		static ShaderManager gShaderManager;
		static BufferManager gBufferManager;


		static EntityManager* getEntityManager() ;
		static ComponentManager* getComponentManager() ;
		static SystemManager* getSystemManager() ;
	};

}

#endif
