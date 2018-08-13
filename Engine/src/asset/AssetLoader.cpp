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

	Entity* AssetLoader::loadEntity(const char * path)
	{
		LuaScript script(path);

		//Shader pbrShader("res/shader/material/pbr_material.glsl");

		EntityManager *entMgr = Engine::getEntityManager();
		ComponentManager *compMgr = Engine::getComponentManager();

		Entity *entity = entMgr->newEntity();
		entity->transform.position.x = script.get<float>("entity.position.x");
		entity->transform.position.y = script.get<float>("entity.position.y");
		entity->transform.position.z = script.get<float>("entity.position.z");

		std::string shaderPath = "res/shader/default/defaultmaterial.glsl";
		std::string geometryPath = "res/mesh/pig.obj";
		std::string texturePath = "res/textures/wood_texture.png";
		
		// Geometry
		
		Model *model = compMgr->AddComponent<Model>(entity);	
		Mesh mesh;
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
		model->numVertices = mesh.numVertices;

		// Material

		Material* material = compMgr->AddComponent<Material>(entity);
		Shader* shader = Engine::gShaderManager.createShader(shaderPath.c_str());

		material->shader = shader;
		//material->shader->setUniformBlockIndex("vs_uniforms", 0);
		//material->shader->setUniformBlockIndex("fs_uniforms", 1);
		material->texture = Engine::gResourceManager.getTexture(texturePath.c_str());

		// Final Renderable

		Renderable3D* renderable = compMgr->AddComponent<Renderable3D>(entity);
		renderable->transform = &entity->transform;
		renderable->model = model;
		renderable->material = material;
		
		return entity;
	}
}

