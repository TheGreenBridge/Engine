//#include <gl\glew.  h>
//#include <GLFW\glfw3.h>
//#include <cmath>
/////PLATFORM
//#include "src\platform\windows\window.h"
//#include "src\platform\windows\InputManager.h"
//#include "src\systems\AnimationManager.h"
//#include "src\platform\windows\Console.h"
//
//#include "src\entity\Camera.h"
//#include "src\entity\Entity.h" // MESH MODEL MATERIAL(TEXTURE) ANIMATION(TRANSFORM)
//#include "src\entity\FollowCamera.h"
//
//#include "src\graphics\buffer\Buffer.h"
//#include "src\entity\mesh\plane.h"
/////RENDER
//
//#include "src\graphics\render\shader.h"
//#include "src\graphics\render\Renderer.h"
//#include "src\graphics\render\Loader.h"
//
//#include "src\graphics\Scene.h"
//#include "src\entity\Light.h"
//#include "src\entity\Terrain.h"
//
/////ANIMATION
////#include "src\graphics\animation\skinning\SkinnedMesh.h"
//#include "src\graphics\animation\Animation.h"
//#include "src\graphics\animation\skinning\RenderableSkin.h"
//#include "src\graphics\animation\AnimationHandle.h"
//#include "src\graphics\animation\interpolation.h"
//
/////COLLISION
//#include "src\collision\AABB.h"
//#include "src\systems\CollisionManager.h"
//
//
/////MEMORY
//#include "src\memory\Allocator.h"
/////UTILS
//#include "src\math\maths.h"
//#include "src\utils\Time.h"
//#include "src\utils\Log.h"
//#include "src\utils\fileutils.h"
//
/////
//#include "src\systems\messageing\Event.h"
//#include "src\systems\messageing\types\KeyPressedEvent.h"
//#include "src\systems\messageing\types\AnimationEvent.h"
//
//#include "src\systems\SystemManager.h"
//#include <AntTweakBar.h>
//#include <random>
//
/////STANDART - REMOVE!!!
//
//
//// NAMESPACES
//using namespace engine::memory;
//using namespace engine;
//using namespace engine::graphics;
//using namespace engine::collision;
//using namespace engine::entity;
//
//#define MEM_STORAGE 8192 // 8 KiB = 8 * 2^10
//
////Prototypen
//void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
//void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
//void updateInput();
//
//// GLOBALS
//Camera camera(90.0f, 1.7777f, 0.1f, 800.0f);
//Window window("TEST", 1280, 720);
//Entity eentity(Vec3(0, 0, 2), Quaternion(0.5f, -0.5f , -0.4f, -0.6f), 1.0f);
//Entity rock(Vec3(10, 0, 0), Quaternion(0, 0, 0, 1), 1.0f);
//Entity plane(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f);
//Entity axis(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f);
//Light sun(Vec3(5, 3, 0), Vec3(1.0,0.0,0.0));
//Terrain terrain;
//
//std::vector<Entity> rocks;
//
//float selectAnimation = 0;
//float beta = 0;
//
//
//// SYSTEMS
//
//SystemManager gSystemManager;
//InputManager gInputManager;
//AnimationManager gAnimationManager;
//CollisionManager gCollisionManager;
//
//FollowCamera followCam(&eentity);
//Renderer renderer(&followCam);
//
//Vec3 fPoint(10, 10, 10);

#include "tests\Game.h"

