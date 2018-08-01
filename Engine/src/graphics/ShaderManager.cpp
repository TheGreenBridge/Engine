//------------------------------------------------------------------------------
// ShaderManager.cpp
//
// Holds all Shaders
//
// Author: Sommerauer Christian
// Created: 31.07.18
// Changed: 31.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <graphics\ShaderManager.h>
#include <EngineCore.h>

namespace engine {
	namespace graphics {

		ShaderManager::ShaderManager(U32 shaders) :
			m_Pool(&Engine::gMemoryManager, shaders)			
		{

		}

		ShaderManager::~ShaderManager()
		{

		}

		void ShaderManager::destroy(Shader* vao)
		{
			m_Pool.deallocate(vao);
		}
	}
}