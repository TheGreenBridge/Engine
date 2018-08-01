#pragma once

#include <common/types.h>
#include <graphics\api\VertexArray.h>

namespace engine {
	namespace graphics {

		

	struct Model {
		U32 vao;
		U32 vbo_vertices;
		U32 vbo_normals;
		U32 vbo_uvs;

		//VertexArray vao;
		U32 numVertices;

		VertexArray* vertices;
	};
} }
