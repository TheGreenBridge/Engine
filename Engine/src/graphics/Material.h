#pragma once

#include <math/Vec3.h>
#include <graphics\api\UniformBuffer.h>

using namespace engine::graphics;
namespace engine {	namespace graphics {
	// forward declaration
	class Texture;
	class Shader;

	

	struct Material {
		Texture *texture;
		Shader *shader;
		UniformBuffer* uniforms;
	};

}}
