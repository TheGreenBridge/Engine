#pragma once

///PLATFORM
#include "..\src\platform\windows\window.h"
#include "..\src\platform\windows\InputManager.h"
#include "..\src\systems\CollisionManager.h"
#include "..\src\systems\AnimationManager.h"
#include "..\src\platform\windows\Console.h"
#include "..\src\systems\SystemManager.h"

#include <application\Application.h>

#include <entity\Camera.h>
#include <entity\Entity.h> // MESH MODEL MATERIAL(TEXTURE) ANIMATION(TRANSFORM)
#include <entity\FollowCamera.h>

#include <EngineCore.h>

///RENDER

#include <graphics\api\Shader.h>
#include <graphics\api\Renderer.h>
#include <graphics\api\Loader.h>
#include <graphics\api\Texture.h>
#include <graphics\font\Font.h>
#include <graphics\api\Framebuffer.h>
#include <graphics\api\UniformBuffer.h>


///UTILS
#include <math\maths.h>
#include <utils\Time.h>
#include <utils\Log.h>
#include <utils\fileutils.h>

//#include <AntTweakBar.h>
// NAMESPACES
using namespace engine;
using namespace engine::memory;
using namespace engine::collision;

#define MEM_STORAGE 8192 // 8 KiB = 8 * 2^10

// GLOBALS
//Vec3 fPoint(10, 10, 10);
class EngineTest : public Application {
private:
	
	// SYSTEMS
	SystemManager gSystemManager;
	InputManager gInputManager;
	AnimationManager gAnimationManager;
	CollisionManager gCollisionManager;

	Console gConsole;
	Renderer* renderer;

	
	Camera* camera;

	// TESTS
	Shader* pbrShader, *skyBoxShader, *fontShader, *shader;
	Cubemap* skybox;

	VertexArray* vao, *skyvao;
	VertexBuffer* vbo, *skyvbo;
	UniformBuffer* ubo;
	Entity *entity;

	Font font;
	
	void stop_();
	void run_();
	void pause_();
	void init_();

public:
	EngineTest();
	~EngineTest();
};