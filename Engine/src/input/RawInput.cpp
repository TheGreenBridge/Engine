#include "RawInput.h"

#include "rawinputconstants.h"
#include "../utils/Log.h"

InputManager* RawInput::inputManager;

RawInput::RawInput(){
	
}

void RawInput::setInputManager(InputManager * manager) {
	 RawInput::inputManager = manager;
}

void RawInput::cursor_position_callback(GLFWwindow* commingWindow, double xpos, double ypos) {
	RawInput::inputManager->mapper.setRawAxisValue(INPUTAXIS::mouse_x, (float)xpos);
	RawInput::inputManager->mapper.setRawAxisValue(INPUTAXIS::mouse_y, (float)ypos);
	//LOG("IN CURSOR CALLBACK");
}

void RawInput::key_callback(GLFWwindow* commingWindow, int key, int scancode, int action, int mods) {
	bool boolAction = false, boolPreviouslyPressed = false;
	switch (action) {
		case GLFW_PRESS: boolAction = true; boolPreviouslyPressed = false; break;
		case GLFW_REPEAT: boolAction = true; boolPreviouslyPressed = true; break;
		case GLFW_RELEASE: boolAction = false; boolPreviouslyPressed = false; break;
		
	}
	RawInput::inputManager->mapper.setRawButtonState((INPUTBUTTON)key, boolAction, boolPreviouslyPressed);
	
	LOG("Button pressed", key);
}

void RawInput::key_callback(int key, int scancode, int action) {
	bool boolAction = false;
	bool boolPreviouslyPressed = false;
	switch (action) {
		case 0: boolAction = false;
			break;
		case 1: boolAction = true;
			break;
		default:
			break;
	}
	
	RawInput::inputManager->mapper.setRawButtonState((INPUTBUTTON)key, boolAction, boolPreviouslyPressed);

	LOG("Button pressed", key);
}