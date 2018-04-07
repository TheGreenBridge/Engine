#pragma once


namespace engine {
	namespace collision {
		struct AABB3D;

		struct Collidable {
			AABB3D *collider;

		};
	}
}