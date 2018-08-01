#pragma once

#include <common\types.h>
#include <math\Vec3.h>
#include <math\Vec2.h>

namespace engine { namespace graphics {

	struct Vertex1P1N1UV
	{
		Vec3 m_position;
		Vec3 m_normal;
		Vec2 uv;
	};

	struct Vertex1P1D1S2UV4J
	{
		Vec3 m_position;
		// ...
	};
} }