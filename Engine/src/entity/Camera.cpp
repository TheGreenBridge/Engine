//------------------------------------------------------------------------------
// File Name: Camera.h
// Description: Shows the scene from the view of this camera
//
// Author: Sommerauer Christian
// Created: 28.01.2017
// Changed: 18.08.2018
//------------------------------------------------------------------------------
//

#include "Camera.h"
// std
#include <string>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	Camera::Camera(F32 fov, F32 aspectRatio, F32 near, F32 far) : 
		Frustum{ fov , aspectRatio , near, far },
		m_Rotation(0.0f, 0.0f, 0.0f, 1.0f), m_Speed(0.01f),
		key_roll(0),
		key_pitch (0),
		key_yaw (0)
	{
		
	}

	//--------------------------------------------------------------------------
	Camera::~Camera() 
	{

	}

	//--------------------------------------------------------------------------
	mat4 Camera::getProjectionMatrix() const
	{		
		return m_ProjectionMatrix;
	}

	//--------------------------------------------------------------------------
	inline void setRotation(const Vec3 &rotation) 
	{
		
	} 

	//--------------------------------------------------------------------------
	void Camera::Rotate(const F32 yaw, const F32 pitch, const F32 roll)
	{
		key_yaw= yaw;
		key_pitch = pitch;
		key_roll = roll;

		// ORIGNIAL
	
		Quaternion key_quat;
		key_quat.setEulerAngles(key_yaw, key_pitch, key_roll);
		m_Rotation.rotate(key_quat);
		m_Rotation.normalize();
	}

	//--------------------------------------------------------------------------
	void Camera::Rotate(const Vec3 &axis, F32 angle)
	{
		//key_pitch = 0;
		//key_roll = 0;
		//key_yaw = 0;

		// roll_axis =	local_Z_Axis == forward
		// pitch_axis = local_X_Axis == strafe
		// yaw_axis =	local_Y_Axis == up

		Vec3 roll_axis, pitch_axis, yaw_axis;

		pitch_axis.x = m_ViewMatrix[0];
		pitch_axis.y = m_ViewMatrix[4];
		pitch_axis.z = m_ViewMatrix[8];

		yaw_axis.x = m_ViewMatrix[1];
		yaw_axis.y = m_ViewMatrix[5];
		yaw_axis.z = m_ViewMatrix[9];

		roll_axis.x = m_ViewMatrix[2];
		roll_axis.y = m_ViewMatrix[6];
		roll_axis.z = m_ViewMatrix[10];

		if (axis.x == 1) {
		
			m_Rotation.rotate(pitch_axis, angle);
		}
		else if (axis.y == 1) {
		
			m_Rotation.rotate(yaw_axis, angle);
		}
		else if (axis.z == 1) {
		
			m_Rotation.rotate(roll_axis, angle);
		}



		//// ORIGNIAL
		//
		//Quaternion key_quat;
		//key_quat.setEulerAngles(key_yaw, key_pitch, key_roll);

		///// DES WOA VORHER!!!
		////m_Rotation.rotate(axis, angle);

		/*Quaternion frame_yaw, frame_pitch;
		frame_pitch.setRotation(YAXIS, key_pitch);
		frame_yaw.setRotation(XAXIS, key_yaw);
		m_Rotation.rotate(frame_pitch * frame_yaw);*/


		// War auch dabei!!!
		//m_Rotation = m_Rotation * key_quat ;
		//m_Rotation.normalize();
	}

	//--------------------------------------------------------------------------
	void Camera::quatRotate(F32 angle, const Vec3 &axis)
	{
	
	}

	//--------------------------------------------------------------------------
	void Camera::update() 
	{
		// IN2GPU EXAMPLE

		//m_Rotation.setRotation(Vec3(key_pitch*PI/180, key_yaw*PI / 180, key_roll*PI / 180));
		//m_Rotation.setEulerAngles(key_yaw, key_pitch, key_roll);
		//m_Rotation.normalize();

		// update view
		mat4 rotation = m_Rotation.toMatrix();
		mat4 translation(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			m_Position.x, m_Position.y, m_Position.z, 1);
		m_ViewMatrix = rotation * translation;
		
		// update perspective
		m_ProjectionMatrix = mat4::Perspective(m_Fov, m_AspectRatio, m_Near, m_Far);


		// update frustum


		/*

		Visual 3D representation of the frustum with all planes and the corner points

									[top]			  __o ftl
			 									 ____/	|\
			 							  ______/       |#\
							ntl o________/           ___|##\ o ftr  		
								|\	 ntr   _________/	|###|                      left
								|#\o______/	   ________ |###|     [far]				\
						[near]	|##|__________/		   o\###|                        \
							nbl	o\#|				fbl  \##|                         \
								  \|__________            \#|                         right
							   nbr o		  \____________\|o fbr
		
										[bottom]
		*/

		
		// Gram Schmidt
		// unit vector in Z direction (look direction)

		Vec3 position = m_Position;
		position.x *= -1;
		position.y *= -1;

		Vec3 Z = m_Rotation.toEulerAngles();
		Z.normalize();

		// Hack
		Z = Vec3(0,0,-1);

		/*LOG("Rotation");
		LOG(m_Rotation);
		*/
		Vec3 Y = UP - Z * Vec3::dotProduct(UP, Z);

		Y.normalize();

		// unit vector in X direction
		Vec3 X = Vec3::crossProduct(Y, Z);
		X.normalize();

		F32 tang = (float)tan(m_Fov * (PI / 180.0f) * 0.5f);
		
		// Width and Height of the near plane and the front plane
		// To Calculate the 8 corner points of the frustum
		F32 nw = m_Near * tang;
		F32 nh = nw / m_AspectRatio;
		F32 fw = m_Far * tang;
		F32 fh = fw / m_AspectRatio;

		// nc .. near plane center, fc .. far plane center
		// X, Y, Z are the unit vectors of the frustum
		Vec3 nc = position - Z * m_Near;
		Vec3 fc = position - Z * m_Far;

		// Points on the near plane
		Vec3 ntl = nc + (Y * nh) - (X * nw);
		Vec3 ntr = nc + (Y * nh) + (X * nw);
		Vec3 nbl = nc - (Y * nh) - (X * nw);
		Vec3 nbr = nc - (Y * nh) + (X * nw);

		// Points on the far plane
		Vec3 ftl = fc + (Y * fh) - (X * fw);
		Vec3 ftr = fc + (Y * fh) + (X * fw);
		Vec3 fbl = fc - (Y * fh) - (X * fw);
		Vec3 fbr = fc - (Y * fh) + (X * fw);

		// Set all border planes of the frustum
		planes[TOP].setPoints(ntr, ntl, ftl);
		planes[BOTTOM].setPoints(nbl, nbr, fbr);
		planes[LEFT].setPoints(ntl, nbl, fbl);
		planes[RIGHT].setPoints(nbr, ntr, fbr);
		planes[NEAR].setPoints(ntl, ntr, nbr);
		planes[FAR].setPoints(ftr, ftl, fbl);

		/*LOG("AspectRatio", m_AspectRatio);

		LOG("nc");
		LOG(nc);

		LOG("fc");
		LOG(fc);

		LOG("nh", nh);
		LOG("nw", nw);
		LOG("fh", fh);
		LOG("fw", fw);
		*/LOG("X,Y,Z");
		LOG(X);
		LOG(Y);
		LOG(Z);/*

		LOG("#####Points#######");
		LOG("ntl:");
		LOG( ntl);
		
		LOG("ntr: ");
		LOG(ntr);

		LOG("nbl");
		LOG(nbl);

		LOG("nbr");
		LOG(nbr);


		LOG("ftl:");
		LOG(ftl);

		LOG("ftr: ");
		LOG(ftr);

		LOG("fbl");
		LOG(fbl);

		LOG("fbr");
		LOG(fbr);*/
	}

	//--------------------------------------------------------------------------
	mat4 Camera::lookAt(const Vec3 &eye, const Vec3 &target, const Vec3 &up) 
	{
		Vec3 f = target - eye;
		f.normalize();

		Vec3 s = Vec3::crossProduct(up, f);
		s.normalize();

		Vec3 v = Vec3::crossProduct(f, s);

		mat4 rotation(-s.x, v.x,  -f.x, 0,
					   s.y, v.y,   f.y, 0,
					  -s.z, v.z,  -f.z, 0, 
					   0  ,    0,    0, 1);

		mat4 translation(1, 0, 0,  0,
						 0, 1, 0,  0,
						 0, 0, 1,  0,
						 eye.x, eye.y, eye.z,  1);

		mat4 result = translation  * rotation;
		return result;
	}

	//--------------------------------------------------------------------------
	void Camera::setPosition(const Vec3 &position) 
	{
	
		m_Position = position;
	}

	//--------------------------------------------------------------------------
	void Camera::Translate(const Vec3 &position) {
		Vec3 forward(m_ViewMatrix[2], m_ViewMatrix[6], m_ViewMatrix[10]);
		Vec3 strafe(m_ViewMatrix[0], m_ViewMatrix[4], m_ViewMatrix[8]);
		Vec3 up(m_ViewMatrix[1], m_ViewMatrix[5], m_ViewMatrix[9]);
	
		m_Position += forward * position.z * m_Speed;
		m_Position += up * position.y * m_Speed;
		m_Position += strafe * position.x * m_Speed;
		//m_Position += position;

		//std::cout << "Position: " << m_Position.x << " , " << m_Position.y << " , " << m_Position.z << std::endl;
	}

	//--------------------------------------------------------------------------
	mat4 Camera::getViewMatrix() const
	{
		return m_ViewMatrix;
	}

	//--------------------------------------------------------------------------
	mat4 Camera::getRotationMatrix() const 
	{
		mat4 result = m_ViewMatrix;
		result[12] = 0;
		result[13] = 0;
		result[14] = 0;
		return result;
	}

	//--------------------------------------------------------------------------
	Frustum Camera::getFrustum() const 
	{
		return *this;
	}

	//--------------------------------------------------------------------------
	void Camera::printInfo() 
	{
		LOG("FOV", m_Fov);
		LOG("Aspect", m_AspectRatio);
		LOG("near", m_Near);
		LOG("far", m_Far);
		LOG("Rotation",
			std::to_string(m_Rotation.x) + " , " +
			std::to_string(m_Rotation.y) + " , " +
			std::to_string(m_Rotation.z) + " , " +
			std::to_string(m_Rotation.w));

		LOG("ViewMatrix", m_ViewMatrix);
		LOG("TRANSLATION.X : ", m_ViewMatrix.elements[12]);

		LOG("m_Rotation",
			" X: " + std::to_string(m_Rotation.x) +
			" Y: " + std::to_string(m_Rotation.y) +
			" Z: " + std::to_string(m_Rotation.z) +
			" W: " + std::to_string(m_Rotation.w));

		mat4 translation(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		mat4 rotation(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

		mat4 result = rotation * translation;

		LOG("TEST MATRIX", result);
	}
}}