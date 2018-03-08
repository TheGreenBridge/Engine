#include "Game.h"

#include <input\RawInput.h>
///MEMORY
#include <memory\Allocator.h>

#include <entity\mesh\plane.h>
#include <entity\Camera.h>
#include <entity\Entity.h> // MESH MODEL MATERIAL(TEXTURE) ANIMATION(TRANSFORM)
#include <entity\FollowCamera.h>

///RENDER

#include <graphics\api\Shader.h>
#include <graphics\api\Renderer.h>
#include <graphics\api\Loader.h>
#include <graphics\api\Texture.h>

#include <entity\Scene.h>
#include <entity\Light.h>
#include <entity\Terrain.h>



///ANIMATION
//#include "src\graphics\animation\skinning\SkinnedMesh.h"
#include <graphics\animation\Animation.h>
#include <graphics\animation\skinning\RenderableSkin.h>
#include <graphics\animation\AnimationHandle.h>
#include <graphics\animation\interpolation.h>

///COLLISION
#include <collision\AABB.h>


///UTILS
#include <math\maths.h>
#include <utils\Time.h>
#include <utils\Log.h>
#include <utils\fileutils.h>

#include <cmath>

using namespace engine::graphics;
using namespace engine::collision;
using namespace engine::entity;
using namespace engine;

Game::Game():
	window("Project Green Bridge", 1280, 720)
{
}

Game::~Game()
{
}

void Game::init()
{
}

