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


using namespace engine::graphics;
using namespace engine::collision;
using namespace engine::entity;
using namespace engine;

EngineTest::EngineTest() :
	Application("Project Green Bridge", 1280, 720),
	pbrShader("res/shader/material/pbr_material.glsl"),
	skyBoxShader("res/shader/default/boxshader.glsl"),
	fontShader("res/shader/ui/text.glsl"),
	shader("res/shader/tests/testShader.glsl"),
	camera(90.0f, 1.7777f, 0.1f, 800.0f),
	renderer(&camera),
	vbo(6 * 2 * sizeof(U32), BufferUsage::DYNAMIC),
	skyvbo(1 * sizeof(U32), BufferUsage::STATIC)
{
}

EngineTest::~EngineTest()
{
}

void EngineTest::init_()
{
	EntityManager *entMgr = Engine::getEntityManager();
	ComponentManager *compMgr = Engine::getComponentManager();
	SystemManager *sysMgr = Engine::getSystemManager();

	entity = entMgr->newEntity();

	entity = entMgr->getEntity(entity->m_UniqueId.id);

	std::cout << "entity id: " << entity->m_UniqueId.id << std::endl;

	compMgr->AddComponent<Model>(entity);
	compMgr->AddComponent<Mesh>(entity);
	compMgr->AddComponent<PBRMaterial>(entity,
		Texture("res/textures/pbr_rust/rustediron2_basecolor.png"),
		Texture("res/textures/pbr_rust/rustediron2_metallic.png"),
		Texture("res/textures/pbr_rust/rustediron2_roughness.png"),
		pbrShader);

	PBRMaterial *pbrmaterial = compMgr->GetComponent<PBRMaterial>(entity);
	Model *model = compMgr->GetComponent<Model>(entity);
	Mesh *mesh = compMgr->GetComponent<Mesh>(entity);

	FileUtils::load_obj("res/mesh/pig.obj", *mesh);
	*model = Loader::loadModel(*mesh);

	entity->mesh = mesh;
	entity->pbrmaterial = pbrmaterial;
	entity->model = model;

	renderer.setCamera(&camera);

	// MANAGER
	gSystemManager.registerSystem(gInputManager);
	gSystemManager.registerSystem(gAnimationManager);
	gSystemManager.registerSystem(gCollisionManager);

	gAnimationManager.startUp();
	gAnimationManager.loadAnimations();
	gCollisionManager.startUp();

	window.setKeyboardCallback(RawInput::key_callback);

	skybox.loadTextures(std::vector<const char*> { "res/textures/cubemaps/sea/right.jpg", "res/textures/cubemaps/sea/left.jpg",
		"res/textures/cubemaps/sea/top.jpg", "res/textures/cubemaps/sea/bottom.jpg",
		"res/textures/cubemaps/sea/back.jpg", "res/textures/cubemaps/sea/front.jpg"
	});

	gInputManager.mapper.addCallback([=](MappedInput &inputs) {
		if (inputs.find(STATE::camera_forward)) { camera.Translate(Vec3(0, 0, 2)); }
		if (inputs.find(STATE::camera_backward)) { camera.Translate(Vec3(0, 0, -2)); }
		if (inputs.find(STATE::camera_left)) { camera.Translate(Vec3(2, 0, 0)); }
		if (inputs.find(STATE::camera_right)) { camera.Translate(Vec3(-2, 0, 0)); }
		if (inputs.find(STATE::camera_up)) { camera.Translate(Vec3(0, -2, 0)); }
		if (inputs.find(STATE::camera_down)) { camera.Translate(Vec3(0, 2, 0)); }
	}, 2);

	
	//skyvao = Loader::loadVAO(skyvbo, skybox.skyboxVertices, 108 * sizeof(float), 3, 0);
	skyvbo.resize(108*sizeof(F32));
	skyvbo.setData(108 * sizeof(F32), skybox.skyboxVertices);
	VertexBufferLayout skylayout;
	skylayout.pushFloat(3);
	skyvao.addBuffer(skyvbo, skylayout);

	renderer.setSkybox(&skybox);

	gConsole.runConsole();

	font.init();
	
	vbo.setData(6 * 2 * sizeof(float), vertices);
	VertexBufferLayout layout;
	layout.pushFloat(2);
	vao.addBuffer(vbo, layout);
}

// Entity
// Renderable
// Material
// Sound
// Collidable3D
// Collidable2D
// Model
// Controlable
// SkinAnimation
// AI
// Physics

float counter = 0;

void EngineTest::run_()
{
	gInputManager.mapper.dispatch();
	camera.update();

	Engine::Update();

	counter += 0.1f;
	renderer.render(skybox, skyvao, skyBoxShader);
	font.renderText(fontShader, camera, "SUMI", 0.5f, 0.5f, 1.0f, Vec3(1.0, 0.0, 0.0));
	shader.enable();
	vao.bind();
	vertices[2] += 0.01f* cos(counter);
	vertices[3] += 0.01f* sin(counter);
	vbo.setData(6 * 2 * sizeof(float), vertices);
	vao.draw(6);

	renderer.renderPBR(*entity);
}

void EngineTest::pause_()
{
}

void EngineTest::stop_()
{
}
