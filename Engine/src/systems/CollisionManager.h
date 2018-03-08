#pragma once

#include "System.h"

namespace engine {
	namespace collision {
		struct AABB3D;
	}
	struct Event;
	using namespace collision;
	class CollisionManager : public ISystem{
	private:
		AABB3D* m_aCollidables;
		U32 numCollidables = 0;

	public:
		CollisionManager();
		~CollisionManager();

		bool testAABBOverlap(AABB3D* a, AABB3D *b);
		AABB3D *getCollidables() { return m_aCollidables; }
		U32 getNumCollidables();

		AABB3D *requestAABB3D();

		void update(const float dTime);
		void onEvent(Event *e);
		void startUp();
		void shutDown();
	};
}
