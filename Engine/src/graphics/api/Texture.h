//------------------------------------------------------------------------------
// Texture.h
//
// Abstracts a texture on the graphics memory
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

namespace engine {	namespace graphics {

	class Texture {
	private:
		U32 m_Handle;
		I32 m_Width, m_Height;
	public:
		Texture();
		Texture(const char *path);
		~Texture();

		void loadImage(const char *path);
		void loadBuffer(U32 width, U32 height, unsigned char* buffer);

		U32 getID() const { return m_Handle; }

		I32 getWidth() const { return m_Width; }
		I32 getHeight() const { return m_Height; }

		void bind() const;
		void unbind() const;

		static void setActive(U32 index);
	};
}}
