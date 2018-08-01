//------------------------------------------------------------------------------
// GLTexture2D.cpp
//
// Open GL implementation of a 2D Texture
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Texture.h>
#include <renderapi\opengl\GLCommon.h>

#include <utils/Log.h>
#include <SOIL.h>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	Texture::Texture() 
	{
		GLCall(glGenTextures(1, &m_Handle));
		LOG("Created Texture 2D");
	}

	//--------------------------------------------------------------------------
	Texture::Texture(const char*path) 
	{
		loadImage(path);
		LOG("Created Texture 2D");
	}

	//--------------------------------------------------------------------------
	Texture::~Texture() 
	{
		GLCall(glDeleteTextures(1, &m_Handle));
		LOG("Deleted Texture 2D");
	}

	//--------------------------------------------------------------------------
	void Texture::loadImage(const char *path) 
	{
		U8 *image = SOIL_load_image(path, &m_Width, &m_Height, 0, SOIL_LOAD_RGB);
		if (image == nullptr) {
			LOG("ERROR: Image could not be loaded! Path", path);
			return;
		}
		
		
		GLCall(glBindTexture(GL_TEXTURE_2D, m_Handle));
		GLCall(glActiveTexture(GL_TEXTURE0));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
		// Set texture filtering parameters
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
		SOIL_free_image_data(image);
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}

	//--------------------------------------------------------------------------
	void Texture::loadBuffer(U32 width, U32 height, unsigned char* buffer)
	{
		// Need to put it elsewhere
		GLCall(glPixelStorei(GL_UNPACK_ALIGNMENT, 1)); // Disable byte-alignment restriction

		m_Width = width;
		m_Height = height;
		//GLCall(glGenTextures(1, &m_Handle));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_Handle));
		GLCall(glActiveTexture(GL_TEXTURE0));

		GLCall(glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			width,
			height,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			buffer
		));

		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	}

	//--------------------------------------------------------------------------
	void Texture::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, m_Handle);
	}

	//--------------------------------------------------------------------------
	void Texture::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	//--------------------------------------------------------------------------
	void Texture::setActive(U32 index)
	{
		switch (index)
		{
		case 0: GLCall(glActiveTexture(GL_TEXTURE0));
			break;
		case 1: GLCall(glActiveTexture(GL_TEXTURE1));
			break;
		case 2: GLCall(glActiveTexture(GL_TEXTURE2));
			break;
		case 3: GLCall(glActiveTexture(GL_TEXTURE3));
			break;
		case 4: GLCall(glActiveTexture(GL_TEXTURE4));
			break;
		case 5: GLCall(glActiveTexture(GL_TEXTURE5));
			break;
		default: GLCall(glActiveTexture(GL_TEXTURE0));
		}	
	}

//// AUSTAUSCHEN durch die eigene API!!!
//glGenTextures(1, &m_ID);
//glBindTexture(GL_TEXTURE_2D, m_ID);
//glActiveTexture(GL_TEXTURE0);
//
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//// Set texture filtering parameters
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//glGenerateMipmap(GL_TEXTURE_2D);
//SOIL_free_image_data(image);
//glBindTexture(GL_TEXTURE_2D, 0);

}}