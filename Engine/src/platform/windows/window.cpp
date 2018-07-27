#include "window.h"
#include "../../utils/Log.h"
#include "..\..\..\tests\Game.h"
#include <graphics\api\Context.h>
#include <SDL.h>


//void windowResize(GLFWwindow * window, int width, int height);
//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

Window::Window(const char* title, const int width, const int height) 
	: m_Title(title), m_Width(width), m_Height(height), m_cxpos(0), m_cypos(0), m_Closed(false)
{
	if (!init()) {
		LOG_ERROR("Context could not get initialized.");
		//glfwTerminate();
		SDL_Quit();
	}
}

Window::~Window() {
	//glfwTerminate();
}

const bool Window::init() {
	//if (!glfwInit()) {
	//	LOG_ERROR("Failed to initialize GLFW!");
	//	return false;
	//}
	//else LOG("Open GL Window created.");

	///* Create a windowed mode window and its OpenGL context */

	//m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	//if (!m_Window)
	//{
	//	glfwTerminate();
	//	return false;
	//}

	///* Make the window's context current */
	//glfwMakeContextCurrent(m_Window);

	

	////printRenderAPI();

	////glClearColor(0.39f, 0.65f, 1.0f, 1.0f);

	//glfwSetWindowSizeCallback(m_Window, windowResize);
	//
	////glEnable(GL_DEPTH_TEST);
	////glFrontFace(GL_CCW);
	////glCullFace(GL_BACK);
	////glEnable(GL_CULL_FACE);

	// SDL version
	/* Information about the current video settings. */
	//const SDL_VideoInfo* info = NULL;
	/* Dimensions of our window. */
	int width = 0;
	int height = 0;
	/* Color depth in bits of our window. */
	int bpp = 0;
	/* Flags we will pass into SDL_SetVideoMode. */
	int flags = 0;

	/* First, initialize SDL's video subsystem. */
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		/* Failed, exit. */
		fprintf(stderr, "Video initialization failed: %s\n",
			SDL_GetError());
		
	}

	/* Let's get some video information. */
	//info = SDL_GetVideoInfo();

	//if (!info) {
	//	/* This should probably never happen. */
	//	fprintf(stderr, "Video query failed: %s\n",
	//		SDL_GetError());
	//	return false;
	//}

	/*
	* Set our width/height to 640/480 (you would
	* of course let the user decide this in a normal
	* app). We get the bpp we will request from
	* the display. On X11, VidMode can't change
	* resolution, so this is probably being overly
	* safe. Under Win32, ChangeDisplaySettings
	* can change the bpp.
	*/
	width = 640;
	height = 480;
	//bpp = info->vfmt->BitsPerPixel;

	/*
	* Now, we want to setup our requested
	* window attributes for our OpenGL window.
	* We want *at least* 5 bits of red, green
	* and blue. We also want at least a 16-bit
	* depth buffer.
	*
	* The last thing we do is request a double
	* buffered window. '1' turns on double
	* buffering, '0' turns it off.
	*
	* Note that we do not use SDL_DOUBLEBUF in
	* the flags to SDL_SetVideoMode. That does
	* not affect the GL attribute state, only
	* the standard 2D blitting setup.
	*/
	

	/*
	* We want to request that SDL provide us
	* with an OpenGL window, in a fullscreen
	* video mode.
	*
	* EXERCISE:
	* Make starting windowed an option, and
	* handle the resize events properly with
	* glViewport.
	*/
	
	flags = SDL_VIDEO_OPENGL | SDL_WINDOW_FULLSCREEN;

	/*
	* Set the video mode
	*/

	m_Window = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, this->m_Width, this->m_Height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
	if (m_Window == nullptr)
	{
		LOG_ERROR("Could not create Window.");
		return false;
	}
	SDL_GL_CreateContext(m_Window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	
	SDL_GL_SetSwapInterval(1);

	//if (SDL_SetVideoMode(width, height, bpp, flags) == 0) {
		/*
		* This could happen for a variety of reasons,
		* including DISPLAY not being set, the specified
		* resolution not being available, etc.
		*/
		//fprintf(stderr, "Video mode set failed: %s\n",
		//	SDL_GetError());
		//return false;
	//}
	
	if (!Context::init()) return false;
	Context::setViewport(m_Width, m_Height);

	SDL_GL_SwapWindow(m_Window);

	return true;
}

//void Window::setCursorCallback(GLFWcursorposfun cbfun){
//	//glfwSetCursorPosCallback(m_Window, cbfun);
//}
//
//void Window::setKeyboardCallback(GLFWkeyfun cbfun) {
//	//glfwSetKeyCallback(m_Window, cbfun);
//}
//
//void Window::setMouseButtonCallback(GLFWmousebuttonfun mbfun) {
//	//glfwSetMouseButtonCallback(m_Window, mbfun);
//}
//
//void Window::setCharCallback(GLFWcharfun ccb) {
//	//glfwSetCharCallback(m_Window, ccb);
//}
//
////GLFWwindow * const Window::getContext() const {
////	return m_Window;
////}
//
void Window::clear() const {
	Context::clear();
}

void Window::update()  {
	
	/* Poll for and process events */
	//glfwPollEvents();
	/* Swap front and back buffers */
	//glfwSwapBuffers(m_Window);	
	//LOG("Render");
	SDL_PumpEvents();
	SDL_Event events;
	while (SDL_PollEvent(&events)) {

		switch (events.type) {
		case SDL_WINDOWEVENT:
			switch (events.window.event) {
			case SDL_WINDOWEVENT_RESIZED:
				LOG("Window.width", events.window.data1);
				LOG("Window.height", events.window.data2);
				Context::setViewport(events.window.data1, events.window.data2);
				break;
			default:
				break;
			}
			break;
		case SDL_KEYDOWN:
		case SDL_KEYUP:		
			if (events.type == SDL_KEYUP) {
				//printf("Release:- ");
				m_KeyboardCallback(events.key.keysym.sym, events.key.keysym.scancode, 0);
			}
			else {
				//printf("Press:- ");
				m_KeyboardCallback( events.key.keysym.sym, events.key.keysym.scancode, 1);
			}
				
			break;
		case SDL_QUIT:
			m_Closed = true;
			break;
		default:
			break;
		}	
	}
	SDL_GL_SwapWindow(m_Window);
}

// returns
const bool Window::isClosed() const {
	//return glfwWindowShouldClose(m_Window) == 1;
	return m_Closed;
}

int Window::getWidth() const {
	return m_Width;
}

int Window::getHeight() const {
	return m_Height;
}

void Window::shutDown() const
{
	//glfwTerminate();
	/*TwTerminate();*/
	SDL_Quit();
}

void Window::setKeyboardCallback(KeyboardCallback callback)
{
	m_KeyboardCallback = callback;
}

void Window::setMouseCallback(MouseCallback callback)
{
	m_MouseCallback = callback;
}


// Events
//void windowResize(GLFWwindow * window, int width, int height) {
//	glViewport(0, 0, width, height);
//}

//static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	LOG("MousePositon: " + std::to_string(xpos) + " , " + std::to_string(ypos));
//}