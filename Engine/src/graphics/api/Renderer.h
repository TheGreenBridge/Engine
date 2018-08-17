//------------------------------------------------------------------------------
// File Name: Renderer.h
// Description: To render graphics
//
// Author: Sommerauer Christian
// Created: 05.02.2017
// Changed: 16.08.2018
//------------------------------------------------------------------------------
//

#pragma once

#include <common/types.h>
#include <entity\Light.h>
#include <graphics\RenderQueue.h>
#include <graphics\Font.h>
#include <graphics\Color.h>
#include <map>

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
		class Terrain;
		class Cubemap;
		class Shader;
	}
	namespace component {
		class Renderable3D;
	}
	namespace entity {
		class Terrain;
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
		Shader* shader;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
		Texture* texture;
		U32 enableFlags;
	};

	struct VS_Uniforms
	{
		mat4 camera;
		mat4 model;
		Vec3 lightPosition;
	};

	struct FS_Uniforms
	{
		Vec3 viewPos;
	};

	struct SortKey
	{
		U64 key;
		RenderItem* renderItem;
	};

	class Renderer {
	private:
		Camera *m_Camera;
		Cubemap *m_Skybox;
		Terrain *m_Terrain;

		Shader* m_fontShader;

		Light m_Lights[MAX_LIGHTS];

		UniformBuffer* VS_uniformBuffer;
		UniformBuffer* FS_uniformBuffer;

		VS_Uniforms vs_uniforms;
		FS_Uniforms fs_uniforms;
		Font font;

		RenderQueue m_RenderQueue;
		std::vector<SortKey> m_sort;

		StateCache m_cache;

		//void loadCollisionShapes();
		void prepare();
		void clearCache();
		void clearRenderQueue();

	public:
		Renderer();

		Renderer(const Renderer&) = delete;

		~Renderer();

		void initialize();
		void render(const Cubemap &cubemap, const VertexArray& vao, const Shader &shader) const;

		void setCamera(Camera *camera);
		void setSkybox(Cubemap *skybox) { m_Skybox = skybox; }

		void setLight(U32 slot, const Light &light);
		Light &getLight(U32 slot) ;

		void combineTextures(const U32 vao, const Texture &tex1, const Texture &tex2, const Shader &shader);
		
		
		// NEW

		void submit(const Renderable3D& renderable);
		void sortRenderQueue();
		void loadRenderQueue();
		void render();
		void renderGUI();
		void renderGUIText(const char*, const F32& x, const F32& y, 
			const F32& size, const Vec3& color);

		void renderTerrain(entity::Terrain& terrain);
	};
}}