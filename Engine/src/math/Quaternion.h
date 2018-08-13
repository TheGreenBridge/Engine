#pragma once

#include "Vec3.h"
#include "mat4.h"

struct Quaternion 
{
	float x, y, z, w;

	Quaternion() = default;
	Quaternion(const Vec3 &xyz, const float w);
	Quaternion(float x, float y, float z, float w);

	Quaternion & operator * (const Quaternion &other);
	
	Quaternion operator * (const Quaternion &other) const;
	Quaternion operator * (const float value) const;

	Quaternion operator +(const Quaternion &other) const;
	Quaternion operator /(const Quaternion &other) const;
	Quaternion operator /(const float value) const;

	void rotate(const Quaternion &other);
	void rotate(const Vec3 &axis, float angle);
	void rotate(const Vec3 &rotationAngles);

	void setComponents(const float qx, const float qy, const float qz, const float qw);

	float length() const;
	
	void setRotation(const Vec3 &axis, float angle);
	void setRotation(const Vec3 &axis);
	
	Quaternion conjugate() const;
	Quaternion inverse();
	
	void normalize();
	
	void setEulerAngles(const float yaw, const float pitch, const float roll);

	mat4 toMatrix();
	Vec3 toEulerAngles() const;
};