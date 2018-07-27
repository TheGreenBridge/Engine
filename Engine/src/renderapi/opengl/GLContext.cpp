//------------------------------------------------------------------------------
// GLContext.cpp
//
// OPEN GL implementation of a render api context
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Context.h>
#include <renderapi\opengl\GLCommon.h>
#include <utils\Log.h>


//------------------------------------------------------------------------------
const BOOL Context::init() 
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		LOG_ERROR("Could not initialize GLEW!");
		return false;
	}
	else LOG("GLEW successfully initialized.");

	GLCall(glClearColor(0.39f, 0.65f, 1.0f, 1.0f));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glFrontFace(GL_CCW));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_CULL_FACE));
	
	return true;
}

//------------------------------------------------------------------------------
const void Context::setViewport(const int width, const int height)
{
	GLCall(glViewport(0, 0, width, height));
}

//------------------------------------------------------------------------------
const void Context::clear()
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

//------------------------------------------------------------------------------
std::string errorCodeToString(U32 error_code)
{
	switch (error_code)
	{
	case GL_NO_ERROR: return std::string("no error"); break;
	case GL_INVALID_ENUM: return std::string("invalid enum"); break;
	case GL_INVALID_VALUE: return std::string("invalid value"); break;
	case GL_INVALID_OPERATION: return std::string("invalid operation"); break;
	case GL_STACK_OVERFLOW: return std::string("stack overflow"); break;
	case GL_STACK_UNDERFLOW: return std::string("stack underflow"); break;
	case GL_OUT_OF_MEMORY: return std::string("out of memory"); break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: 
		return std::string("invalid framebuffer operation"); break;
	case GL_CONTEXT_LOST: return std::string("context lost"); break;
	case GL_TABLE_TOO_LARGE: return std::string("table too large"); break;
	default: return std::string("unknown error code"); break;
	}
}

//------------------------------------------------------------------------------
const void Context::getErrors(const char* file, U32 line)
{
	U32 error;
	while ((error = glGetError()) != GL_NO_ERROR)
	{
		std::string text = "_GL Error_ Code: " + std::to_string(error) +
			" text: " + errorCodeToString(error) + '\n' + std::string(file) + 
			std::to_string(line);
		LOG_ERROR(text.c_str());
	}
}