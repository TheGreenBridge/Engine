#pragma once

#include <math/Vec3.h>
using namespace engine::graphics;
namespace engine {	namespace graphics {
	// forward declaration
	class Texture;
	class Shader;

	

	struct Material {
		Vec3 diffuse;
		Vec3 ambient;
		Vec3 specular;

		Texture *texture;
		Shader *shader;
	};

}}
