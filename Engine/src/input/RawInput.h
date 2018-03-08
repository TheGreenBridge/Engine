#pragma once
#include "../platform/windows/InputManager.h"

#include <GLFW\glfw3.h>
// forward declaration
//namespace engine {	class InputManager; }
//class GLFWwindow;

using namespace engine;

class RawInput {
	
private:
	static engine::InputManager *inputManager;
	RawInput();
public:
	static void setInputManager(engine::InputManager *manager);
	static void cursor_position_callback(GLFWwindow* commingWindow, double xpos, double ypos);
	static void key_callback(GLFWwindow* commingWindow, int key, int scancode, int action, int mods);
	static void key_callback(int key, int scancode, int action);
};