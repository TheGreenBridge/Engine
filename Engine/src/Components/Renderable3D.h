
#ifndef __RENDERABLE_3D_COMPONENT_H__
#define __RENDERABLE_3D_COMPONENT_H__
#pragma once

#include <graphics\Model.h>
#include <entity\component\Transform.h>
#include <graphics\Material.h>

using namespace engine::graphics;

namespace engine {	namespace component {

	struct Renderable3D
	{
		Transform* transform;
		Model* model;
		Material* material;
	};


	

}}




#endif //__RENDERABLE_3D_COMPONENT_H__
