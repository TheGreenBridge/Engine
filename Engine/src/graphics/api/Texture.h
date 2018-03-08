#pragma once

#include <common\types.h>

namespace engine {	namespace graphics {

	class Texture {
	private:
		U32 m_ID;
		I32 m_Width, m_Height;
	public:
		Texture();
		Texture(const char *path);
		~Texture();

		void loadImage(const char *path);

		U32 getID() const { return m_ID; }

		I32 getWidth() const { return m_Width; }
		I32 getHeight() const { return m_Height; }
	};
}}
