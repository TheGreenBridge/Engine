#include "AssetLoader.h"
#include <scripting\LuaScript.h>
#include <entity\Entity.h>
#include <EngineCore.h>
#include <graphics\pbr\PBRMaterial.h>
#include <graphics\Mesh.h>
#include <graphics\Model.h>

namespace engine {

	using namespace graphics;

	void AssetLoader::loadEntity(const char * path) const
	{
		LuaScript script(path);

		Shader pbrShader("res/shader/material/pbr_material.glsl");

		EntityManager *entMgr = Engine::getEntityManager();
		ComponentManager *compMgr = Engine::getComponentManager();

		Entity *entity = entMgr->newEntity();
		entity->transform.position.x = script.get<float>("entity.position.x");
		entity->transform.position.y = script.get<float>("entity.position.y");
		entity->transform.position.z = script.get<float>("entity.position.z");

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

		/*FileUtils::load_obj("res/mesh/pig.obj", *mesh);
		*model = Loader::loadModel(*mesh);

		entity->mesh = mesh;
		entity->pbrmaterial = pbrmaterial;
		entity->model = model;*/

	}
}

