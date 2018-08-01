//#include "Game.h"
//
//#include <input\RawInput.h>
/////MEMORY
//
//#include <entity\mesh\plane.h>
//#include <entity\Camera.h>
//#include <entity\Entity.h> // MESH MODEL MATERIAL(TEXTURE) ANIMATION(TRANSFORM)
//#include <entity\FollowCamera.h>
//
//#include <EngineCore.h>
//
/////RENDER
//
//#include <graphics\api\Shader.h>
//#include <graphics\api\Renderer.h>
//#include <graphics\api\Loader.h>
//#include <graphics\api\Texture.h>
//
//#include <entity\Scene.h>
//#include <entity\Light.h>
//#include <entity\Terrain.h>
//
//
//
/////ANIMATION
////#include "src\graphics\animation\skinning\SkinnedMesh.h"
//#include <graphics\animation\Animation.h>
//#include <graphics\animation\skinning\RenderableSkin.h>
//#include <graphics\animation\AnimationHandle.h>
//#include <graphics\animation\interpolation.h>
//
/////COLLISION
//#include <collision\AABB.h>
//
//
/////UTILS
//#include <math\maths.h>
//#include <utils\Time.h>
//#include <utils\Log.h>
//#include <utils\fileutils.h>
//
///// SCRIPTING
//#include <scripting\LuaScript.h>
//
//#include <cmath>
//
//using namespace engine::graphics;
//using namespace engine::collision;
//using namespace engine::entity;
//using namespace engine;
//
//Game::Game():
//	Application("Project Green Bridge", 1280, 720)
//{
//}
//
//Game::~Game()
//{
//}
//
//void Game::init()
//{
//	Engine::Initialize();
//}
//
//void Game::pause()
//{
//
//}
//
//void Game::stop()
//{
//
//}
//
//// Entity
//// Renderable
//// Material
//// Sound
//// Collidable3D
//// Collidable2D
//// Model
//// Controlable
//// SkinAnimation
//// AI
//// Physics
//
//void Game::run()
//{
//	Shader pbrShader("res/shader/material/pbr_material.glsl");
//	Shader defaultShader("res/shader/default/default.vert", "res/shader/default/default.frag");
//	Shader shader("res/shader/default/defaultmaterial.vert", "res/shader/default/defaultmaterial.frag");
//	Shader skyBoxShader("res/shader/default/boxshader.vert", "res/shader/default/boxshader.frag");
//	Shader skinShader("res/shader/animation/rigshader.glsl");
//	Shader aabbShader("res/shader/default/aabbshader.vert", "res/shader/default/aabbshader.frag");
//	Shader terrainShader("res/shader/terrain/terrainshader.vert", "res/shader/terrain/terrainshader.frag");
//	Shader environmentShader("res/shader/environment/environmentShader.vert", "res/shader/environment/environmentShader.frag");
//	Shader oneColorShader("res/shader/post_processing/one_color.glsl");
//	Shader combineShader("res/shader/post_processing/combine.glsl");
//	Shader basicShader("res/shader/default/basic.vert", "res/shader/default/basic.frag");
//
//
//	
//	
//	PBRMaterial pbrmaterial = PBRMaterial(
//		Texture("res/textures/pbr_rust/rustediron2_basecolor.png"),
//		Texture("res/textures/pbr_rust/rustediron2_metallic.png"),
//		Texture("res/textures/pbr_rust/rustediron2_roughness.png"),
//		pbrShader);;
//
//	//HALT();
//
//	// VARIABLES
//	Light sun(Vec3(5, 3, 0), Vec3(1.0, 0.0, 0.0));
//	Terrain terrain;
//
//	
//	Cubemap skybox;
//	Texture texture("res/textures/wood_texture.png");
//	Texture texture_white("res/textures/colors/color_white.png");
//
//	Material material{ Vec3(), Vec3(), Vec3(),	&texture, &environmentShader };
//	
//	Mesh mesh, planemesh, sphereMesh;
//	
//	FileUtils::load_obj("res/mesh/pig.obj", mesh);
//	FileUtils::load_obj("res/mesh/default/cube.obj", sphereMesh);
//	createPlaneMesh(planemesh);
//
//	Model model;
//	Model sphereModel;
//	Model planemodel;
//
//	model = Loader::loadModel(mesh);
//	sphereModel = Loader::loadModel(sphereMesh);
//	//planemodel = Model{ Loader::loadVAO(planemodel.vbo_vertices, &planemesh.getVertices()[0].x, planemesh.getVertices().size() * sizeof(Vec3), 3, 0) };
//	
//	
//	
//	U32 skyvbo;
//	//GLuint skyvao = Loader::loadVAO(skyvbo, skybox.skyboxVertices, 108 * sizeof(float), 3, 0);
//	Animation testAnimation(Transform(Vec3(0, 0, 0), Quaternion(0, 0, 0, 1), 1.0f),
//		Transform(Vec3(10, 10, 0), Quaternion(0, 0, 0, 1), 3.0f));
//	Entity plane;
//	plane = Entity{ Transform(Vec3(0, 10.0f, 0), Quaternion(0, 0, 0, 1), 1.0f), &planemesh, &planemodel, };
//	
//	Entity rock{ Transform(Vec3(10, 0, 0), Quaternion(0, 0, 0, 1), 1.0f), &sphereMesh, &sphereModel, &material, &testAnimation, };
//	
//	Entity player{ Transform(Vec3(0, 0, 2), Quaternion(0.0f,0.0f,0.0f,1.0f), /*Quaternion(0.5f, -0.5f, -0.4f, -0.6f),*/ 1.0f),
//		&mesh, &model, &material,	nullptr, nullptr, nullptr, };
//	player.transform.rotation.rotate(Vec3(-90.0f, 0, 0));
//	
//	
//	Camera camera(90.0f, 1.7777f, 0.1f, 800.0f);
//	FollowCamera followCam(&player);
//	Renderer renderer(&camera);
//	Scene scene;
//	Time time;
//	U32 FPS = 0;
//	//AABB3D *test = gCollisionManager.requestAABB3D();
//	Entity rocks[10];
//
//	
//
//	rock.pbrmaterial = &pbrmaterial;
//
//	LuaScript script("res/entities/test.lua");
//	Entity testEntity;
//	testEntity.pbrmaterial = &pbrmaterial;
//	Mesh testMesh;
//	FileUtils::load_obj(script.get <std::string>("entity.model").c_str(), testMesh);
//	testEntity.mesh = &testMesh;
//	Model testModel = Loader::loadModel(testMesh);
//	testEntity.model = &testModel;
//
//	float player_x = script.get<float>("entity.position.x");
//
//	
//	testEntity.transform.position.x = script.get<float>("entity.position.x");
//	testEntity.transform.position.y = script.get<float>("entity.position.y");
//	testEntity.transform.position.z = script.get<float>("entity.position.z");
//
//
//	//script.callFunction("onInit");
//	//script.callFunction("onRepeat");
//
//	//gSystemManager.testManager();
//	// MANAGER
//	gSystemManager.registerSystem(gInputManager);
//	gSystemManager.registerSystem(gAnimationManager);
//	gSystemManager.registerSystem(gCollisionManager);
//
//	gAnimationManager.startUp();
//	gAnimationManager.loadAnimations();
//	gCollisionManager.startUp();
//
//	//window.setCursorCallback(RawInput::cursor_position_callback);
//	//window.setKeyboardCallback(RawInput::key_callback);
//
//	window.setKeyboardCallback(RawInput::key_callback);
//	
//	// MOUSE INPUT
//	/*I32 xPosition = 0, yPosition = 0;
//	gInputManager.mapper.addCallback([&camera, &xPosition, &yPosition](MappedInput &inputs) {
//		I32 currentX = inputs.ranges.find(RANGE::camera_x)->second;
//		I32 currentY = inputs.ranges.find(RANGE::camera_y)->second;
//	
//		I32 dx = (I32)currentX - xPosition;
//		I32 dy = (I32)currentY - yPosition;
//
//		F32 sens = 0.01f;
//		F32 ry = -dy * sens;
//		F32 rx = -dx * sens;
//		
//		xPosition = (I32)currentX;
//		yPosition = (I32)currentY;
//		
//		camera.Rotate(Vec3(1, 0, 0), -ry);
//		camera.Rotate(Vec3(0, 1, 0), -rx);
//
//	}, 2);*/
//
//	skybox.loadTextures(std::vector<const char*> { "res/textures/cubemaps/sea/right.jpg", "res/textures/cubemaps/sea/left.jpg",
//		"res/textures/cubemaps/sea/top.jpg", "res/textures/cubemaps/sea/bottom.jpg",
//		"res/textures/cubemaps/sea/back.jpg", "res/textures/cubemaps/sea/front.jpg"
//	});	
//	terrain.loadTerrain();
//	
//	
//	pbrmaterial.albedo = Vec3(0.5, 0.0, 0.0);
//	pbrmaterial.ao = 1.0f;
//	pbrmaterial.roughness = 0.5f;
//	pbrmaterial.metallic = 0.5f;
//	player.pbrmaterial = &pbrmaterial;
//	renderer.initialize();
//	camera.setPosition(Vec3(0.0f, 0.0f, -2.0f));
//	camera.setRotation(Vec3(0.0f, 0.0f, 0.0f), 1.0f);
//	camera.setSpeed(0.1f);
//	followCam.setPosition(Vec3(0.0f, 0.0f, 0.0f));
//	followCam.setRotation(Vec3(0.0f, 0.707f, 0.0f), 1.0f);
//	gAnimationManager.requestNewComponent(player.animatable);
//	scene.add(&player);
//	scene.add(&rock);
//	
//	for (int i = 0; i < 10; i++) {
//		rocks[i].transform = Transform(Vec3(0.0f, 0.0f, i * 2.0f - 10.0f), Quaternion(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);
//		rocks[i].model = &sphereModel;
//		rocks[i].mesh = &sphereMesh;
//		rocks[i].material = &material;
//		rocks[i].pbrmaterial = &pbrmaterial;
//		scene.add(&rocks[i]);
//	}
//	// INPUT
//
//	gInputManager.mapper.addCallback([&player](MappedInput &inputs) {
//		if (inputs.find(STATE::player_right)) { player.transform.position.x += 0.1f; }
//		if (inputs.find(STATE::player_left)) { player.transform.position.x -= 0.1f; }
//		if (inputs.find(STATE::player_up)) { player.transform.position.y += 0.1f; }
//		if (inputs.find(STATE::player_down)) { player.transform.position.y -= 0.1f; }
//	}, 1);
//
//	gInputManager.mapper.addCallback([&renderer, &camera, &followCam](MappedInput &inputs) {
//		if (inputs.find(ACTION::change_camera_3rdperson)) { renderer.setCamera(&followCam); }
//		else if (inputs.find(ACTION::change_camera_debug)) { renderer.setCamera(&camera); }
//	}, 2);
//
//	gInputManager.mapper.addCallback([&camera](MappedInput &inputs) {
//		if (inputs.find(STATE::camera_forward)) { camera.Translate(Vec3(0, 0, 2)); }
//		if (inputs.find(STATE::camera_backward)) { camera.Translate(Vec3(0, 0, -2)); }
//		if (inputs.find(STATE::camera_left)) { camera.Translate(Vec3(2, 0, 0)); }
//		if (inputs.find(STATE::camera_right)) { camera.Translate(Vec3(-2, 0, 0)); }
//		if (inputs.find(STATE::camera_up)) { camera.Translate(Vec3(0, -2, 0)); }
//		if (inputs.find(STATE::camera_down)) { camera.Translate(Vec3(0, 2, 0)); }
//	}, 2);
//
//	//Loop until the user closes the window 
//	time.init();
//	time.start();
//	
//	int tmpPos = -10;
//
//	//rock.collidable = gCollisionManager.requestAABB3D();
//	/*player.collidable = gCollisionManager.requestAABB3D();
//	player.collidable->min -= Vec3(2, 2, 2);
//	player.collidable->max += Vec3(1, 1, 1);*/
//
//	renderer.setSkybox(&skybox);
//
//	gAnimationManager.logStates();
//	float counter = 0;
//
//	while (!window.isClosed())
//	{
//		window.clear();
//		
//		gInputManager.mapper.dispatch();
//		counter += 0.01f;
//		Vec3 newPosition = rock.animation->getPosition(cosf(counter * 180.0f / (float)PI) * 0.5f + 0.5f);
//			
//		player.transform.rotation.rotate(Vec3(0, counter/1000, 0));
//		//player.transform.scale = 0.01f*sinf(counter*180.0f / (float)PI) + 1.0f;
//		
//		camera.update();
//		followCam.update((float)time.getDelta() / 1000);
//
//		gSystemManager.update();
//		gAnimationManager.update((float)time.getDelta() / 1000);
//		//gCollisionManager.update(10);
//
//
//		//renderer.render(skybox, skyvao, skyBoxShader);
//		renderer.renderAABBs(gCollisionManager.getCollidables(), gCollisionManager.getNumCollidables(), aabbShader);
//
//		renderer.render(player, oneColorShader);
//
//		// DEFAULT Rendering Stuff****************
//		// DEFAULT PLANE
//		//plane.transform.position.y += (float)sin(time.getPastTime()*10.0);
//		renderer.renderLINES(plane, defaultShader);
//		
//		renderer.renderRenderSkin(player, skinShader);
//		//renderer.renderReflection(player);
//
//		/*for (int i = 0; i < 10; i++){
//			rocks[i].transform.position.x += sin(counter * 180.0f / (float)pi) * 0.03f - 0.002;
//			rocks[i].transform.position.y -= 9.81f * 0.001f;
//			if (rocks[i].transform.position.y < 0.0f) {
//				rocks[i].transform.position.y = 30;
//			}*/
//		
//			//renderer.renderreflection(rocks[i]);
//		rock.pbrmaterial->metallic = 0;
//		rock.transform.position = Vec3(-10, 0, 0);
//		
//		Light &lightPos = renderer.getLight(0);
//		lightPos.setPosition(Vec3(player.transform.position.x, player.transform.position.y, 5) );
//
//		for (int x = 0; x < 5; ++x) {
//			rock.transform.position.x += 3;
//			rock.pbrmaterial->metallic += (float)x / 5;
//			rock.transform.position.y = 0;
//			rock.pbrmaterial->roughness = 0;
//			for (int y = 0; y < 5; ++y) {
//				rock.transform.position.y += 3;	
//				rock.pbrmaterial->roughness += (float)y / 5;
//				renderer.renderPBR(rock);
//			}
//		}
//		
//		//renderer.render(testEntity, texture_white, basicShader);
//		renderer.renderPBR(testEntity);
//		//}
//		//
//		
//		//renderer.renderTerrain(terrain.getModel().vertices, terrainShader, 3, terrain.getNumIndices());
//
//		window.update();
//		FPS++;
//		time.measureTime();
//		if (time.getPastTime() >= 1000l) {
//			time.erasePastTime();
//			LOG("FPS", FPS);
//			FPS = 0;
//		}
//	}
//	window.shutDown();	
//}