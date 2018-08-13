//------------------------------------------------------------------------------
// File Name: Camera.h
// Description: Shows the scene from the view of this camera
//
// Author: Sommerauer Christian
// Created: 28.01.2017
// Changed: 13.08.2018
//------------------------------------------------------------------------------
//

#include "FollowCamera.h"
#include "Entity.h"
#include <utils\Log.h>

namespace engine {	namespace graphics {


	FollowCamera::FollowCamera(Entity *entity) :
		Camera(90.0f, 1.7777f, 0.1f, 800.0f), m_pEntity(entity) 
	{
	
	}

	FollowCamera::~FollowCamera(){

	}

	void FollowCamera::update(F32 dTime) {
	
		m_Position = Vec3(0, -5, -entityDistance) - m_pEntity->transform.position;
		//LOG("followcam:",m_Position.x);
		Camera::update();
	}

	void calculateCameraPosition(F32 horizDistance, F32 verticDistance) {
		
	}
}}

