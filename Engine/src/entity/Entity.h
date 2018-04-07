#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"
#include "../math/Quaternion.h"

#include "../graphics/Mesh.h"
#include "../graphics/Model.h"
#include "../graphics/Material.h"
#include "../graphics/animation/Animation.h"
#include <graphics\pbr\PBRMaterial.h>

#include "component\Transform.h"
#include "component\Animatable.h"
#include "../graphics/animation/skinning/RenderableSkin.h"
#include "../collision/AABB.h"

using namespace engine::animation;
using namespace engine::collision;
using namespace engine::graphics;
//using namespace engine::component;

namespace engine {

	// forward declaration
	//class PBRMaterial;

	struct EntityId
	{
		U32 id;
	};

	class Entity {
	public:
		/*Entity(const Vec3 &postion, const Quaternion &rotation, const float scale);
		Entity();*/
		//Entity() {};
		~Entity() {};

		// COMPONENTS
		Transform transform;
		Mesh *mesh;
		Model *model;
		Material *material;

		Animation *animation;
	
		Animatable *animatable;
		AABB3D *collidable;
		PBRMaterial *pbrmaterial;

		mat4 getTransformation();

		EntityId m_UniqueId;
		//EntityId getId();
	//private:
	//	EntityId m_UniqueId;
	};

}