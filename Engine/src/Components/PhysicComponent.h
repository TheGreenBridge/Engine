#ifndef __PHYSIC_COMPONENT_H__
#define __PHYSIC_COMPONENT_H__
#pragma once

#include <common\types.h>
#include <math\Vec3.h>

struct PhysicComponent
{
	Vec3 direction;

	F32 mass;

	F32 speed;
	F32 acceleration;
};


#endif // __PHYSIC_COMPONENT_H__