int main() {
	
	/*TwInit(TW_OPENGL, NULL);
	TwWindowSize(300, 500);
	TwBar *myBar;
	myBar = TwNewBar("testBar");
	TwAddVarRW(myBar, "Position", TW_TYPE_DIR3F, &eentity.transform.position.x, "");
	TwAddVarRW(myBar, "Rotation_x", TW_TYPE_FLOAT, &eentity.transform.rotation.x, 
		" min=-1 max=1 step=0.1 keyIncr=e keyDecr=E ");
	TwAddVarRW(myBar, "Rotation_y", TW_TYPE_FLOAT, &eentity.transform.rotation.y,
		" min=-1 max=1 step=0.1 keyIncr=r keyDecr=R ");
	TwAddVarRW(myBar, "Rotation_z", TW_TYPE_FLOAT, &eentity.transform.rotation.z,
		" min=-1 max=1 step=0.1 keyIncr=t keyDecr=T ");
	TwAddVarRW(myBar, "Rotation_w", TW_TYPE_FLOAT, &eentity.transform.rotation.w,
		" min=-1 max=1 step=0.1 keyIncr=z keyDecr=Z ");

	gSystemManager.testManager();
	 MANAGER
	gSystemManager.registerSystem(gInputManager);
	gSystemManager.registerSystem(gAnimationManager);
	gSystemManager.registerSystem(gCollisionManager);

	gAnimationManager.startUp();
	gAnimationManager.loadAnimations();
	
	gCollisionManager.startUp();
	
	

	window.setCursorCallback(RawInput::cursor_position_callback);
	window.setKeyboardCallback(key_callback);
	window.setMouseButtonCallback(TwEventMouseButtonGLFW3);
	window.setCharCallback(TwEventCharGLFW3);
	
	// SHADER
	Shader defaultShader("res/shader/default.vert", "res/shader/default.frag");
	Shader shader("res/shader/defaultmaterial.vert", "res/shader/defaultmaterial.frag");
	//Shader uiShader("res/shader/ui/uishader.vert", "res/shader/ui/uishader.frag");
	Shader skyBoxShader("res/shader/boxshader.vert", "res/shader/boxshader.frag");
	Shader skinShader("res/shader/animation/rigshader.vert", "res/shader/animation/rigshader.frag");
	Shader aabbShader("res/shader/aabbshader.vert", "res/shader/aabbshader.frag");
	Shader terrainShader("res/shader/terrainshader.vert", "res/shader/terrainshader.frag");

	Cubemap skybox;
	std::vector<const GLchar*> faces;
	faces.push_back("res/textures/cubemaps/sea/right.jpg");
	faces.push_back("res/textures/cubemaps/sea/left.jpg");
	faces.push_back("res/textures/cubemaps/sea/top.jpg");
	faces.push_back("res/textures/cubemaps/sea/bottom.jpg");
	faces.push_back("res/textures/cubemaps/sea/back.jpg");
	faces.push_back("res/textures/cubemaps/sea/front.jpg");
	skybox.loadTextures(faces);


	camera.setPosition(Vec3(0.0f,0.0f,0.0f));
	camera.setRotation(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	followCam.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	followCam.setRotation(Vec3(0.0f, 0.707f, 0.0f), 1.0f);
	renderer.initialize();

	// Textures
	Texture texture("res/textures/wood_texture.png");
	//terrain.loadTerrain();
	Material material;
	material.texture = &texture;
	
	// TEXTURE APPLY
	eentity.material = &material;

	//GLuint vboaxis;
	
	// MESH
	Mesh mesh,planeMesh;
	FileUtils::load_obj("res/mesh/pig.obj", mesh);
	createPlaneMesh(planeMesh);

	//entity.mesh = &mesh;
	plane.mesh = &planeMesh;

	// MODELS
	Model model = loadModel(mesh);
	//Model model2 = loadModel(mesh);
	Model planemodel;
	//Model axismodel;
	rock.model = &model;
	rock.mesh = &mesh;
	rock.material = &material;


	// initialize random seed: 
	srand(time(NULL));

	/* generate secret number between 1 and 10: 
	

	/*for (U32 i = 0; i < 10; i++) {
		int random = rand() % 100 + 1;
		Entity tmpRock(Vec3(random, 100, 2), Quaternion(0,0,0,1), 1.0f);
		tmpRock.collidable = gCollisionManager.requestAABB3D();
		rocks.push_back(tmpRock);
	}
	
	planemodel.vao = loadVAO(planemodel.vertices, &planeMesh.getVertices()[0].x, planeMesh.getVertices().size() * sizeof(Vec3), 3, 0);

	//vboaxis = loadBufferf(skeletonSketch, 36, 3, 0);
	uint skyvbo;
	GLuint skyvao = loadVAO(skyvbo, skybox.skyboxVertices,108 * sizeof(float),3,0);
	

	Animation testAnimation(Transform(Vec3(0,0,0), Quaternion(0,0,0,1), 1.0f),
		Transform(Vec3(10,10,0), Quaternion(0,0,0,1), 3.0f));
	rock.animation = &testAnimation;

	// MODEL APPLY
	eentity.model = &model;
	plane.model = &planemodel;

	// get Animation Component
	gAnimationManager.requestNewComponent(eentity.animatable);

	// SCENE
	Scene scene;
	scene.add(&eentity);
	scene.add(&rock);

	float counter = 0;
	
	//Renderer renderer(&camera);
	

	Time time;
	uint FPS = 0;
	//Loop until the user closes the window 
	time.init();
	time.start();

	//Vec3 startVector = pig.transform.position;
	//Vec3 endVector(10,10,0);

	AABB3D *test = gCollisionManager.requestAABB3D();
	int tmpPos = -10;
	test->max = Vec3(tmpPos + 3, 3, 3);
	test->min = Vec3(tmpPos + -3, -3, -3);

	rock.collidable = gCollisionManager.requestAABB3D();
	eentity.collidable = gCollisionManager.requestAABB3D();
	eentity.collidable->min -= Vec3(2, 2, 2);
	eentity.collidable->max += Vec3(1, 1, 1);

	gAnimationManager.logStates();
	while (!window.isClosed())
	{
		
		window.clear();
		updateInput();
		counter += 0.0001f;
		//pig.position = ani_lerp(startVector, endVector, beta);
		Vec3 newPosition = rock.animation->getPosition(cosf(counter * 180.0f / (float)PI) * 0.5f + 0.5f);
		rock.transform.position = newPosition;
		rock.collidable->min = newPosition;
		rock.collidable->max = newPosition + Vec3(1,1,1);


		//pig.transform.rotation.rotate(Vec3(0,1,0), 0.001f);
		eentity.transform.scale = 0.1f*sinf(counter*180.0f/(float)PI) + 1.0f;
		camera.update();
		followCam.update((float)time.getDelta() / 1000);
		
		gSystemManager.update();
		gAnimationManager.update((float)time.getDelta()/1000);
		gCollisionManager.update(10);
		
		

		//renderer.render(skybox, skyvao, skyBoxShader);
		renderer.render(scene, shader, sun);
		
		renderer.renderAABBs(gCollisionManager.getCollidables(), gCollisionManager.getNumCollidables(), aabbShader);

		// DEFAULT Rendering Stuff****************
		// DEFAULT PLANE
		renderer.renderLINES(plane, defaultShader);
		//renderer.renderAABB(*test, aabbShader);	
		renderer.renderRenderSkin(eentity, skinShader);
		
		renderer.renderTerrain(terrain.getModel().vertices, terrainShader, 3, terrain.getNumIndices());
		
		//TwDraw();
		window.update();
		//TwDraw();
		FPS++;
		time.measureTime();
		if (time.getPastTime() >= 1000l) {
			time.erasePastTime();
			LOG("FPS", FPS );
			FPS = 0;
		}
	}
	glfwTerminate();
	TwTerminate();
*/

	Game test;
	test.init();
	test.run();

	return 0;
}

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