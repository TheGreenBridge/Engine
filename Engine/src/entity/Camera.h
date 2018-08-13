//------------------------------------------------------------------------------
// File Name: Camera.h
// Description: Shows the scene from the view of this camera
//
// Author: Sommerauer Christian
// Created: 28.01.2017
// Changed: 13.08.2018
//------------------------------------------------------------------------------
//

#pragma once

#include <math/mat4.h>
#include <math/vec3.h>
#include <math/Quaternion.h>
#include <utils/Log.h>


namespace engine {	namespace graphics {

	class Camera{
	protected:
		Vec3 m_Position;//, m_FocalPoint, m_UP, m_ViewDirection;
		F32 key_pitch, key_yaw, key_roll;

		mat4 m_ViewMatrix;
		mat4 m_ProjectionMatrix;
		Quaternion m_Rotation;
		F32 m_Fov, m_AspectRatio, m_Near, m_Far;

	public:
	
		F32 m_Speed;
	
		Camera(F32 fov, F32 aspectRatio, F32 near, F32 far);
		~Camera();

		mat4 getProjectionMatrix() const;
		mat4 getViewMatrix() const;
		mat4 getRotationMatrix() const;

		void update();

		void setSpeed(const F32 speed) { m_Speed = speed; }
		float getSpeed()const { return m_Speed; }

		inline const Vec3 &getPosition() const { return m_Position; }
		void setPosition(const Vec3 &position);

		inline const Vec3 &getRotation() const { return m_Rotation.toEulerAngles(); }
		const Quaternion &getQuatRotation() const { return m_Rotation; }
	
		inline void setRotation(const Vec3 &rotation, const F32 angle) { m_Rotation.setRotation(rotation, angle);
		m_Rotation.normalize();
		}

		void Translate(const Vec3 &translation);

		//inline void Rotate(const vec3 &rotation, const float angle) { m_Rotation.rotate(rotation, angle);}
		void Rotate(const Vec3 &rotationAngles, F32 angle);
		void Rotate(const F32 yaw, const F32 pitch, const F32 roll);

		inline void Translate(F32 x, F32 y, F32 z) { m_Position += Vec3(x, y, z); }
		inline void Rotate(F32 x, F32 y, F32 z, F32 angle) { m_Rotation.rotate(Vec3(x,y,z), angle); }

		mat4 lookAt(const Vec3 &position, const Vec3 &target, const Vec3 &up);

		void quatRotate(F32 angle, const Vec3 &axis);

		void printInfo();
	};

}}
