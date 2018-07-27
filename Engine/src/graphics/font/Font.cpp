//------------------------------------------------------------------------------
// Font.cpp
//
// Implementation to render text
//
// Author: Sumi
// Created: 18.07.18
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#include "Font.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include <cassert>
#include <utils\Log.h>

namespace engine { namespace graphics{
	
	//VertexArray Font::m_VertexArray = VertexArray();
	std::map<U8, Font::Character> Font::Characters = std::map<U8, Character>();

	//------------------------------------------------------------------------------
	Font::Font()
	{

	}

	//------------------------------------------------------------------------------
	void Font::init()
	{
		FT_Library ft;
		if (FT_Init_FreeType(&ft))
			LOG_ERROR("ERROR::FREETYPE: Could not init FreeType Library");

		// A face is a collection of glyphs
		FT_Face face;
		if (FT_New_Face(ft, "res/fonts/arial.ttf", 0, &face))
		{
			LOG_DEBUG("ERROR::FREETYPE: Failed to load font");
			assert(1 == 2);
		}
			

		// Define Font size
		FT_Set_Pixel_Sizes(face, 0, 48);

		// Set active glyph
		if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
			LOG("ERROR::FREETYTPE: Failed to load Glyph");

		//glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

		for (U8 c = 0; c < 120; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				LOG("ERROR::FREETYTPE: Failed to load Glyph");
				continue;
			}

			Texture texture;
			texture.loadBuffer(face->glyph->bitmap.width, face->glyph->bitmap.rows,
				face->glyph->bitmap.buffer);
			//// Generate texture
			//GLuint texture;
			//glGenTextures(1, &texture);
			//glBindTexture(GL_TEXTURE_2D, texture);
			//glTexImage2D(
			//	GL_TEXTURE_2D,
			//	0,
			//	GL_RED,
			//	face->glyph->bitmap.width,
			//	face->glyph->bitmap.rows,
			//	0,
			//	GL_RED,
			//	GL_UNSIGNED_BYTE,
			//	face->glyph->bitmap.buffer
			//);
			//// Set texture options
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			//// Now store character for later use
			Character character = {
				texture,
				iVec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				iVec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<U32>(face->glyph->advance.x)
			};
			Characters.insert(std::pair<U8, Character>(c, character));
		}

		FT_Done_Face(face);
		FT_Done_FreeType(ft);

		VertexBufferLayout layout;
		layout.pushFloat(4);

		m_VertexArray.createAndAddBuffer(4 * 6 * 4 * 2, layout, BufferUsage::DYNAMIC);
	}

	//------------------------------------------------------------------------------
	void Font::renderText(Shader& shader, const Camera& camera, std::string text, float x, float y, float scale, Vec3 color) {
		// Activate corresponding render state	
		shader.enable();
		
		shader.setUniform3f("textColor", color);
		//shader.setUniformMat4("projection", camera.getProjectionMatrix());

		//glUniform3f(glGetUniformLocation(shader.Program, "textColor"), color.x, color.y, color.z);
		//glActiveTexture(GL_TEXTURE0);
		Texture::setActive(0);
		m_VertexArray.bind();
		//glBindVertexArray(VAO);

		// Iterate through all characters
		std::string::const_iterator c;
		for (c = text.begin(); c != text.end(); c++)
		{
			Character& ch = Characters[*c];

			F32 xpos = x + ch.bearing.x * scale;
			F32 ypos = y - (ch.size.y - ch.bearing.y) * scale;

			F32 w = ch.size.x * scale;
			F32 h = ch.size.y * scale;
			// Update VBO for each character
			F32 vertices[6][4] = {
				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos,     ypos,       0.0, 1.0 },
				{ xpos + w, ypos,       1.0, 1.0 },

				{ xpos,     ypos + h,   0.0, 0.0 },
				{ xpos + w, ypos,       1.0, 1.0 },
				{ xpos + w, ypos + h,   1.0, 0.0 }
			};
			// Render glyph texture over quad
			//ch.texture.bind();
			//glBindTexture(GL_TEXTURE_2D, ch.textureID);
			// Update content of VBO memory
			

			//glBindBuffer(GL_ARRAY_BUFFER, VBO);
			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			//glBindBuffer(GL_ARRAY_BUFFER, 0);
			// Render quad
			shader.setUniformTexture("text", 0, ch.texture.getID());
			m_VertexArray.bind();
			m_VertexArray.getBuffer()->setData(sizeof(vertices), vertices);
			m_VertexArray.draw(6);
			//glDrawArrays(GL_TRIANGLES, 0, 6);
			// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
			x += (ch.advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
		}
		m_VertexArray.unbind();
		//glBindVertexArray(0);
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
}
}
