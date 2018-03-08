#pragma once

#include "../math/vec3.h"
#include "../math/mat4.h"
#include "../math/Quaternion.h"

#include "../graphics/Mesh.h"
#include "../graphics/Model.h"
#include "../graphics/Material.h"
#include "../graphics/animation/Animation.h"

#include "component\Transform.h"
#include "component\Animatable.h"
#include "../graphics/animation/skinning/RenderableSkin.h"
#include "../collision/AABB.h"

using namespace engine::animation;
using namespace engine::collision;
using namespace engine::graphics;
//using namespace engine::component;

namespace engine {



	class Entity {
	private:
	
	public:
		/*Entity(const Vec3 &postion, const Quaternion &rotation, const float scale);
		Entity();*/
		~Entity() {};

		// COMPONENTS
		Transform transform;
		Mesh *mesh;
		Model *model;
		Material *material;
		Animation *animation;
	
		Animatable *animatable;
		AABB3D *collidable;

		mat4 getTransformation();
	};

}