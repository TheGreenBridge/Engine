#include "mat4.h"
#include <sstream>

mat4::mat4(float diagonal)
{
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;

	elements[0 + 0 * 4] = diagonal;
	elements[1 + 1 * 4] = diagonal;
	elements[2 + 2 * 4] = diagonal;
	elements[3 + 3 * 4] = diagonal;
}

mat4::mat4()
{
	for (int i = 0; i < 4 * 4; i++)
		elements[i] = 0.0f;
}

mat4::mat4(	float x1, float x2, float x3, float x4,
			float y1, float y2, float y3, float y4,
			float z1, float z2, float z3, float z4,
			float w1, float w2, float w3, float w4) {

	elements[0] = x1;
	elements[1] = x2;
	elements[2] = x3;
	elements[3] = x4;
	elements[4] = y1;
	elements[5] = y2;
	elements[6] = y3;
	elements[7] = y4;
	elements[8] = z1;
	elements[9] = z2;
	elements[10] = z3;
	elements[11] = z4;
	elements[12] = w1;
	elements[13] = w2;
	elements[14] = w3;
	elements[15] = w4;
}

inline float toRadians(float degrees)
{
	return (float)(degrees * (PI / 180.0));
}

mat4 mat4::Perspective(float fov, float aspectRatio, float near, float far) {
	mat4 result(1.0f);

	float q = 1.0f / tan(toRadians(0.5f * fov));
	float a = q / aspectRatio;

	float b = (near + far) / (near - far);
	float c = (2.0f * near * far) / (near - far);

	result.elements[0 + 0 * 4] = a;
	result.elements[1 + 1 * 4] = q;
	result.elements[2 + 2 * 4] = b;
	result.elements[3 + 2 * 4] = -1.0f;
	result.elements[2 + 3 * 4] = c;
	result.elements[3 + 3 * 4] = 0;

	return result;
}

mat4 & mat4::operator *=(const mat4 &other) {
	return multiply(other);
}

mat4 mat4::operator * (const mat4 &other) const {
	mat4 result;
	float data[16];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			data[x + y * 4] = sum;
		}
	}
	memcpy(result.elements, data, 4 * 4 * sizeof(float));
	return result;
}

float & mat4::operator[](const int index) {
	return elements[index];
}

mat4& mat4::multiply(const mat4& other)
{
	float data[16];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += elements[x + e * 4] * other.elements[e + y * 4];
			}
			data[x + y * 4] = sum;
		}
	}
	memcpy(elements, data, 4 * 4 * sizeof(float));

	return *this;
}

mat4 mat4::multiply(const mat4 &other) const {
	mat4 result;

	float data[16];
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			float sum = 0.0f;
			for (int e = 0; e < 4; e++)
			{
				sum += result.elements[x + e * 4] * other.elements[e + y * 4];
			}
			data[x + y * 4] = sum;
		}
	}
	memcpy(result.elements, data, 4 * 4 * sizeof(float));

	return result;
}

mat4 mat4::Translate(const Vec3 &translation){
	
	mat4 result(1.0f);

	result.elements[0 + 3 * 4] = translation.x;
	result.elements[1 + 3 * 4] = translation.y;
	result.elements[2 + 3 * 4] = translation.z;
	
	return result;
}

mat4 mat4::Rotate(float angle, const Vec3& axis)
{
	mat4 result(1.0f);

	float r = toRadians(angle);
	float c = cos(r);
	float s = sin(r);
	float omc = 1.0f - c;

	float x = axis.x;
	float y = axis.y;
	float z = axis.z;

	result.elements[0 + 0 * 4] = x * omc + c;
	result.elements[1 + 0 * 4] = y * x * omc + z * s;
	result.elements[2 + 0 * 4] = x * z * omc - y * s;

	result.elements[0 + 1 * 4] = x * y * omc - z * s;
	result.elements[1 + 1 * 4] = y * omc + c;
	result.elements[2 + 1 * 4] = y * z * omc + x * s;

	result.elements[0 + 2 * 4] = x * z * omc + y * s;
	result.elements[1 + 2 * 4] = y * z * omc - x * s;
	result.elements[2 + 2 * 4] = z * omc + c;

	return result;
}