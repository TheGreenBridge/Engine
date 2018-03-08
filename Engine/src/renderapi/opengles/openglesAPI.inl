#pragma once
#include "../../types.h"

#include <gl\glew.h>

// Render API for OpenGL ES

namespace GPU {

	inline GLenum GetError() {
		return glGetError();
	}

	inline void GenBuffers(GLsizei n, GLuint* buffers) {
		glGenBuffers(n, buffers);
	}

	inline void DeleteBuffers(GLsizei n, GLuint* buffers) {
		glDeleteBuffers(n, buffers);
	}

	inline void BindBuffer(GLenum type, GLint buffer) {
		glBindBuffer(type, buffer);
	}

	inline void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage) {
		glBufferData(target, size, data, usage);
	}
	
	inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data) {
		glBufferSubData(target, offset, size, data);
	}

	inline GLboolean IsBuffer(GLuint buffer) {
		return glIsBuffer(buffer);
	}

	inline void GetBufferParameteriv(GLenum target, GLenum value, GLint* data) {
		glGetBufferParameteriv(target, value, data);
	}

	inline void DepthRangef(GLclampf nearVal, GLclampf farVal) {
		glDepthRangef(nearVal, farVal);
	}

	inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height) {
		glViewport(x, y, width, height);
	}

	// Pixel Reading
	inline void ReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid * data) {
		glReadPixels(x, y, width, height, format, type, data);
	}

	inline void VertexAttrib1f(GLuint index, GLfloat v0) {
		glVertexAttrib1f(index, v0);
	}

	inline void VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1) {
		glVertexAttrib2f(index, v0, v1);
	}

	inline void VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2) {
		glVertexAttrib3f(index, v0, v1, v2);
	}

	inline void VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
		glVertexAttrib4f(index, v0, v1, v2, v3);
	}

	inline void VertexAttrib1fv(GLuint index, const GLfloat *v) {
		glVertexAttrib1fv(index, v);
	}

	inline void VertexAttrib2fv(GLuint index, const GLfloat *v) {
		glVertexAttrib2fv(index, v);
	}

	inline void VertexAttrib3fv(GLuint index, const GLfloat *v) {
		glVertexAttrib3fv(index, v);
	}

	inline void VertexAttrib4fv(GLuint index, const GLfloat *v) {
		glVertexAttrib4fv(index, v);
	}

	inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer) {
		glVertexAttribPointer(index, size, type, normalized, stride, pointer);
	}
	inline void EnableVertexAttribArray(GLuint index) {
		glEnableVertexAttribArray(index);
	}
	inline void DisableVertexAttribArray(GLuint index) {
		glDisableVertexAttribArray(index);
	}

	// Draw Calls
	inline void DrawArrays(GLenum mode, GLint first, GLsizei count) {
		glDrawArrays(mode, first, count);
	}

	inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices) {
		glDrawElements(mode, count, type, indices);
	}


	// Textures
	inline void ActiveTexture(GLenum texture) {
		glActiveTexture(texture);
	}
	
	inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data) {
		glTexImage2D(target, level, internalformat, width, height, border, format, type, data);
	}
	
	inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
		glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
	}
	
	inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data) {
		glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, data);
	}

	inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
		glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
	}

	inline void CompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid * data) {
		glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
	}

	inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data) {
		glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
	}

	inline void TexParameterf(GLenum target, GLenum pname, GLfloat param) {
		glTexParameterf(target, pname, param);
	}

	inline void TexParameteri(GLenum target, GLenum pname, GLint param) {
		glTexParameteri(target, pname, param);
	}

	inline void GenerateMipmap(GLenum target) {
		glGenerateMipmap(target);
	}

	inline void BindTexture(GLenum target, GLuint texture) {
		glBindTexture(target, texture);
	}

	inline void DeleteTextures(GLsizei n, const GLuint * textures) {
		glDeleteTextures(n, textures);
	}

	inline void GenTextures(GLsizei n, GLuint * textures) {
		glGenTextures(n, textures);
	}

	inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
		glGetTexParameterfv(target, pname, params);
	}

	inline void GetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
		glGetTexParameteriv(target, pname, params);
	}

	inline GLboolean IsTexture(GLuint texture) {
		return glIsTexture(texture);
	}

	// Renderoptions
	inline void LineWith(GLfloat width) {
		glLineWidth(width);
	}

	inline void FrontFace(GLenum mode) {
		glFrontFace(mode);
	}

	inline void CullFace(GLenum mode) {
		glCullFace(mode);
	}

	inline void Enable(GLenum cap) {
		glEnable(cap);
	}

	inline void Disable(GLenum cap) {
		glDisable(cap);
	}

	inline void PolygonOffset(GLfloat factor, GLfloat units) {
		glPolygonOffset(factor, units);
	}

	inline void PixelStorei(GLenum pname, GLint param) {
		glPixelStorei(pname, param);
	}

	// Shader
	inline GLuint CreateShader(GLenum shaderType) {
		return glCreateShader(shaderType);
	}

	inline void ShaderSource(GLuint shader, GLsizei count, const GLchar * const *string, const GLint *length) {
		glShaderSource(shader, count, string, length);
	}

	inline void CompileShader(GLuint shader) {
		glCompileShader(shader);
	}

	inline void ReleaseShaderCompiler() {
		glReleaseShaderCompiler();
	}

	inline void DeleteShader(GLuint shader) {
		glDeleteShader(shader);
	}

	inline void ShaderBinary(GLsizei n, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length) {
		glShaderBinary(n, shaders, binaryformat, binary, length);
	}

	inline GLuint CreateProgram() {
		return glCreateProgram();
	}

	inline void AttachShader(GLuint program, GLuint shader) {
		glAttachShader(program, shader);
	}

	inline void DetachShader(GLuint program, GLuint shader) {
		glDetachShader(program, shader);
	}

	inline void LinkProgram(GLuint program) {
		glLinkProgram(program);
	}

	inline void UseProgram(GLuint program) {
		glUseProgram(program);
	}

	inline void DeleteProgram(GLuint program) {
		glDeleteProgram(program);
	}

	inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
		glGetActiveAttrib(program, index, bufSize, length, size, type, name);
	}

	inline void GetAttribLocation(GLuint program, const GLchar *name) {
		glGetAttribLocation(program, name);
	}

	inline void BindAttribLocation(GLuint program, GLuint index, const GLchar *name){
		glBindAttribLocation(program, index, name);
	}

	inline GLint GetUniformLocation(GLuint program, const GLchar *name) {
		return glGetUniformLocation(program, name);
	}

	inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, GLchar *name) {
		glGetActiveUniform(program, index, bufSize, length, size, type, name);
	}

	// Uniforms
	inline void Uniform1f(GLint location, GLfloat v0) {
		glUniform1f(location, v0);
	}

	inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1) {
		glUniform2f(location, v0, v1);
	}

	inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
		glUniform3f(location, v0, v1, v2);
	}

	inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
		glUniform4f(location, v0, v1, v2, v3);
	}

	inline void Uniform1i(GLint location, GLint v0) {
		glUniform1i(location, v0);
	}

	inline void Uniform2i(GLint location, GLint v0, GLint v1) {
		glUniform2i(location, v0, v1);
	}

	inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
		glUniform3i(location, v0, v1, v2);
	}

	inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
		glUniform4i(location, v0, v1, v2, v3);
	}

	inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, float* value) {
		glUniformMatrix2fv(location, count, transpose, value);
	}

	inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, float* value) {
		glUniformMatrix3fv(location, count, transpose, value);
	}

	inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, float* value) {
		glUniformMatrix4fv(location, count, transpose, value);
	}


	inline void ValidateProgram(GLuint program) {
		glValidateProgram(program);
	}

	inline GLboolean IsShader(GLuint shader) {
		return glIsShader(shader);
	}

	inline void GetShaderiv(GLuint shader, GLenum pname, GLint *params) {
		glGetShaderiv(shader, pname, params);
	}

	inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders) {
		glGetAttachedShaders(program, maxCount, count, shaders);
	}

	inline void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, GLchar *infoLog) {
		glGetShaderInfoLog(shader, maxLength, length, infoLog);
	}

	inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *source) {
		glGetShaderSource(shader, bufSize, length, source);
	}

	inline void GetShaderPrecisionFormat(GLenum shaderType, GLenum precisionType, GLint *range, GLint *precision) {
		glGetShaderPrecisionFormat(shaderType, precisionType, range, precision);
	}

	inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params) {
		glGetVertexAttribfv(index, pname, params);
	}

	inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint *params) {
		glGetVertexAttribiv(index, pname, params);
	}

	inline void GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer) {
		glGetVertexAttribPointerv(index, pname, pointer);
	}

	inline void GetUniformfv(GLuint program, GLint location, GLfloat *params) {
		glGetUniformfv(program, location, params);
	}

	inline void GetUniformiv(GLuint program, GLint location, GLint *params) {
		glGetUniformiv(program, location, params);
	}

	inline GLboolean IsProgram(GLuint program) {
		return glIsProgram(program);
	}

	inline void GetProgramiv(GLuint program, GLenum pname, GLint *params) {
		glGetProgramiv(program, pname, params);
	}

	inline void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, GLchar *infoLog) {
		glGetProgramInfoLog(program, maxLength, length, infoLog);
	}
	
	inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height) {
		glScissor(x, y, width, height);
	}

	inline void SampleCoverage(GLclampf value, GLboolean invert) {
		glSampleCoverage(value, invert);
	}

	inline void StencilFunc(GLenum func, GLint ref, GLuint mask) {
		glStencilFunc(func, ref, mask);
	}

	inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
		glStencilFuncSeparate(face, func, ref, mask);
	}

	inline void StencilOp(GLenum sfail, GLenum dpfail, GLenum dppass) {
		glStencilOp(sfail, dpfail, dppass);
	}

	inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
		glStencilOpSeparate(face, sfail, dpfail, dppass);
	}

	inline void DepthFunc(GLenum func) {
		glDepthFunc(func);
	}

	// Blending

	// mode{GL_FUNC_ADD, GL_FUNC_SUBTRACT, or GL_FUNC_REVERSE_SUBTRACT}
	inline void BlendEquation(GLenum mode) {
		glBlendEquation(mode);
	}

	inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
		glBlendEquationSeparate(modeRGB, modeAlpha);
	}

	inline void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha) {
		glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
	}
	/* sfactor{GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA,
	GL_ONE_MINUS_CONSTANT_ALPHA, and GL_SRC_ALPHA_SATURATE.The initial value is GL_ONE}*/
	inline void BlendFunc(GLenum sfactor, GLenum dfactor) {
		glBlendFunc(sfactor, dfactor);
	}

	inline void BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
		glBlendColor(red, green, blue, alpha);
	}

	inline void Flush() {
		glFlush();
	}

	inline void Finish() {
		glFinish();
	}

	inline void Hint(GLenum target, GLenum mode) {
		glHint(target, mode);
	}

	inline void GetBooleanv(GLenum pname, GLboolean *params) {
		glGetBooleanv(pname, params);
	}
	inline void GetIntegerv(GLenum pname, GLint *params) {
		glGetIntegerv(pname, params);
	}

	inline void GetFloatv(GLenum pname, GLfloat *params) {
		glGetFloatv(pname, params);
	}

	inline GLboolean IsEnabled(GLenum cap) {
		return glIsEnabled(cap);
	}

	inline const GLubyte* GetString(GLenum name) {
		return glGetString(name);
	}

	// Buffers

	inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
		glColorMask(red, green, blue, alpha);
	}
	
	inline void DepthMask(GLboolean flag) {
		glDepthMask(flag);
	}

	inline void StencilMask(GLuint mask) {
		glStencilMask(mask);
	}

	inline void StencilMaskSeparate(GLenum face, GLuint mask) {
		glStencilMaskSeparate(face, mask);
	}

	inline void Clear(GLbitfield mask) {
		glClear(mask);
	}

	inline void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
		glClearColor(red, green, blue, alpha);
	}

	inline void ClearDepth(GLclampf depth) {
		glClearDepth(depth);
	}

	inline void ClearStencil(GLint s) {
		glClearStencil(s);
	}

	// Framebuffer

	inline void BindFramebuffer(GLenum target, GLuint framebuffer) {
		glBindFramebuffer(target, framebuffer);		
	}

	inline void DeleteFramebuffers(GLsizei n, const GLuint * framebuffers) {
		glDeleteFramebuffers(n, framebuffers);
	}

	inline void GenFramebuffers(GLsizei n, GLuint * framebuffers) {
		glGenFramebuffers(n, framebuffers);
	}

	inline void BindRenderbuffer(GLenum target, GLuint renderbuffer) {
		glBindRenderbuffer(target, renderbuffer);
	}

	inline void DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) {
		glDeleteRenderbuffers(n, renderbuffers);
	}

	inline void GenRenderbuffers(GLsizei n, GLuint * renderbuffers) {
		glGenRenderbuffers(n, renderbuffers);
	}

	inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
		glRenderbufferStorage(target, internalformat, width, height);
	}

	inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
		glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
	}

	inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
		glFramebufferTexture2D(target, attachment, textarget, texture, level);
	}

	inline GLenum CheckFramebufferStatus(GLenum target) {
		return glCheckFramebufferStatus(target);
	}

	inline GLboolean IsFramebuffer(GLuint framebuffer) {
		return glIsFramebuffer(framebuffer);
	}

	inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
		glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
	}

	inline GLboolean IsRenderbuffer(GLuint renderbuffer) {
		return glIsRenderbuffer(renderbuffer);
	}

	inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) {
		glGetRenderbufferParameteriv(target, pname, params);
	}

}
