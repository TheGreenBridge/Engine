#include <graphics\api\Texture.h>
#include <renderapi\opengl\GLCommon.h>

#include <utils/Log.h>
#include <SOIL.h>

namespace engine {	namespace graphics {

	Texture::Texture() {

	}

	Texture::Texture(const char*path) {
		loadImage(path);
	}

	Texture::~Texture() {

	}

	void Texture::loadImage(const char *path) {
		U8 *image = SOIL_load_image(path, &m_Width, &m_Height, 0, SOIL_LOAD_RGB);
		if (image == nullptr) {
			LOG("ERROR: Image could not be loaded! Path", path);
			return;
		}
	
		glGenTextures(1, &m_ID);
		glBindTexture(GL_TEXTURE_2D, m_ID);
		glActiveTexture(0);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// Set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		SOIL_free_image_data(image);
		glBindTexture(GL_TEXTURE_2D, 0);
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