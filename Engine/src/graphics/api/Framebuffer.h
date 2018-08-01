//------------------------------------------------------------------------------
// FrameBuffer.h
//
// Represents a framebuffer on the gpu
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: 30.07.18
//------------------------------------------------------------------------------
//
#pragma once

#include <common\types.h>

namespace engine {
	namespace graphics {

		class FrameBuffer {
		private:
			U32 m_BufferID;

			U32 m_DepthBufferID;
			U32 m_RenderedTexture;

			U16 m_PixelWidth, m_PixelHeight;

		public:
			FrameBuffer(U16 pixelWidth, U16 pixelHeight);
			FrameBuffer(const FrameBuffer& other) = delete;
			FrameBuffer() = delete;

			void enable() const;
			void disable() const;
			const U32 getRenderbuffer() const;
		};

	}
}