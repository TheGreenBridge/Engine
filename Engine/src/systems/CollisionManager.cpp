#include "../collision/AABB.h"
#include "CollisionManager.h"

#include <chrono>
#include <thread>

#include "../utils/Log.h"


#define MAX_COLLIDABLES 10

using namespace engine::collision;

namespace engine {

	CollisionManager::CollisionManager() {

	}

	CollisionManager::~CollisionManager() {

	}


	bool CollisionManager::testAABBOverlap(AABB3D *a, AABB3D *b) {
		F32 d1x = b->min.x - a->max.x;
		F32 d1y = b->min.y - a->max.y;
		F32 d1z = b->min.z - a->max.z;

		F32 d2x = a->min.x - b->max.x;
		F32 d2y = a->min.y - b->max.y;
		F32 d2z = a->min.z - b->max.z;

		if (d1x > 0.0f || d1y > 0.0f || d1z > 0.0f)
			return false;

		if (d2x > 0.0f || d2y > 0.0f || d2z > 0.0f)
			return false;

		return true;
	}

	AABB3D *CollisionManager::requestAABB3D() {
		if (numCollidables < MAX_COLLIDABLES) {		
			AABB3D &result = m_aCollidables[numCollidables++];
			result.max = Vec3(1, 1, 1);
			result.min = Vec3(0, 0, 0);
			return &result;
		}
		else {
			LOG("CollisionManager out of Memory");
			return nullptr;
		}
	}

	void CollisionManager::update(F32 dTime) {
		for (U32 i = 0; i < numCollidables; i++) {
			//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
			
			//LOG("num ", numCollidables);
			for (U32 a = i; a < numCollidables;  ) {
				a++;
				//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				
				
				if(testAABBOverlap(&m_aCollidables[i], &m_aCollidables[a])) 
					LOG("Collision detected");
			}
		}
		
	}

	void drawAABB(const AABB3D &collider) {
		
	}

	U32 CollisionManager::getNumCollidables() {
		return numCollidables;
	}
	
	void CollisionManager::onEvent(Event *e) {

	}

	void CollisionManager::startUp() {
		m_aCollidables = REQUEST_MEMORY(AABB3D, MAX_COLLIDABLES);
	}

	void CollisionManager::shutDown() {

	}

}