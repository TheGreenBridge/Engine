//------------------------------------------------------------------------------
// GLCubemap.cpp
//
// OPEN GL implementation of a cubemap
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Cubemap.h>
#include <renderapi\opengl\GLCommon.h>
#include <SOIL.h>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	Cubemap::Cubemap() 
	{

	}

	//--------------------------------------------------------------------------
	Cubemap::~Cubemap() 
	{
		GLCall(glDeleteTextures(1, &m_TexID));
	}

	//--------------------------------------------------------------------------
	void Cubemap::loadTextures(std::vector<const char*> faces) {
		GLCall(glGenTextures(1, &m_TexID));
		GLCall(glActiveTexture(GL_TEXTURE0));

		int width, height;
		unsigned char* image;

		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TexID));
		for (GLuint i = 0; i < faces.size(); i++)
		{
			image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
			GLCall(glTexImage2D(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
				GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			));
		}
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
		GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

}}