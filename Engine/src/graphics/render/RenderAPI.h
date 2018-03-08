#pragma once

/*
#define OPENGL

#include "../../types.h"
//#include "gltypes.h"

// all functions from the APIs

inline void printRenderAPI();

// BUFFER
inline int createBuffer();
inline int createVertexArray();
inline int createFrameBuffer();
inline int createRenderBuffer();
inline void createVertexArrays(const I32 size, I32 *array);
inline void genBuffers(const U32 size, U32 *buffers);
//Binding
inline void bindBuffer(const U32 bufferID);
inline void unbindBuffer();
inline void bindVertexBuffer();

inline void bufferData(const U32 length, const F32 *data);
inline void vertexAttribPointer();
inline void enableVertexAttribArray(const U32 attributeID);

// TEXTURE
inline void genTextures(const U32 size, U32 *storage);
inline void bindTexture(const U32 storage);
inline void activeTexture(const U32 textureUnit);
inline void texParameteri();
inline void texImage2D(const I32 level, const U32 width, U32 height, I32 border, const void *pixels);
inline void generateMipmap();

// SHADER
inline U32 createVertexShader();
inline U32 createFragmentShader();
inline void shaderSource(U32 shader, I32 count, char* const *string, const I32 *lenght);
inline void compileShader(U32 shader);

// SHADER - ERROR
inline void getShaderiv(U32 shader, int *param);
inline void getShaderInfoLog(U32 shader, U32 buffsize, I32 *length, char *infolog);
inline void deleteShader(U32 shader);


// SHADER - PROGRAM
inline U32 createProgram();
inline void useProgram(U32 program);
inline void linkProgram(U32 program);
inline void attachShader(U32 program, U32 shader);
inline void validateProgram(U32 program);
inline void deleteProgram(U32 program);

// SHADER - UNIFORMS
// UNIFORMS - GET
inline I32 getUniformLocation(U32 program, const char *name);

// UNIFORMS - SET
inline void uniform3f(I32 location, const F32 v1, const F32 v2, const F32 v3);
inline void uniformMatrix4fv(I32 location, const F32 *value);


// ######################################
// OPEN GL Functions

namespace GPU {

	//inline GLenum GetError();
	//inline void GenBuffers(GLsizei n, GLuint* buffers);
	//inline void DeleteBuffers(GLsizei n, GLuint* buffers);
	//inline void BindBuffer(GLenum type, GLint buffer);
	////inline void BufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
	////inline void BufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
	//inline unsigned char IsBuffer(GLuint buffer);
	//inline void GetBufferParameteriv(GLenum target, GLenum value, GLint* data);
	//inline void DepthRangef(GLclampf nearVal, GLclampf farVal);
	//inline void Viewport(GLint x, GLint y, GLsizei width, GLsizei height);


	//// Pixel Reading
	//inline void ReadPixels(GLint x,	GLint y, GLsizei width, GLsizei height, GLenum format,	GLenum type, GLvoid * data);

	//inline void VertexAttrib1f(GLuint index, GLfloat v0);
	//inline void VertexAttrib2f(GLuint index, GLfloat v0, GLfloat v1);
	//inline void VertexAttrib3f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2);
	//inline void VertexAttrib4f(GLuint index, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

	//inline void VertexAttrib1fv(GLuint index, const GLfloat *v);
	//inline void VertexAttrib2fv(GLuint index, const GLfloat *v);
	//inline void VertexAttrib3fv(GLuint index, const GLfloat *v);
	//inline void VertexAttrib4fv(GLuint index, const GLfloat *v);

	//inline void VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, GLvoid *pointer);
	//inline void EnableVertexAttribArray(GLuint index);
	//inline void DisableVertexAttribArray(GLuint index);

	//// Draw Calls
	//inline void DrawArrays(GLenum mode, GLint first, GLsizei count);
	//inline void DrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices);


	//// Textures
	//inline void ActiveTexture(GLenum texture);
	//inline void TexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid * data);
	//inline void CopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x,	GLint y, GLsizei width, GLsizei height, GLint border);
	//inline void TexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid * data);
	//inline void CopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
	//inline void CompressedTexImage2D(GLenum target,	GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize,	const GLvoid * data);
	//inline void CompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid * data);
	//inline void TexParameterf(GLenum target, GLenum pname, GLfloat param);
	//inline void TexParameteri(GLenum target, GLenum pname, GLint param);
	//inline void GenerateMipmap(GLenum target);
	//inline void BindTexture(GLenum target, GLuint texture);
	//inline void DeleteTextures(GLsizei n, const GLuint * textures);
	//inline void GenTextures(GLsizei n, GLuint * textures);
	//inline void GetTexParameterfv(GLenum target, GLenum pname, GLfloat * params);
	//inline void GetTexParameteriv(GLenum target, GLenum pname, GLint * params);
	//inline unsigned char IsTexture(GLuint texture);

	//// Renderoptions
	//inline void LineWith(GLfloat width);
	//inline void FrontFace(GLenum mode);
	//inline void CullFace(GLenum mode);

	//inline void Enable(GLenum cap);
	//inline void Disable(GLenum cap);

	//inline void PolygonOffset(GLfloat factor, GLfloat units);
	//inline void PixelStorei(GLenum pname, GLint param);

	//// Shader
	//inline GLuint CreateShader(GLenum shaderType);
	//inline void ShaderSource(GLuint shader, GLsizei count, const char * const *string, const GLint *length);
	//inline void CompileShader(GLuint shader);
	//inline void ReleaseShaderCompiler();
	//inline void DeleteShader(GLuint shader);
	//inline void ShaderBinary(GLsizei n, const GLuint *shaders, GLenum binaryformat, const void *binary, GLsizei length);

	//inline GLuint CreateProgram();
	//inline void AttachShader(GLuint program, GLuint shader);
	//inline void DetachShader(GLuint program, GLuint shader);
	//inline void LinkProgram(GLuint program);
	//inline void UseProgram(GLuint program);
	//inline void DeleteProgram(GLuint program);

	//inline void GetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, char *name);
	//inline void GetAttribLocation(GLuint program, const char *name);
	//inline void BindAttribLocation(GLuint program, GLuint index, const char *name);
	//inline GLint GetUniformLocation(GLuint program, const char *name);
	//inline void GetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei *length, GLint *size, GLenum *type, char *name);

	//// Uniforms
	//inline void Uniform1f(GLint location, GLfloat v0);
	//inline void Uniform2f(GLint location, GLfloat v0, GLfloat v1);
	//inline void Uniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
	//inline void Uniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
	//inline void Uniform1i(GLint location, GLint v0);
	//inline void Uniform2i(GLint location, GLint v0, GLint v1);
	//inline void Uniform3i(GLint location, GLint v0, GLint v1, GLint v2);
	//inline void Uniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);

	//inline void UniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, float* value);
	//inline void UniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, float* value);
	//inline void UniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, float* value);


	//inline void ValidateProgram(GLuint program);
	//inline unsigned char IsShader(GLuint shader);
	//inline void GetShaderiv(GLuint shader, GLenum pname, GLint *params);
	//inline void GetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei *count, GLuint *shaders);
	//inline void GetShaderInfoLog(GLuint shader, GLsizei maxLength, GLsizei *length, char *infoLog);
	//inline void GetShaderSource(GLuint shader, GLsizei bufSize, GLsizei *length, char *source);
	//inline void GetShaderPrecisionFormat(GLenum shaderType, GLenum precisionType, GLint *range, GLint *precision);
	//inline void GetVertexAttribfv(GLuint index, GLenum pname, GLfloat *params);
	//inline void GetVertexAttribiv(GLuint index, GLenum pname, GLint *params);
	//inline void GetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid **pointer);
	//inline void GetUniformfv(GLuint program, GLint location, GLfloat *params);
	//inline void GetUniformiv(GLuint program, GLint location, GLint *params);
	//inline unsigned char IsProgram(GLuint program);
	//inline void GetProgramiv(GLuint program, GLenum pname, GLint *params);
	//inline void GetProgramInfoLog(GLuint program, GLsizei maxLength, GLsizei *length, char *infoLog);
	//inline void Scissor(GLint x, GLint y, GLsizei width, GLsizei height);
	//inline void SampleCoverage(GLclampf value, GLboolean invert);
	//inline void StencilFunc(GLenum func, GLint ref, GLuint mask);
	//inline void StencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
	//inline void StencilOp(GLenum sfail, GLenum dpfail, GLenum dppass);
	//inline void StencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
	//inline void DepthFunc(GLenum func);

	//// Blending

	//// mode{GL_FUNC_ADD, GL_FUNC_SUBTRACT, or GL_FUNC_REVERSE_SUBTRACT}
	//inline void BlendEquation(GLenum mode);
	//inline void BlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
	//inline void BlendFuncSeparate(GLenum srcRGB, GLenum dstRGB,	GLenum srcAlpha, GLenum dstAlpha);
	///* sfactor{GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_DST_COLOR, 
	// GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, 
	// GL_ONE_MINUS_DST_ALPHA, GL_CONSTANT_COLOR, GL_ONE_MINUS_CONSTANT_COLOR, GL_CONSTANT_ALPHA, 
	// GL_ONE_MINUS_CONSTANT_ALPHA, and GL_SRC_ALPHA_SATURATE.The initial value is GL_ONE}
	//inline void BlendFunc(GLenum sfactor, GLenum dfactor);
	//inline void BlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	//
	//inline void Flush();
	//inline void Finish();

	//inline void Hint(GLenum target,	GLenum mode);
	//inline void GetBooleanv(GLenum pname, GLboolean *params);
	//inline void GetIntegerv(GLenum pname, GLint *params);
	//inline void GetFloatv(GLenum pname, GLfloat *params);
	//inline unsigned char IsEnabled(GLenum cap);
	//inline const GLubyte* GetString(GLenum name);

	//// Buffers

	//inline void ColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
	//inline void DepthMask(GLboolean flag);
	//inline void StencilMask(GLuint mask);
	//inline void StencilMaskSeparate(GLenum face, GLuint mask);

	//inline void Clear(GLbitfield mask);
	//inline void ClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
	//inline void ClearDepth(GLclampf depth);
	//inline void ClearStencil(GLint s);

	//// Framebuffer

	//inline void BindFramebuffer(GLenum target, GLuint framebuffer);
	//inline void DeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
	//inline void GenFramebuffers(GLsizei n, GLuint * framebuffers);
	//inline void BindRenderbuffer(GLenum target,	GLuint renderbuffer);
	//inline void DeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
	//inline void GenRenderbuffers(GLsizei n, GLuint * renderbuffers);
	//inline void RenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
	//inline void FramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
	//inline void FramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
	//inline GLenum CheckFramebufferStatus(GLenum target);
	//inline unsigned char IsFramebuffer(GLuint framebuffer);
	//inline void GetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
	//inline unsigned char IsRenderbuffer(GLuint renderbuffer);
	//inline void GetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);

}

//low Level RenderAPI includes


#ifdef OPENGL
	#ifndef RAPICHOSEN
		#define RAPICHOSEN
		#include "../../renderapi/opengl/openglAPI.inl" 
	#endif
#endif

#ifdef OPENGLES	
	#ifndef RAPICHOSEN
		#define RAPICHOSEN
		#include "../../renderapi/opengles/openglesAPI.inl"	
	#endif
#endif

#ifdef DIRECTX
	#ifndef RAPICHOSEN
		#define RAPICHOSEN
		#include "../../renderapi/directx/directxAPI.inl"
	#endif
#endif
*/