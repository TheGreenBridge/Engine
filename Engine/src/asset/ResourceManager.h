//------------------------------------------------------------------------------
// ResourceManager.h
//
// Handles all resources
//
// Author: Sommerauer Christian
// Created: 11.08.18
// Changed: 11.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <memory\PoolContainer.h>

// forward declarations
	
namespace engine {
	namespace graphics {
		class Texture;
		struct Model;
		struct Material;
} }

namespace engine {	namespace asset {

	using namespace engine::memory;

	// Resources
	// Texture
	// Mesh
	// Shader
	// Material


	class ResourceManager final
	{
	public:
		// Ctor & Dtor
		explicit ResourceManager(IAllocator* allocator);

		~ResourceManager();


		graphics::Texture* getTexture(const char* path);
		graphics::Model* getModel(const char* path);
		graphics::Material* getMaterial(const char* path);
		graphics::Texture* createTexture(const char* name);


		// Deleted Ctor
		ResourceManager() = delete;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

	private:

		PoolContainer<graphics::Texture> m_TextureContainer;
		PoolContainer<graphics::Model> m_ModelContainer;
		//PoolContainer<graphics::Material> m_MaterialContainer;

	};
}}
