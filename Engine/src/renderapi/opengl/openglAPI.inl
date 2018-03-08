#pragma once
//Render API for OpenGL
/*
#include <GL\glew.h>

typedef GLuint uint;

//#include "../../utils/log.h"
//
inline void printRenderAPI() {
	//PRINTLOG("OpenGL");
	//PRINTLOG(glGetString(GL_VERSION));
}

inline void genBuffers(const uint size, uint *buffers) {
	glCreateBuffers(size, buffers);
}

inline void bindBuffer(const uint bufferID) {
	glBindBuffer(GL_ARRAY_BUFFER, bufferID);
}

inline void unbindBuffer() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

inline void bufferData(const uint length, const float *data) {
	glBufferData(GL_ARRAY_BUFFER, length, data, GL_STATIC_DRAW);
}

inline void vertexAttribPointer(const uint dimensions) {
	// GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 0, 0);
}

inline void enableVertexAttribArray(const uint attributeID) {
	glEnableVertexAttribArray(attributeID);
}


// Textures
inline void genTextures(const uint size, uint *storage) {
	glGenTextures(size, storage);
}

inline void bindTexture(const uint storage) {
	glBindTexture(GL_TEXTURE_2D, storage);
}

inline void activeTexture(const uint textureUnit) {
	glActiveTexture(GL_TEXTURE0 + textureUnit);
}

inline void texParameteri() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

inline void texImage2D(const int level, const uint width, uint height, int border, const void *pixels) {
	glTexImage2D(GL_TEXTURE_2D, level, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
}

inline void generateMipmap() {
	glGenerateMipmap(GL_TEXTURE_2D);
}

// SHADER
inline uint createProgram() { return glCreateProgram(); }

inline uint createVertexShader() { return glCreateShader(GL_VERTEX_SHADER); }

inline uint createFragmentShader() { return glCreateShader(GL_FRAGMENT_SHADER); }

inline void shaderSource(uint shader, int count, const char* const *source, const int *length) {
	glShaderSource(shader, count, source, length);
}

inline void compileShader(uint shader) { glCompileShader(shader); }

inline void getShaderiv(uint shader, int *param) {
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, param);
}

inline void getShaderInfoLog(uint shader, uint buffsize, int *length, char *infolog) {
	glGetShaderInfoLog(shader, buffsize, length, infolog);
}

inline void deleteShader(uint shader) { glDeleteShader(shader); }

inline void attachShader(uint program, uint shader) { glAttachShader(program, shader); }

inline void linkProgram(uint program) { glLinkProgram(program); }

inline void validateProgram(uint program) { glValidateProgram(program); }

inline void useProgram(uint program) { glUseProgram(program); }

inline void deleteProgram(uint program) { glDeleteProgram(program); }

// SHADER - UNIFORMS - GET

inline int getUniformLocation(uint program, const char *name) { return glGetUniformLocation(program, name); }

// SHADER - UNIFORMS - SET

inline void uniform3f(int location, float v1, float v2, float v3) {
	glUniform3f(location, v1, v2, v3);
}

inline void uniformMatrix4fv(int location, const float *value) {
	glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

*/