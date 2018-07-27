#pragma once


//#include <GLFW\glfw3.h>
#include <common\types.h>

typedef void (*KeyboardCallback)(int key, int scancode, int action);
typedef void (*MouseCallback)(int width, int height);

struct SDL_Window;

class Window {
private:
	const char *m_Title;
	I32 m_Width, m_Height;
	bool m_Closed;

	MouseCallback m_MouseCallback;
	KeyboardCallback m_KeyboardCallback;

	SDL_Window* m_Window;

	//GLFWwindow *m_Window;

	I32 m_cxpos, m_cypos;
	  
public:
	Window(const char* title, const int width, const int height);
	~Window();

	void clear() const;
	void update() ;
	const bool init();
	const bool isClosed() const;

	//GLFWwindow * const getContext() const;

	int getWidth() const;
	int getHeight() const;

	int getCXPosition() const { return m_cxpos; };
	int getCYPosition() const { return m_cypos; };

	void shutDown() const;

	void setKeyboardCallback(KeyboardCallback callback);
	void setMouseCallback(MouseCallback callback);

	// Callbacks

	/*void setCursorCallback(GLFWcursorposfun cbfn);
	void setKeyboardCallback(GLFWkeyfun cbfun);
	void setMouseButtonCallback(GLFWmousebuttonfun mbfun);
	void setCharCallback(GLFWcharfun ccb);*/
	
	//friend void window_size_callback(GLFWwindow* window, int width, int height);
};