//------------------------------------------------------------------------------
// EngineTest.cpp
//
// This is a test of the engine
//
// Author: Sumi
// Created: xx.xx.xx
// Changed: 21.07.18
//------------------------------------------------------------------------------
//

#include "EngineTest.h"

#include <iostream>
#include <input\RawInput.h>
///MEMORY

#include <graphics\api\VertexArray.h>
#include <memory\Memory.h>
#include <asset\AssetLoader.h>

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace engine::graphics;
using namespace engine::collision;
using namespace engine;

EngineTest::EngineTest() :
	Application("Project Green Bridge", 1280, 720), terrain()
{

}

EngineTest::~EngineTest()
{

}

void EngineTest::init_()
{
	////////////////////////////////////////////////////////////////
	pbrShader = Engine::gShaderManager.createShader("res/shader/material/pbr_material.glsl");
	skyBoxShader = Engine::gShaderManager.createShader("res/shader/default/boxshader.glsl");
	
	
	shader = NEW_MEM Shader("res/shader/tests/testShader.glsl");
	camera = NEW_MEM Camera(90.0f, 1.7777f, 0.1f, 800.0f);
	renderer = NEW_MEM Renderer();
	renderer->setCamera(camera);
	//vbo = Engine::gBufferManager.createVertexBuffer(6 * 2 * sizeof(U32), BufferUsage::DYNAMIC);
	skyvbo = Engine::gBufferManager.createVertexBuffer(1 * sizeof(U32), BufferUsage::STATIC);
	//vao = NEW_MEM VertexArray();
	skyvao = NEW_MEM VertexArray();
	skybox = NEW_MEM Cubemap();
	////////////////////////////////////////////////////////////////


	EntityManager *entMgr = Engine::getEntityManager();
	ComponentManager *compMgr = Engine::getComponentManager();
	SystemManager *sysMgr = Engine::getSystemManager();

	entity = entMgr->newEntity();	
	terrain.init();

	AssetLoader::loadScene(*renderer, "res/scenes/scene.json");

	//srand(time(NULL));
	//for (int i = 0; i < 3; ++i)
	//{
	//	Entity* ent = AssetLoader::loadEntity("res/entities/entity.json");
	//	Renderable3D * renderable = Engine::getComponentManager()->GetComponent<Renderable3D>(ent);
	//	/* initialize random seed: */
	//	/* generate secret number between 1 and 10: */
	//	renderable->transform->position.x = rand() % 20 + 1;
	//	renderable->transform->position.y = rand() % 20 + 1;
	//	renderable->transform->position.z = rand() % 20 + 1;
	//	renderer->submit(*renderable);
	//}

	/*compMgr->AddComponent<Model>(entity);
	compMgr->AddComponent<Mesh>(entity);*/
	/*compMgr->AddComponent<PBRMaterial>(entity,
		Texture("res/textures/pbr_rust/rustediron2_basecolor.png"),
		Texture("res/textures/pbr_rust/rustediron2_metallic.png"),
		Texture("res/textures/pbr_rust/rustediron2_roughness.png"),
		pbrShader);*/
	//PBRMaterial *pbrmaterial = compMgr->GetComponent<PBRMaterial>(entity);
	//Model *model = compMgr->GetComponent<Model>(entity);
	//Mesh *mesh = compMgr->GetComponent<Mesh>(entity);
	//FileUtils::load_obj("res/mesh/pig.obj", *mesh);
	//*model = Loader::loadModel(*mesh);
	//entity->mesh = mesh;
	////entity->pbrmaterial = pbrmaterial;
	//entity->model = model;

	// MANAGER
	gSystemManager.registerSystem(gInputManager);
	gSystemManager.registerSystem(gAnimationManager);
	gSystemManager.registerSystem(gCollisionManager);

	gAnimationManager.startUp();
	gAnimationManager.loadAnimations();
	gCollisionManager.startUp();

	window.setKeyboardCallback(RawInput::key_callback);

	skybox->loadTextures(std::vector<const char*> { "res/textures/cubemaps/sea/right.jpg", "res/textures/cubemaps/sea/left.jpg",
		"res/textures/cubemaps/sea/top.jpg", "res/textures/cubemaps/sea/bottom.jpg",
		"res/textures/cubemaps/sea/back.jpg", "res/textures/cubemaps/sea/front.jpg"
	});

	gInputManager.mapper.addCallback([=](MappedInput &inputs) {

		F32 speed = 1000;
		F32 time = Engine::getSystemManager()->getDeltaTimef();
		long long timel = Engine::getSystemManager()->getDeltaTime();
		F32 distance = speed * time;

		if (inputs.find(STATE::camera_forward)) { camera->Translate(Vec3(0, 0, distance)); }
		if (inputs.find(STATE::camera_backward)) { camera->Translate(Vec3(0, 0, -distance)); }
		if (inputs.find(STATE::camera_left)) { camera->Translate(Vec3(distance, 0, 0)); }
		if (inputs.find(STATE::camera_right)) { camera->Translate(Vec3(-distance, 0, 0)); }
		if (inputs.find(STATE::camera_up)) { camera->Translate(Vec3(0, -distance, 0)); }
		if (inputs.find(STATE::camera_down)) { camera->Translate(Vec3(0, distance, 0)); }
		//if (inputs.find(STATE::camera_down)) { LOG_ERROR("pause"); }

	}, 2);

	skyvbo->resize(108*sizeof(F32));
	skyvbo->setData(108 * sizeof(F32), skybox->skyboxVertices);
	BufferLayout skylayout;
	skylayout.pushFloat(3);
	skyvao->addBuffer(skyvbo, skylayout);

	renderer->setSkybox(skybox);

	gConsole.runConsole();



	Mesh mesh;

	/*
	FileUtils::load_obj(geometryPath.c_str(), mesh);

	VertexBuffer* vbuffer = Engine::gBufferManager.createVertexBuffer(mesh.getVertices().size() * sizeof(Vec3));
	VertexBuffer* nbuffer = Engine::gBufferManager.createVertexBuffer(mesh.getNormals().size() * sizeof(Vec3));
	VertexBuffer* uvbuffer = Engine::gBufferManager.createVertexBuffer(mesh.getUVs().size() * sizeof(Vec2));

	vbuffer->setData(mesh.getVertices().size() * sizeof(Vec3), mesh.getVertices().data());
	nbuffer->setData(mesh.getNormals().size() * sizeof(Vec3), mesh.getNormals().data());
	uvbuffer->setData(mesh.getUVs().size() * sizeof(Vec2), mesh.getUVs().data());

	BufferLayout layout;
	layout.pushFloat(3);
	BufferLayout layout_uvs;
	layout_uvs.pushFloat(2);

	VertexArray* vao = Engine::gBufferManager.createVertexArray();

	vao->addBuffer(vbuffer, layout);
	vao->addBuffer(nbuffer, layout);
	vao->addBuffer(uvbuffer, layout_uvs);

	model->vertices = vao;
	model->numVertices = mesh.numVertices;*/




}

U32 counter = 0;

void EngineTest::run_()
{
	gInputManager.mapper.dispatch();
	camera->update();

	renderer->render(*skybox, *skyvao, *skyBoxShader);

	renderer->render();


	
	//terrain.update();

	counter = ++counter % 25;

	renderer->renderTerrain(terrain);

	std::string fps = "FPS: " + std::to_string(Engine::getSystemManager()->getFPS());
	renderer->renderGUIText(fps.c_str(), 0.0f, 700.0f, 0.4f, Color::Green);
	renderer->renderGUIText("version: 0.0.01", 0.0f, 680.0f, 0.4f, Color::Green);
	renderer->renderGUIText("@sumi", 0.0f, 660.0f, 0.4f, Color::Green);
}

void EngineTest::pause_()
{
}

void EngineTest::stop_()
{
}
