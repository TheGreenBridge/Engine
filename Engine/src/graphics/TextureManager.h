//------------------------------------------------------------------------------
// TextureManager.h
//
// Holds all sorts of textures and cubemaps
//
// Author: Sommerauer Christian
// Created: 31.07.18
// Changed: 31.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <memory\allocator\PoolAllocator.h>
#include <graphics\api\Texture.h>
#include <graphics\api\Cubemap.h>
#include <common\types.h>

namespace engine { namespace graphics {

	using namespace engine::memory;

	class TextureManager {
	private:
		PoolAllocator<Texture> m_PoolTextures;
		PoolAllocator<Cubemap> m_PoolCubemaps;
	public:

		TextureManager(U32 textures, U32 cubemaps);
		// Deleted Ctr
		TextureManager() = delete;
		TextureManager(const TextureManager&) = delete;
		TextureManager(TextureManager&&) = delete;
		// Deleted Assignment
		TextureManager& operator=(const TextureManager&) = delete;
		TextureManager& operator=(const TextureManager&&) = delete;

		~TextureManager();

		Texture* createTexture();
		Cubemap* createCubemap();

		void destroy(Texture* texture);
		void destroy(Cubemap* cubemap);
	};

} }