//------------------------------------------------------------------------------
// Entity.h
//
// Represents a object in the scene
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

// Components
///////////////////////////////////////////
// Entity
// Renderable
//		|-> Model
//		|-> Material
// Soundable
// Collidable
// Controlable
// Animateable
// AI
// Physics
///////////////////////////////////////////

#pragma once

#include "component\Transform.h"

#define Bit(x) 1 << x

namespace engine {

	struct EntityId
	{
		U32 id;
	};

	enum EComponent : U32
	{
		RENDERABLE	= Bit(0),
		ANIMATABLE	= Bit(1),
		PHYSICS		= Bit(2),
		COLLIDABLE	= Bit(3),
		CONTROLABLE = Bit(4),
		SOUNDABLE	= Bit(5),
		SCRIPT		= Bit(6)
	};

	class Entity {

	public:
		// Ctor & Dtor
		Entity(const Vec3 &postion, const Quaternion &rotation, const float scale);
		Entity();
		~Entity();
		
		EntityId m_UniqueId;
		Transform transform;

		void addComponent();
		void detachComponent();

		void detachAll();

		mat4 getTransformation();
		EntityId getId();

	private:

		U32 components;
	};

}


// OLD CODE

//Mesh *mesh;
//Model *model;
//Material *material;
//Animation *animation;
//Animatable *animatable;
//AABB3D *collidable;
//PBRMaterial *pbrmaterial;