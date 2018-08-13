//------------------------------------------------------------------------------
// File Name: Renderer.h
// Description: To render graphics
//
// Author: Sommerauer Christian
// Created: 05.02.2017
// Changed: 13.08.2018
//------------------------------------------------------------------------------
//

#pragma once

#include <entity/Entity.h>
#include <entity\Scene.h>
#include <entity\Light.h>


#include <graphics\api\Shader.h>
#include <graphics\api\Cubemap.h>
#include <graphics\api\VertexArray.h>


#include <graphics\pbr\PBRMaterial.h>

#include <Components\Renderable3D.h>
#include <graphics\RenderQueue.h>

#include <common/types.h>

#define MAX_LIGHTS 4

#define Bit(x) 1<<x

using namespace engine::component;

// Forward Declarations
/////////////////////////////////////////////////////////
namespace engine { 
	namespace collision {
		struct AABB3D;
	}
	namespace graphics {
		class Camera;
	}
}
/////////////////////////////////////////////////////////


namespace engine { namespace graphics {

	enum EGEnable
	{
		DEPTH_TEST			= Bit(0),
		BLEND				= Bit(1),
		BACK_FACE_CULLING	= Bit(2),
	};

	struct StateCache
	{
		U32 shader;
		U32 vertexArray;
		U32 vertexBuffer;
		U32 texture;
		U32 enableFlags;
	};

	struct VS_Uniforms
	{
		mat4 projection;
		mat4 view;
		mat4 model;
	};

	struct FS_Uniforms
	{
		Vec3 viewPos;
	};

	class Renderer {
	private:
		Camera *m_Camera;
		Cubemap *m_Skybox;
		U32 vbo_aabb;
		Light m_Lights[MAX_LIGHTS];

		UniformBuffer* VS_uniformBuffer;
		UniformBuffer* FS_uniformBuffer;

		RenderQueue m_RenderQueue;
		StateCache m_cache;

		void loadCollisionShapes();

	public:
		Renderer();
		Renderer(Camera *camera);

		Renderer(const Renderer&) = delete;

		~Renderer();

		void initialize();
		void render(const Cubemap &cubemap, const VertexArray& vao, const Shader &shader) const;
			
		/*void render(const Scene &scene, const Shader &shader, const Light &light) const;
		void render(const U32 vbo, const Shader &shader, const int dim, U32 size) const;
			
		void render(Entity &entity, const Texture &texture, const Shader &shader) const;

		void render(Entity &entity, const Shader &shader) const;
			
		void renderLINES(Entity &entity, const Shader &shader) const;
		void renderUI(Entity &entity, const Shader &shader) const;
			
		void renderRenderSkin(Entity &entity, const Shader &shader) const;
		void renderAABB(const collision::AABB3D &aabb, const Shader &shader) const;
		void renderAABBs(const collision::AABB3D *aabb, const U32 size, const Shader &shader) const;
		void renderTerrain(const U32 vbo, const Shader &shader, const int dim, U32 size) const;
		void renderReflection(Entity &entity) const;
		
		//void renderPBR(Entity &entity) const;*/

		void setCamera(Camera *camera);
		void setSkybox(Cubemap *skybox) { m_Skybox = skybox; }

		void setLight(U32 slot, const Light &light);
		Light &getLight(U32 slot) ;

		void combineTextures(const U32 vao, const Texture &tex1, const Texture &tex2, const Shader &shader);
		
		
		// NEW

		void submit(const Renderable3D& renderable);
		void sortRenderQueue();
		void render();
	};
}}