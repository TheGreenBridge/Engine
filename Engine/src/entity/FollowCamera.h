#pragma once

#include <entity\Camera.h>
#include <math\vec3.h>
#include <common\types.h>

// Forward Declarations
namespace engine {	
	class Entity;
}

namespace engine { namespace graphics {

	class FollowCamera : public Camera{

	public:
		FollowCamera(Entity *entity);
		~FollowCamera();

		void update(float dTime);

		void increasePosition(F32 dx, F32 dy, F32 dz);
		void increaseRotation(const Quaternion &quat);

	protected:
		
		F32 velocity = 1.2f;
		F32 acceleration = 0.8f;
		F32 entityDistance = 10.0f;
		F32 angleAroundEntity = 0;

		Entity *m_pEntity;
		
	private:
		void calculateCameraPosition(F32 horizDistance, F32 verticDistance);
		F32 calculateHorizontalDistance();
		F32 calculateVerticalDistance();
		void calculateZoom();
		void calculateYaw();
		void calculatePitch();
		void calculateAngleAroundEntity();
	};
}}

