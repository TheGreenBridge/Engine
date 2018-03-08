#pragma once

// forward declaration
struct mat4;
struct Quaternion;
struct Vec3;
struct Transform;

namespace engine {
	namespace animation {
		// forward declaration
		struct JointPose;
		
		Quaternion ani_lerp(const Quaternion &qa, const Quaternion &qb, const float beta);

		Vec3 ani_lerp(const Vec3 &qa, const Vec3 &qb, const float beta);

		float ani_lerp(const float &fa, const float &fb, const float beta);

		Transform ani_transform(const Transform& trans_from, const Transform& trans_to, const float beta);

		JointPose ani_lerp(const JointPose& pose1, const JointPose &pose2, const float beta);
	}
}