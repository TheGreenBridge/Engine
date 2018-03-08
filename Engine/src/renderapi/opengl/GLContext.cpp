
#include <graphics\api\Context.h>
#include <renderapi\opengl\GLCommon.h>
#include <utils\Log.h>

const BOOL Context::init() 
{
	if (glewInit() != GLEW_OK) {
		LOG_ERROR("Could not initialize GLEW!");
		return false;
	}
	else LOG("GLEW successfully initialized.");

	glClearColor(0.39f, 0.65f, 1.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	
	return true;
}

const void Context::setViewport(const int width, const int height)
{
	glViewport(0, 0, width, height);
}

const void Context::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
