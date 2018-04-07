#pragma once

#include <common\types.h>

namespace engine {
	namespace graphics {

		class Framebuffer {
		private:
			U32 m_BufferID;

			U32 m_DepthBufferID;
			U32 m_RenderedTexture;

			U16 m_PixelWidth, m_PixelHeight;

		public:
			Framebuffer(U16 pixelWidth, U16 pixelHeight);
			void enable() const;
			void disable() const;
			const U32 getRenderbuffer() const;
		};

	}
}