#pragma once

// size = 4 * 3 = 12 bytes
struct Vec3 {
	float x, y, z;
	Vec3(float const x, float const y, const float z) : x(x), y(y), z(z) {}
	Vec3() : x(0), y(0), z(0) { }

	Vec3 & operator+=(const Vec3 &other);
	Vec3 & operator+=(const float value);
	Vec3 & operator/=(const float value);
	Vec3 & operator-=(const Vec3 &other);

	Vec3 operator + (const Vec3 &other) const;
	Vec3 operator -(const Vec3 &other) const;
	Vec3 operator * (const float value) const;

	float length();
	void normalize();

	static float dotProduct(const Vec3 &vector1, const Vec3 &vector2);
	static Vec3 crossProduct(const Vec3 &vector1, const Vec3 &vector2);
	static Vec3 normalize(Vec3 &vector);
};




const Vec3 UP(0, 1, 0);
const Vec3 LEFT(1, 0, 0);
const Vec3 FORWARD(0, 0, 1);

const Vec3 XAXIS(1, 0, 0);
const Vec3 YAXIS(0, 1, 0);
const Vec3 ZAXIS(0, 0, 1);
