#include "Log.h"
#include <iostream>
#include <string>

#include <math/mat4.h>
#include <math/Quaternion.h>




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
#ifdef DEBUG
	std::cout << text << std::endl;
#endif
}

void LOG(const std::string title, const std::string text) {
#ifdef DEBUG
	std::cout << title << ": " << text << std::endl;
#endif
}

void LOG(const char* title, const int number) {
#ifdef DEBUG
	std::cout << title << ": " << number << std::endl;
#endif
}

void LOG(const char* title, const float number) {
#ifdef DEBUG
	std::cout << title << ": " << number << std::endl;
#endif
}

void LOG(const char* title, const unsigned int number) {
#ifdef DEBUG
	std::cout << title << ": " << number << std::endl;
#endif
}


// ERROR
void logError(const char* text, const char* file, U32 line) {
	std::cerr << "ERROR: " << text << file << line << std::endl;
	HALT();
}

void logDebug(const char * text, const char * file, U32 line)
{
	std::cout << text << file << ": " << line << std::endl;
}

void HALT()
{
	//system("Color C");
	std::cout << "Enter Taste druecken ..." << std::endl;
	std::getchar();
	//system("Color");
}
