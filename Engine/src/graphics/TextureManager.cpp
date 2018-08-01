//------------------------------------------------------------------------------
// TextureManager.cpp
//
// Implementation of the texture manager
//
// Author: Sommerauer Christian
// Created: 31.07.18
// Changed: 31.07.18
//------------------------------------------------------------------------------
//

#include <graphics\TextureManager.h>
#include <EngineCore.h>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	TextureManager::TextureManager(U32 textures, U32 cubemaps) :
		m_PoolTextures(&Engine::gMemoryManager, textures),
		m_PoolCubemaps(&Engine::gMemoryManager, textures)
	{

	}

	//--------------------------------------------------------------------------
	TextureManager::~TextureManager()
	{

	}

	//--------------------------------------------------------------------------
	Texture* TextureManager::createTexture() 
	{
		return m_PoolTextures.allocate();
	}

	//--------------------------------------------------------------------------
	Cubemap * TextureManager::createCubemap()
	{
		return m_PoolCubemaps.allocate();
	}

	//--------------------------------------------------------------------------
	void TextureManager::destroy(Texture* texture)
	{
		m_PoolTextures.deallocate(texture);
	}

	//--------------------------------------------------------------------------
	void TextureManager::destroy(Cubemap* cubemap)
	{
		m_PoolCubemaps.deallocate(cubemap);
	}
}}