#pragma once


#include "../../entity/component/Transform.h"

namespace engine {	namespace animation {
		class Animation {
		private:
			Transform m_start;
			Transform m_end;
			//float m_speed;

		public:
			//Animation();
			Animation(Transform startVector, Transform endVector);
			~Animation();

			Vec3 getPosition(const float deltaTime) const;
			Quaternion getRotation(const float deltaTime) const;
			float getScale(const float deltaTime) const;
		};
}}

