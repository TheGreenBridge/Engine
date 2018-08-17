#pragma once

#include <common/types.h>
#include <graphics\api\VertexArray.h>

namespace engine {
	namespace graphics {

		

	struct Model {
		//VertexArray vao;
		U32 numVertices;

		VertexArray* vertices;
	};
} }
