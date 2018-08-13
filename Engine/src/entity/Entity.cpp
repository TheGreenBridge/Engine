//------------------------------------------------------------------------------
// Entity.cpp
//
// Implementation of a entity
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#include "Entity.h"
#include <EngineCore.h>

namespace engine {

	//--------------------------------------------------------------------------
	Entity::Entity(
		const Vec3 &position, const Quaternion &rotation, const float scale)
		: transform(position, rotation, scale)
	{

	}

	//--------------------------------------------------------------------------
	Entity::Entity() : transform(Vec3(0,0,0), Quaternion(0,0,0,1), 1.0f) 
	{

	}

	//--------------------------------------------------------------------------
	Entity::~Entity()
	{

	}

	//--------------------------------------------------------------------------
	mat4 Entity::getTransformation() {
		mat4 result(1.0f);

		result = transform.rotation.toMatrix();
	
		result[12] = transform.position.x;
		result[13] = transform.position.y;
		result[14] = transform.position.z;

		mat4 scaleMatrix(transform.scale, 0, 0, 0,
							0, transform.scale, 0, 0,
							0, 0, transform.scale, 0,
							0, 0, 0, 1);

		result = result * scaleMatrix;

		return result;
	}

	//--------------------------------------------------------------------------
	EntityId Entity::getId()
	{
		return m_UniqueId;
	}

	//--------------------------------------------------------------------------
	void Entity::addComponent()
	{

	}

	//--------------------------------------------------------------------------
	void Entity::detachComponent()
	{
		
	}

	//--------------------------------------------------------------------------
	void Entity::detachAll()
	{
		
	}
}