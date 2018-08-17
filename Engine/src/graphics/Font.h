//------------------------------------------------------------------------------
// Font.h
//
// Represents a text on the screen
//
// Author: Sumi
// Created: 18.07.18
// Edited: 18.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <math\Vec3.h>
#include <math\iVec2.h>
#include <common\types.h>

// std
#include <map>
#include <string>

// Forward Declarations
namespace engine { namespace graphics {
		class VertexArray;
		class Texture;
		class Shader;
		class Camera;
} }

namespace engine{ namespace graphics{
	class Font
	{
	private:
		VertexArray* m_VertexArray;
	public:
		struct Character {
			U32 texture;	// ID handle of the glyph texture
			iVec2	size;       // Size of glyph
			iVec2	bearing;    // Offset from baseline to left/top of glyph
			U32     advance;    // Offset to advance to next glyph
		};

		Font();

		static std::map<U8, Character> Characters;
		void init();
		void renderText(Shader& shader, const Camera& camera, std::string text, float x, float y, float scale, Vec3 color);
	};
}}