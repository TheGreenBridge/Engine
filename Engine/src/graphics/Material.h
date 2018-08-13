//------------------------------------------------------------------------------
// Material.h
//
// Represents a material on a model
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <math/Vec3.h>
#include <graphics\api\UniformBuffer.h>


// Forward Declaration
namespace engine {	namespace graphics {
	class Texture;
	class Shader;
}}


namespace engine {	namespace graphics {

	struct Material {
		Texture *texture;
		Shader *shader;
		UniformBuffer* uniforms;
	};

}}
