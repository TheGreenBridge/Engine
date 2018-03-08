#pragma once

#include <common\types.h>

namespace engine {	namespace graphics {

	class Renderable2D {

	private:

		U32 m_VBO;

	public:

		Renderable2D() {
			//glGenVertexArrays(1, &m_VBO);
		}

	};

} }