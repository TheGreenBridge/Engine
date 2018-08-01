//------------------------------------------------------------------------------
// GLFramebuffer.cpp
//
// OPEN GL implementation of a framebuffer
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Framebuffer.h>
#include <renderapi\opengl\GLCommon.h>
#include <common\types.h>
#include <utils\Log.h>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	FrameBuffer::FrameBuffer(U16 pixelWidth, U16 pixelHeight):
		m_PixelWidth(pixelWidth) , m_PixelHeight(pixelHeight)
	{
		// create a new Framebuffer
		GLCall(glGenFramebuffers(1, &m_BufferID));
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));

		GLCall(glGenTextures(1, &m_RenderedTexture));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_RenderedTexture));
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixelWidth, pixelHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0));
		// Filter
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
		
		/// Multiply Rendered Textures -> Cubemaps
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_RenderedTexture, 0);

		/// Only one Rendered Texture
		GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTexture, 0));
			
		// Create a new Renderbuffer and configure it.
		GLCall(glGenRenderbuffers(1, &m_DepthBufferID));
		GLCall(glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID));
		// GL_DEPTH_COMPONENT, GL_DEPTH24_STENCIL8
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pixelWidth, pixelHeight));
		// GL_DEPTH_STENCIL_ATTACHMENT
		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID));

		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		GLCall(glDrawBuffers(1, DrawBuffers)); // "1" is the size of DrawBuffers

										// Always check that our framebuffer is ok
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Framebuffer is not complete!");
		}

		// default framebuffer
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
			//return false;
	}

	//--------------------------------------------------------------------------
	void FrameBuffer::enable() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID));
		//glEnable(GL_DEPTH_TEST);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	//--------------------------------------------------------------------------
	void FrameBuffer::disable() const
	{
		GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
	}

	//--------------------------------------------------------------------------
	const U32 FrameBuffer::getRenderbuffer() const
	{
		return m_RenderedTexture;
	}
}}