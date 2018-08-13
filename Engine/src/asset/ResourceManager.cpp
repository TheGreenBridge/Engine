//------------------------------------------------------------------------------
// ResourceManager.h
//
// Implementation of the ResourceManager
//
// Author: Sommerauer Christian
// Created: 11.08.18
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#include "ResourceManager.h"
#include <utils\Hash.h>

#include <graphics\api\Texture.h>
#include <graphics\Model.h>

namespace engine { namespace asset {
	
	using namespace engine::graphics;

	//--------------------------------------------------------------------------
	ResourceManager::ResourceManager(IAllocator* allocator) : 
		m_TextureContainer(allocator, 10),
		m_ModelContainer(allocator, 10)
	{
		
	}

	//--------------------------------------------------------------------------
	ResourceManager::~ResourceManager()
	{

	}

	//--------------------------------------------------------------------------
	Texture* ResourceManager::getTexture(const char* path)
	{
		U32 hash = Hash::toHash(path);
		Texture* texture = m_TextureContainer.getElement(hash);
		if (!texture)
		{
			texture = m_TextureContainer.newElement(hash, path);
		}
		return texture;
	}

	//--------------------------------------------------------------------------
	graphics::Model * ResourceManager::getModel(const char * path)
	{
		return nullptr;
	}

	graphics::Material * ResourceManager::getMaterial(const char * path)
	{
		return nullptr;
	}

} }