#include "Quaternion.h"
#include <cmath>

Quaternion::Quaternion(const Vec3 &axis, const float angle) {
	setRotation(axis, angle);
}

Quaternion::Quaternion(float x, float y, float z, float w)
	: x(x), y(y), z(z), w(w)
{ }

Quaternion &Quaternion::operator*(const Quaternion &other) {
	w = w*other.w - x*other.x - y*other.y - z*other.z;
	x = w*other.x + x*other.w + y*other.z - z*other.y;
	y = w*other.y - y*other.z + y*other.w + z*other.x;
	z = w*other.z + x*other.y - y*other.x + z*other.w;

	return *this;
}

Quaternion Quaternion::operator*(const Quaternion &other) const {
	Quaternion result(0,0,0,1);
	result.w = w*other.w - x*other.x - y*other.y - z*other.z;
	result.x = w*other.x + x*other.w + y*other.z - z*other.y;
	result.y = w*other.y - y*other.z + y*other.w + z*other.x;
	result.z = w*other.z + x*other.y - y*other.x + z*other.w;

	return result;
}

Quaternion Quaternion::operator * (const float value) const {
	Quaternion result(x, y, z, w);
	result.x *= value;
	result.y *= value;
	result.z *= value;
	result.w *= value;
	return result;
}

Quaternion Quaternion::operator +(const Quaternion &other) const {
	Quaternion result(x, y, z, w);
	result.x += other.x;
	result.y += other.y;
	result.z += other.z;
	result.w += other.w;
	return result;
}

Quaternion Quaternion::operator /(const Quaternion &other) const {
	Quaternion result(x, y, z, w);
	result.x /= other.x;
	result.y /= other.y;
	result.z /= other.z;
	result.w /= other.w;
	return result;
}

Quaternion Quaternion::operator /(const float value) const {
	Quaternion result(x, y, z, w);
	result.x /= value;
	result.y /= value;
	result.z /= value;
	result.w /= value;
	return result;
}

void Quaternion::setRotation(const Vec3 &axis, float angle) {
	float fAngle = angle * 0.5f;
	w = cosf(fAngle);
	x = axis.x * sinf(fAngle);
	y = axis.y * sinf(fAngle);
	z = axis.z * sinf(fAngle);
}

void Quaternion::setRotation(const Vec3 &angles) {
	w = 1;
	x = 0;
	y = 0;
	z = 0;

	rotate(Vec3(1, 0, 0), angles.x);
	rotate(Vec3(0, 1, 0), angles.y);
	rotate(Vec3(0, 0, 1), angles.z);
}

void Quaternion::rotate(const Quaternion & other) {
	w = w*other.w - x*other.x - y*other.y - z*other.z;
	x = w*other.x + x*other.w + y*other.z - z*other.y;
	y = w*other.y - y*other.z + y*other.w + z*other.x;
	z = w*other.z + x*other.y - y*other.x + z*other.w;
}

void Quaternion::rotate(const Vec3 &axis, float angle) {
	
	float fAngle = angle * 0.5f;
	float sin_angle = sinf(fAngle);

	float w2 = cosf(fAngle);
	float x2 = axis.x * sin_angle;
	float y2 = axis.y * sin_angle;
	float z2 = axis.z * sin_angle;

	w = w*w2 - x*x2 - y*y2 - z*z2;
	x = w*x2 + x*w2 + y*z2 - z*y2;
	y = w*y2 - y*z2 + y*w2 + z*x2;
	z = w*z2 + x*y2 - y*x2 + z*w2;
}

void Quaternion::setComponents(const float qx, const float qy, const float qz, const float qw) {
	x = qx;
	y = qy;
	z = qz;
	w = qw;

}

void Quaternion::rotate(const Vec3 &angles) {
	rotate(Vec3(1, 0, 0), angles.x);
	rotate(Vec3(0, 1, 0), angles.y);
	rotate(Vec3(0, 0, 1), angles.z);
}

Quaternion Quaternion::conjugate() const {
	return Quaternion(-x, -y, -z, w);
}

Quaternion Quaternion::inverse() {
	Quaternion result(0,0,0,0);
	/*result = (*this).conjugate;
	result.normalize();	*/
	return result;
}

float norm(const Quaternion &quaternion) {
	float result;
	result = quaternion.x * quaternion.x;
	result += quaternion.y * quaternion.y;
	result += quaternion.z * quaternion.z;
	result += quaternion.w * quaternion.w;
	return result;
}

float Length(const Quaternion &quaternion) {
	return sqrt(norm(quaternion));
}

float Quaternion::length() const {
	return x*x + y*y + z*z + w*w;
}

void Quaternion::normalize() {
	float L = Length(*this);
	x /= L;
	y /= L;
	z /= L;
	w /= L;
}

void Quaternion::setEulerAngles(const float yaw, const float pitch, const float roll) {
	
	//ORIGINAL : yaw, roll, pitch!

	float t0 = std::cos(yaw * 0.5f);
	float t1 = std::sin(yaw * 0.5f);
	float t2 = std::cos(roll * 0.5f);
	float t3 = std::sin(roll * 0.5f);
	float t4 = std::cos(pitch * 0.5f);
	float t5 = std::sin(pitch * 0.5f);

	w = t0 * t2 * t4 + t1 * t3 * t5;
	x = t0 * t3 * t4 - t1 * t2 * t5;
	y = t0 * t2 * t5 + t1 * t3 * t4;
	z = t1 * t2 * t4 - t0 * t3 * t5;
}

mat4 Quaternion::toMatrix() {
	mat4 result(0);
	normalize();
	result[0] = 1 - 2*y*y - 2*z*z;
	result[1] = 2 * x*y + 2 * z*w;
	result[2] = 2 * x*z - 2 * y*w;
	
	result[4] = 2 * x*y - 2 * z*w;
	result[5] = 1 - 2 * x*x - 2 * z*z;
	result[6] = 2 * y*z + 2 * x*w;

	result[8] = 2 * x*z + 2 * y*w;
	result[9] = 2 * y*z - 2 * x*w;
	result[10] = 1 - 2 * x*x - 2 * y*y;

	result[15] = 1;

	return result;
}

Vec3 Quaternion::toEulerAngles() const {
	
	return Vec3(atan2(2.0f*x*w - 2.0f*y*z, 1.0f - 2.0f*x*x - 2.0f*z*z),
		atan2(2.0f*y*w - 2.0f*x*z, 1.0f - 2.0f*y*y - 2.0f*z*z),
		asin(2.0f*x*y + 2.0f*z*w));
}