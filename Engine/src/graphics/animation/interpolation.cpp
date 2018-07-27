//------------------------------------------------------------------------------
// interpolation.cpp
//
// Provides functions to interpolate vectors, quaternions, etc.
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include "interpolation.h"

#include <graphics\animation\skinning\JointPose.h>
#include <math\Quaternion.h>
#include <math\Vec3.h>
#include <math\mat4.h>
#include <entity\component\Transform.h>


namespace engine {	namespace animation {

    //--------------------------------------------------------------------------
	Quaternion ani_lerp(const Quaternion &qa, const Quaternion &qb, 
		const float beta) {
		Quaternion result(0, 0, 0, 1);
		result = (qa*(1.0f - beta) + qb*beta);
		result = result / result.length();
		result.normalize();
		return result;
	}

	//--------------------------------------------------------------------------
	Vec3 ani_lerp(const Vec3 &va, const Vec3 &vb, const float beta) {
		Vec3 result;
		result = (va*(1.0f - beta) + vb*beta);
		return result;
	}

	//--------------------------------------------------------------------------
	float ani_lerp(const float &fa, const float &fb, const float beta) {
		float result;
		result = (fa*(1.0f - beta) + fb*beta);
		return result;
	}
	
	//--------------------------------------------------------------------------
	Transform ani_transform(const Transform& trans_from, 
		const Transform& trans_to, const float beta) {
		Transform result;
		result.position = ani_lerp(trans_from.position, trans_to.position, beta);
		result.rotation = ani_lerp(trans_from.rotation, trans_to.rotation, beta);
		result.scale = ani_lerp(trans_from.scale, trans_to.scale, beta);
		return result;
	}
	
	//--------------------------------------------------------------------------
	JointPose ani_lerp(const JointPose& pose1, const JointPose &pose2, 
		const float beta) {
		JointPose result;
		result.m_trans = pose1.m_trans;
		//result.m_trans = ani_lerp(pose1.m_trans, pose2.m_trans, beta);
		result.m_rot = ani_lerp(pose1.m_rot, pose2.m_rot, beta);
		result.m_scale = ani_lerp(pose1.m_scale, pose2.m_scale, beta);
		return result;
	}

}}