#include "AssetLoader.h"
#include <scripting\LuaScript.h>
#include <entity\Entity.h>
#include <EngineCore.h>
#include <graphics\pbr\PBRMaterial.h>
#include <graphics\Mesh.h>
#include <graphics\Model.h>
#include <utils\FileUtils.h>

#include <graphics\api\VertexArray.h>
#include <graphics\api\IndexBuffer.h>

#include <Components\Renderable3D.h>

#include <memory\Memory.h>
#include <EngineCore.h>

namespace engine {

	using namespace graphics;
	using namespace component;

	void AssetLoader::loadEntity(const char * path)
	{
		LuaScript script(path);

		//Shader pbrShader("res/shader/material/pbr_material.glsl");

		EntityManager *entMgr = Engine::getEntityManager();
		ComponentManager *compMgr = Engine::getComponentManager();

		Entity *entity = entMgr->newEntity();
		entity->transform.position.x = script.get<float>("entity.position.x");
		entity->transform.position.y = script.get<float>("entity.position.y");
		entity->transform.position.z = script.get<float>("entity.position.z");

		
		Model *model = compMgr->AddComponent<Model>(entity);	

		Renderable3D* renderable = compMgr->AddComponent<Renderable3D>(entity);
		renderable->transform = &entity->transform;
		renderable->model = model;
		renderable->material;

		Material* material = compMgr->AddComponent<Material>(entity);
		material->shader = Engine::gShaderManager.createShader("");
		material->texture = Engine::gTextureManager.createTexture();
		
		material->texture->loadImage("");

		UniformBuffer* uniformBuffer = 		Engine::gBufferManager.createUniformBuffer(10);
		material->uniforms = uniformBuffer;
		
		
		struct {
			F32 test;
			F32 test3;
		} uniform;

		



		/*compMgr->AddComponent<PBRMaterial>(entity,
			Texture("res/textures/pbr_rust/rustediron2_basecolor.png"),
			Texture("res/textures/pbr_rust/rustediron2_metallic.png"),
			Texture("res/textures/pbr_rust/rustediron2_roughness.png"),
			pbrShader);*/

		//PBRMaterial *pbrmaterial = compMgr->GetComponent<PBRMaterial>(entity);
		
		
		Mesh mesh;
		FileUtils::load_obj("res/mesh/pig.obj", mesh);

		VertexBuffer* position_buffer = Engine::gBufferManager.createVertexBuffer(mesh.getVertices().size(), BufferUsage::STATIC);
		VertexBuffer* normal_buffer = Engine::gBufferManager.createVertexBuffer(mesh.getNormals().size(), BufferUsage::STATIC);
		VertexBuffer* uv_buffer = Engine::gBufferManager.createVertexBuffer(mesh.getUVs().size(), BufferUsage::STATIC);
		
		BufferLayout layout;
		layout.pushFloat(3);

		VertexArray* vao = Engine::gBufferManager.createVertexArray();

		vao->addBuffer(position_buffer, layout);
		vao->addBuffer(normal_buffer, layout);
		vao->addBuffer(uv_buffer, layout);


		model->vertices = vao;

		

		//model = Loader::loadModel(*mesh);

		//entity->mesh = mesh;
		//entity->pbrmaterial = pbrmaterial;
		//entity->model = model;*/

	}
}

