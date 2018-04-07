#include "Log.h"
#include <iostream>
#include "../math/mat4.h"
#include "../math/Quaternion.h"
#include <string>

#define PRINTLOG(a) std::cout << a << std::endl
#define NEWLINE() std::cout << std::endl

void LOG(std::string title, const mat4 &matrix) {

	NEWLINE();

	PRINTLOG("mat4" + title);

	std::cout << matrix.elements[0] << ", " << matrix.elements[1] << ", " << matrix.elements[2] << ", " << matrix.elements[3] << ", " << std::endl;
	std::cout << matrix.elements[4] << ", " << matrix.elements[5] << ", " << matrix.elements[6] << ", " << matrix.elements[7] << ", " << std::endl;
	std::cout << matrix.elements[8] << ", " << matrix.elements[9] << ", " << matrix.elements[10] << ", " << matrix.elements[11] << ", " << std::endl;
	std::cout << matrix.elements[12] << ", " << matrix.elements[13] << ", " << matrix.elements[14] << ", " << matrix.elements[15] << ", " << std::endl;
}

void LOG(const Quaternion &quat) {
	NEWLINE();
	PRINTLOG("Quaternion");
	std::cout << "X: " << quat.x << " Y: " << quat.y << " Z: " << quat.z << " W: " << quat.w << std::endl;
}

void LOG(const Vec3 &v) {
	NEWLINE();
	PRINTLOG("Vector");
	std::cout << "X: " << v.x << " Y: " << v.y << " Z: " << v.z << std::endl;
}

void LOG(const std::string text) {
	std::cout << text << std::endl;
}

void LOG(const std::string title, const std::string text) {
	std::cout << title << ": " << text << std::endl;
}

void LOG(const char* title, const int number) {
	std::cout << title << ": " << number << std::endl;
}

void LOG(const char* title, const float number) {
	std::cout << title << ": " << number << std::endl;
}

void LOG(const char* title, const unsigned int number) {
	std::cout << title << ": " << number << std::endl;
}

// ERROR
void LOG_ERROR(const char* text) {
	std::cerr << "ERROR: " << text << std::endl;
	HALT();
}

void HALT()
{
	//system("Color C");
	std::cout << "Beliebige Taste druecken ..." << std::endl;
	std::getchar();
	//system("Color");
}
