#pragma once

#include"../math/vec3.h"

namespace engine {
	namespace collision {
		struct AABB3D {
			Vec3 min;
			Vec3 max;
		};
	}
}
