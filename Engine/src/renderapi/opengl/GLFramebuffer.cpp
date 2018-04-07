#include <graphics\api\Framebuffer.h>
#include <renderapi\opengl\GLCommon.h>
#include <common\types.h>
#include <utils\Log.h>

namespace engine {	namespace graphics {

	Framebuffer::Framebuffer(U16 pixelWidth, U16 pixelHeight):
		m_PixelWidth(pixelWidth) , m_PixelHeight(pixelHeight)
	{
		// create a new Framebuffer
		glGenFramebuffers(1, &m_BufferID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);

		glGenTextures(1, &m_RenderedTexture);

		// "Bind" the newly created texture : all future texture functions will modify this texture
		glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);

		// Give an empty image to OpenGL ( the last "0" )
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pixelWidth, pixelHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
		
		/// Multiply Rendered Textures -> Cubemaps
		//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_RenderedTexture, 0);

		/// Only one Rendered Texture
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderedTexture, 0);
			
		// Create a new Framebuffer and configure it.
		glGenRenderbuffers(1, &m_DepthBufferID);
		glBindRenderbuffer(GL_RENDERBUFFER, m_DepthBufferID);
		// GL_DEPTH_COMPONENT, GL_DEPTH24_STENCIL8
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, pixelWidth, pixelHeight);
		// GL_DEPTH_STENCIL_ATTACHMENT
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthBufferID);

		GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
		glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

										// Always check that our framebuffer is ok
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			LOG_ERROR("Framebuffer is not complete!");
		}

		// default framebuffer
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//return false;
	}

	void Framebuffer::enable() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_BufferID);
		//glEnable(GL_DEPTH_TEST);
		//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Framebuffer::disable() const
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	const U32 Framebuffer::getRenderbuffer() const
	{
		return m_RenderedTexture;
	}
}}