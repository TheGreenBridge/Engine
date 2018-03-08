#pragma once

#include "../math/mat4.h"
#include "../math/vec3.h"
#include "../math/Quaternion.h"
#include <string>
#include "../utils/Log.h"

namespace engine {	namespace graphics {

	class Camera{
	protected:
		Vec3 m_Position;//, m_FocalPoint, m_UP, m_ViewDirection;
		float key_pitch, key_yaw, key_roll;

		mat4 m_ViewMatrix;
		Quaternion m_Rotation;
		float m_Fov, m_AspectRatio, m_Near, m_Far;

	public:
	
		float m_Speed;
	
		Camera(float fov, float aspectRatio, float near, float far);
		~Camera();

		mat4 getProjectionMatrix() const;
		mat4 getViewMatrix() const;
		mat4 getRotationMatrix() const;

		void update();

		void setSpeed(const float speed) { m_Speed = speed; }
		float getSpeed()const { return m_Speed; }

		inline const Vec3 &getPosition() const { return m_Position; }
		void setPosition(const Vec3 &position);

		inline const Vec3 &getRotation() const { return m_Rotation.toEulerAngles(); }
		const Quaternion &getQuatRotation() const { return m_Rotation; }
	
		inline void setRotation(const Vec3 &rotation, const float angle) { m_Rotation.setRotation(rotation, angle);
		m_Rotation.normalize();
		}

		void Translate(const Vec3 &translation);

		//inline void Rotate(const vec3 &rotation, const float angle) { m_Rotation.rotate(rotation, angle);}
		void Rotate(const Vec3 &rotationAngles, float angle);
		void Rotate(const float yaw, const float pitch, const float roll);

		inline void Translate(float x, float y, float z) { m_Position += Vec3(x, y, z); }
		inline void Rotate(float x, float y, float z, float angle) { m_Rotation.rotate(Vec3(x,y,z), angle); }

		mat4 lookAt(const Vec3 &position, const Vec3 &target, const Vec3 &up);

		void quatRotate(float angle, const Vec3 &axis);

		void printInfo() {
			LOG("FOV", this->m_Fov);
			LOG("Aspect", this->m_AspectRatio);
			LOG("near", this->m_Near);
			LOG("far", this->m_Far);
			LOG("Rotation",
				std::to_string(this->m_Rotation.x) + " , " +
				std::to_string(this->m_Rotation.y) + " , " +
				std::to_string(this->m_Rotation.z) + " , " +
				std::to_string(this->m_Rotation.w));
		
			LOG("ViewMatrix", m_ViewMatrix);
			LOG("TRANSLATION.X : ", m_ViewMatrix.elements[12]);
		
			LOG("m_Rotation",
				" X: "  + std::to_string(m_Rotation.x) + 
				" Y: " + std::to_string(m_Rotation.y) +
				" Z: " + std::to_string(m_Rotation.z) +
				" W: " + std::to_string(m_Rotation.w));
		
			mat4 translation(	1, 0, 0, 0,
								0, 1, 0, 0,
								0, 0, 1, 0,
								0, 0, 0, 1);

			mat4 rotation(  1, 0, 0, 0,
							0, 1, 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

			mat4 result = rotation * translation;

			LOG("TEST MATRIX", result);
		}
	};

}}
