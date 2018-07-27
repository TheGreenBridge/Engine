
//#include "tests\EngineTest.h"
//
//int main() {
//
//	EngineTest test;
//	test.init();
//	test.run();
//
//	return 0;
//}

//int xPosition = 0, yPosition = 0;
//
//void cursor_position_callback(GLFWwindow* commingWindow, double xpos, double ypos)
//{
//	TwEventMousePosGLFW3(commingWindow, xpos, ypos);
//	int dx = (int)xpos - xPosition;
//	int dy = (int)ypos - yPosition;
//
//	float sens = 0.01f;
//	float ry = -dy * sens;
//	float rx = -dx * sens;
//
//	xPosition = (int)xpos;
//	yPosition = (int)ypos;
//
//	camera.Rotate(Vec3(1, 0, 0), -ry);
//	camera.Rotate(Vec3(0, 1, 0), -rx);
//}
//
//float angle = 0;
//Transform fromTrans(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f);
//Transform toTrans(Vec3(0, 0, 0), Quaternion(1, 0, 0, 1), 1.0f);
//float countering = 0;
//bool cameraState = false;
//void updateInput() {
//	// Translation
//	if (gInputManager.KEYS[GLFW_KEY_W]) camera.Translate(Vec3(0, 0, 1));
//	if (gInputManager.KEYS[GLFW_KEY_S]) camera.Translate(Vec3(0, 0, -1));
//	if (gInputManager.KEYS[GLFW_KEY_A]) camera.Translate(Vec3(1, 0, 0));
//	if (gInputManager.KEYS[GLFW_KEY_D]) camera.Translate(Vec3(-1, 0, 0));
//	if (gInputManager.KEYS[GLFW_KEY_SPACE]) camera.Translate(Vec3(0, -1, 0));
// 	if (gInputManager.KEYS[GLFW_KEY_C]) camera.Translate(Vec3(0, 1, 0));
//
//	// Inits
//	if (gInputManager.KEYS[GLFW_KEY_L]) sun.setPosition(Vec3(0, 5, 0));
//
//	// Camera: UP - DOWN - FRONT - BACK- RIGHT - LEFT
//	if (gInputManager.KEYS[GLFW_KEY_8]) { camera.setRotation(Vec3(1, 0, 0), (float)(PI / 2)); camera.setPosition(Vec3(0, -10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_2]) { camera.setRotation(Vec3(-1, 0, 0), (float)(PI / 2)); camera.setPosition(Vec3(0, 10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_5]) { camera.setRotation(Vec3(0, 0, 0), 1); camera.setPosition(Vec3(0, 0, -10)); }
//	if (gInputManager.KEYS[GLFW_KEY_0]) { camera.setRotation(Vec3(0, 0, 1), (float)(PI / 2)); camera.setPosition(Vec3(0, 0, -10)); }
//	if (gInputManager.KEYS[GLFW_KEY_6]) { camera.setRotation(Vec3(0, 0, 1), (float)(PI / 2)); camera.setPosition(Vec3(-10, 0, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_4]) { camera.setRotation(Vec3(0, 0, -1), (float)(PI / 2)); camera.setPosition(Vec3(10, 0, 0)); }
//
//	//Rotation
//	if (gInputManager.KEYS[GLFW_KEY_Q]) camera.Rotate(Vec3(0, 0, 1), 0.1f);
//
//	// Special
//	if (gInputManager.KEYS[GLFW_KEY_ENTER]) camera.printInfo();
//	if (gInputManager.KEYS[GLFW_KEY_U]) { camera.setRotation(Vec3(1, 0, 0), (float)(PI / 2));	camera.setPosition(Vec3(0, -10, 0)); }
//	if (gInputManager.KEYS[GLFW_KEY_V]) checkConsole();
//
//	if (gInputManager.KEYS[GLFW_KEY_X]) camera.m_Speed = 0.1f;
//	if (gInputManager.KEYS[GLFW_KEY_B]) camera.m_Speed = 0.01f;
//
//	if (gInputManager.KEYS[GLFW_KEY_P]) {
//		/*if (beta < 1)*/ beta += 0.01f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_O]) {
//		/*if (beta > 0)*/ beta -= 0.01f;
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_K]) {
//		//if(entity.animatable->m_pHandle->playbackRate < 3.0f)	entity.animatable->m_pHandle->playbackRate += 0.02f;
//		//LOG("PlaybackRate", entity.animatable->m_pHandle->playbackRate);
//
//		gAnimationManager.update(0.005f);
//		//selectAnimation = 0;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_J]) {
//		//if(entity.animatable->m_pHandle->playbackRate > -1.02) entity.animatable->m_pHandle->playbackRate -= 0.02f;
//		//LOG("PlaybackRate", entity.animatable->m_pHandle->playbackRate);
//		gAnimationManager.update(-0.005f);
//		//selectAnimation = 1.0f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_UP]) {
//		eentity.transform.position.y += 0.1f;
//		eentity.collidable->max.y += 0.1f;
//		eentity.collidable->min.y += 0.1f;
//		//AnimationEvent e(0, true);
//		//gAnimationManager.onEvent(&e);
//	}
//	else {
//		//AnimationEvent e(0, false);
//		//gAnimationManager.onEvent(&e);
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_DOWN]) {
//		eentity.transform.position.y -= 0.1f;
//		eentity.collidable->max.y -= 0.1f;
//		eentity.collidable->min.y -= 0.1f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_RIGHT]) {
//		eentity.transform.position.x += 0.1f;
//		eentity.collidable->max.x += 0.1f;
//		eentity.collidable->min.x += 0.1f;
//	}
//	if (gInputManager.KEYS[GLFW_KEY_LEFT]) {
//		eentity.transform.position.x -= 0.1f;
//		eentity.collidable->max.x -= 0.1f;
//		eentity.collidable->min.x -= 0.1f;
//	}
//
//	if (gInputManager.KEYS[GLFW_KEY_H]) {
//		if(countering < 1)countering += 0.001f;
//		eentity.transform = ani_transform(fromTrans, toTrans, countering);
//	}
//	
//	if (gInputManager.KEYS[GLFW_KEY_M]) {			
//		renderer.setCamera(&followCam);
//	}
//	if (gInputManager.KEYS[GLFW_KEY_N]) {
//		renderer.setCamera(&camera);
//	}
//}
//
//
//
//void key_callback(GLFWwindow* commingWindow, int key, int scancode, int action, int mods){	
//	TwEventKeyGLFW3(commingWindow, key, scancode, action, mods);
//	
//	if (action == GLFW_PRESS) {
//		gInputManager.KEYS[key] = true;
//		KeyPressedEvent ke(key);
//		engine::Event *e = &ke;
//		gInputManager.onEvent(e);
//	}
//	else if (action == GLFW_RELEASE) {
//		gInputManager.KEYS[key] = false;
//		engine::Event e(EventType::EVENT_KEY_RELEASED);
//		gInputManager.onEvent(&e);
//	}
//}