void Game::run()
{
	Camera camera(90.0f, 1.7777f, 0.1f, 800.0f);
	Light sun(Vec3(5, 3, 0), Vec3(1.0, 0.0, 0.0));
	Terrain terrain;

	//gSystemManager.testManager();
	// MANAGER
	gSystemManager.registerSystem(gInputManager);
	gSystemManager.registerSystem(gAnimationManager);
	gSystemManager.registerSystem(gCollisionManager);

	gAnimationManager.startUp();
	gAnimationManager.loadAnimations();
	gCollisionManager.startUp();

	//window.setCursorCallback(RawInput::cursor_position_callback);
	//window.setKeyboardCallback(RawInput::key_callback);

	window.setKeyboardCallback(RawInput::key_callback);
	
	// MOUSE INPUT
	/*I32 xPosition = 0, yPosition = 0;
	gInputManager.mapper.addCallback([&camera, &xPosition, &yPosition](MappedInput &inputs) {
		I32 currentX = inputs.ranges.find(RANGE::camera_x)->second;
		I32 currentY = inputs.ranges.find(RANGE::camera_y)->second;
	
		I32 dx = (I32)currentX - xPosition;
		I32 dy = (I32)currentY - yPosition;

		F32 sens = 0.01f;
		F32 ry = -dy * sens;
		F32 rx = -dx * sens;
		
		xPosition = (I32)currentX;
		yPosition = (I32)currentY;
		
		camera.Rotate(Vec3(1, 0, 0), -ry);
		camera.Rotate(Vec3(0, 1, 0), -rx);

	}, 2);*/
	
	// SHADER
	Shader defaultShader("res/shader/default.vert", "res/shader/default.frag");
	Shader shader("res/shader/defaultmaterial.vert", "res/shader/defaultmaterial.frag");
	//Shader uiShader("res/shader/ui/uishader.vert", "res/shader/ui/uishader.frag");
	Shader skyBoxShader("res/shader/boxshader.vert", "res/shader/boxshader.frag");
	Shader skinShader("res/shader/animation/rigshader.vert", "res/shader/animation/rigshader.frag");
	Shader aabbShader("res/shader/aabbshader.vert", "res/shader/aabbshader.frag");
	Shader terrainShader("res/shader/terrainshader.vert", "res/shader/terrainshader.frag");
	Shader environmentShader("res/shader/environmentShader.vert", "res/shader/environmentShader.frag");

	Cubemap skybox;
	/*skybox.loadTextures(std::vector<const GLchar*> { "res/textures/cubemaps/colors/right_green.png",	"res/textures/cubemaps/colors/left_blue.png",
		"res/textures/cubemaps/colors/top_yellow.png", "res/textures/cubemaps/colors/bottom_white.png",
		"res/textures/cubemaps/colors/back_red.png","res/textures/cubemaps/colors/front_black.png"
	});*/

	skybox.loadTextures(std::vector<const char*> { "res/textures/cubemaps/sea/right.jpg", "res/textures/cubemaps/sea/left.jpg",
		"res/textures/cubemaps/sea/top.jpg", "res/textures/cubemaps/sea/bottom.jpg",
		"res/textures/cubemaps/sea/back.jpg", "res/textures/cubemaps/sea/front.jpg"
	});

	// Textures
	Texture texture("res/textures/wood_texture.png");
	
	terrain.loadTerrain();
	Material material{ Vec3(), Vec3(), Vec3(),	&texture, &environmentShader};

	//GLuint vboaxis;

	// MESH
	Mesh mesh, planemesh, sphereMesh;
	FileUtils::load_obj("res/mesh/pig.obj", mesh);
	FileUtils::load_obj("res/mesh/sphere.obj", sphereMesh);
	createPlaneMesh(planemesh);

	// MODELS
	 Model model = Loader::loadModel(mesh);
	 Model sphereModel = Loader::loadModel(sphereMesh);
	//Model model2 = loadModel(mesh);
	 Model planemodel{ Loader::loadVAO(planemodel.vertices, &planemesh.getVertices()[0].x, planemesh.getVertices().size() * sizeof(Vec3), 3, 0)	};
	//Model axismodel;

	//vboaxis = loadBufferf(skeletonSketch, 36, 3, 0);
	U32 skyvbo;
	GLuint skyvao = Loader::loadVAO(skyvbo, skybox.skyboxVertices, 108 * sizeof(float), 3, 0);

	// ANIMATIONS
	Animation testAnimation(Transform(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f),
		Transform(Vec3(10, 10, 0), Quaternion(0, 0, 0, 1), 3.0f));

	// ENTITIES
	Entity plane{ Transform(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f), &planemesh, &planemodel,  };
	Entity rock{ Transform(Vec3(10, 0, 0), Quaternion(0, 0, 0, 1), 1.0f), &mesh, &model, &material, &testAnimation,};
	Entity player{ Transform(Vec3(0, 0, 2), Quaternion(0.0f,0.0f,0.0f,1.0f), /*Quaternion(0.5f, -0.5f, -0.4f, -0.6f),*/ 1.0f),
		&mesh, &model, &material,	nullptr, nullptr, nullptr,};

	gInputManager.mapper.addCallback([&player](MappedInput &inputs) {
		if (inputs.find(STATE::player_left)) { player.transform.position.x -= 0.1f; LOG("left");
		}
		if (inputs.find(STATE::player_up)) { player.transform.position.y += 0.1f; }
		if (inputs.find(STATE::player_right)) { player.transform.position.x += 0.1f; }
		if (inputs.find(STATE::player_down)) { player.transform.position.y -= 0.1f; }
	}, 1);

	// get Animation Component
	gAnimationManager.requestNewComponent(player.animatable);

	// SCENE
	Scene scene;
	scene.add(&player);
	scene.add(&rock);
	Entity rocks[10];
	for (int i = 0; i < 10; i++) {
		rocks[i].transform = Transform(Vec3(i * 2.0f, 0.0f, 0.0f), Quaternion(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
		rocks[i].model = &sphereModel;
		rocks[i].mesh = &sphereMesh;
		rocks[i].material = &material;
		scene.add(&rocks[i]);
	}
	//Renderer renderer(&camera);

	FollowCamera followCam(&player);
	Renderer renderer(&followCam);
	renderer.initialize();
	gInputManager.mapper.addCallback([&renderer, &camera, &followCam](MappedInput &inputs) {
		if (inputs.find(ACTION::change_camera_3rdperson)) { renderer.setCamera(&followCam); }
		else if (inputs.find(ACTION::change_camera_debug)) { renderer.setCamera(&camera); }
	}, 2);

	gInputManager.mapper.addCallback([&camera](MappedInput &inputs) {
		if (inputs.find(STATE::camera_forward)) { camera.Translate(Vec3(0, 0, 2)); }
		if (inputs.find(STATE::camera_backward)) { camera.Translate(Vec3(0, 0, -2)); }
		if (inputs.find(STATE::camera_left)) { camera.Translate(Vec3(2, 0, 0)); LOG("left"); }
		if (inputs.find(STATE::camera_right)) { camera.Translate(Vec3(-2, 0, 0)); }
		if (inputs.find(STATE::camera_up)) { camera.Translate(Vec3(0, -2, 0)); }
		if (inputs.find(STATE::camera_down)) { camera.Translate(Vec3(0, 2, 0)); }
	}, 2);

	camera.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	camera.setRotation(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
	followCam.setPosition(Vec3(0.0f, 0.0f, 0.0f));
	followCam.setRotation(Vec3(0.0f, 0.707f, 0.0f), 1.0f);

	Time time;
	U32 FPS = 0;
	//Loop until the user closes the window 
	time.init();
	time.start();

	//Vec3 startVector = pig.transform.position;
	//Vec3 endVector(10,10,0);

	AABB3D *test = gCollisionManager.requestAABB3D();
	int tmpPos = -10;
	test->max = Vec3(tmpPos + 3.0f, 3.0f, 3.0f);
	test->min = Vec3(tmpPos + -3.0f, -3.0f, -3.0f);

	rock.collidable = gCollisionManager.requestAABB3D();
	player.collidable = gCollisionManager.requestAABB3D();
	player.collidable->min -= Vec3(2, 2, 2);
	player.collidable->max += Vec3(1, 1, 1);

	renderer.setSkybox(&skybox);

	gAnimationManager.logStates();
	float counter = 0;
	bool testB = true;
	while (!window.isClosed())
	{
		window.clear();

		gInputManager.mapper.dispatch();
		counter += 0.1f;
		//pig.position = ani_lerp(startVector, endVector, beta);
		Vec3 newPosition = rock.animation->getPosition(cosf(counter * 180.0f / (float)PI) * 0.5f + 0.5f);
		rock.transform.position = newPosition;
		rock.collidable->min = newPosition;
		rock.collidable->max = newPosition + Vec3(1, 1, 1);

		//pig.transform.rotation.rotate(Vec3(0,1,0), 0.001f);
		player.transform.scale = 0.1f*sinf(counter*180.0f / (float)PI) + 1.0f;
		camera.setPosition(Vec3(counter, counter, counter));
		
		camera.update();
		followCam.update((float)time.getDelta() / 1000);
		camera.setPosition(Vec3(counter*1000, 0,0));

		gSystemManager.update();
		gAnimationManager.update((float)time.getDelta() / 1000);
		//gCollisionManager.update(10);

		renderer.render(skybox, skyvao, skyBoxShader);
		renderer.render(scene, shader, sun);
		renderer.renderAABBs(gCollisionManager.getCollidables(), gCollisionManager.getNumCollidables(), aabbShader);

		// DEFAULT Rendering Stuff****************
		// DEFAULT PLANE
		plane.transform.position.y += (float)sin(time.getPastTime()*10.0);
		if (testB)
		{
			renderer.renderLINES(plane, defaultShader);
			testB = false;
		}
		renderer.renderLINES(plane, defaultShader);
		//renderer.renderRenderSkin(player, skinShader);
		renderer.renderReflection(player);

		for (int i = 0; i < 10; i++){
			//rocks[i].transform.position.x += sin(counter * 180.0f / (float)pi) * 0.03f - 0.002;
			rocks[i].transform.position.y -= 9.81f * 0.001f;
			if (rocks[i].transform.position.y < 0.0f) {
				rocks[i].transform.position.y = 30;
			}
		
			//renderer.renderReflection(rocks[i]);
		}
		//renderer.renderTerrain(terrain.getModel().vertices, terrainShader, 3, terrain.getNumIndices());

		window.update();
		//TwDraw();
		FPS++;
		time.measureTime();
		if (time.getPastTime() >= 1000l) {
			time.erasePastTime();
			LOG("FPS", FPS);
			FPS = 0;
		}
	}
	window.shutDown();
	
}