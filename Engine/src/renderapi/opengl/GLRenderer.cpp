//------------------------------------------------------------------------------
// GLRenderer.cpp
//
// OPEN GL implementation of the renderer
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 16.08.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Renderer.h>
#include <graphics\api\Texture.h> 

#include <renderapi/opengl/GLCommon.h>
#include <entity\Camera.h>

#include <entity\component\Transform.h>
#include <entity\Terrain.h>
#include <Components\Renderable3D.h>

#include <EngineCore.h>

#include <EngineCore.h>
#include <cmath>
#include <algorithm>


using namespace engine::graphics;
using namespace engine::component;
using namespace engine::entity;
using namespace engine;

namespace engine {	namespace graphics {

	
	//--------------------------------------------------------------------------
	Renderer::Renderer() : 
		m_RenderQueue(Engine::gMemoryManager.allocate(sizeof(RenderItem) * 50).ptr, 50)
	{
		// SHADER
		m_fontShader = Engine::gShaderManager.createShader("res/shader/ui/text.glsl");


		// STANDARD UNIFORM BUFFER
		VS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(VS_Uniforms));
		VS_uniformBuffer->setBindingPoint(0);
		FS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(FS_Uniforms));
		FS_uniformBuffer->setBindingPoint(1);

		// INIT
		clearCache();
		font.init();
	}

	//------------------------------------------------------------------------------
	Renderer::~Renderer() 
	{

	}

	////------------------------------------------------------------------------------
	//void Renderer::loadCollisionShapes() 
	//{

	//	Vec3 verts[8];
	//	verts[0] = Vec3(0, 0, 0);
	//	verts[1] = Vec3(1, 0, 0);
	//	verts[2] = Vec3(1, 0, 1);
	//	verts[3] = Vec3(0, 0, 1);

	//	verts[4] = Vec3(0, 1, 0);
	//	verts[5] = Vec3(1, 1, 0);
	//	verts[6] = Vec3(1, 1, 1);
	//	verts[7] = Vec3(0, 1, 1);

	//	GLCall(glGenBuffers(1, &vbo_aabb));

	//	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb));
	//	GLCall(glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verts, GL_STATIC_DRAW));
	//	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
	//	GLCall(glEnableVertexAttribArray(0));
	//}

	//------------------------------------------------------------------------------
	void Renderer::initialize() 
	{
		//loadCollisionShapes();
	}

	

	//------------------------------------------------------------------------------
	void Renderer::render(const Cubemap &cubemap, const VertexArray& vao, const Shader &shader) const
	{
		GLCall(glDepthMask(GL_FALSE));
		shader.enable();

		vao.bind();
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.getTextureID()));
		shader.setUniformMat4("projection", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view", m_Camera->getRotationMatrix());

		GLCall(glDrawArrays(GL_TRIANGLES, 0, 36));
		vao.unbind();
		GLCall(glDepthMask(GL_TRUE));
	}
		
	//------------------------------------------------------------------------------
	void Renderer::setCamera(Camera *camera) {
		m_Camera = camera;
	}

	//------------------------------------------------------------------------------
	void Renderer::setLight(U32 slot, const Light &light)
	{
		if (slot >= MAX_LIGHTS && slot < 0)	{
			LOG_ERROR("Renderer::setLight invalid slot!");
			return;
		}
		m_Lights[slot] = light;				
	}

	//------------------------------------------------------------------------------
	Light &Renderer::getLight(U32 slot) 
	{	
		if (slot >= MAX_LIGHTS && slot < 0)	{
			LOG_ERROR("Renderer::getLight invalid slot!");
			return m_Lights[0];
		}
		return m_Lights[slot];	
	}

	//------------------------------------------------------------------------------
	void Renderer::combineTextures(const U32 vao, 
		const Texture &tex1, const Texture &tex2, const Shader &shader)
	{
		shader.enable();

		shader.setUniformTexture("baseMap", 0, tex1.getID());
		shader.setUniformTexture("overlayMap", 1, tex2.getID());
		//glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3));
		shader.disable();
	}

	//------------------------------------------------------------------------------
	void Renderer::submit(const Renderable3D& renderable)
	{
		RenderItem item;
		U64 key = 0;
		const Vec3& modelPosition = renderable.transform->position;
		const Vec3& cameraPosition = m_Camera->getPosition();

		item.distance = Vec3::distance(cameraPosition, modelPosition);
		item.renderable = &renderable;


		Frustum frustum = m_Camera->getFrustum();
		
		/*
		-------------------------
		|	Material ID	| Depth	|
		-------------------------
		|		40		|	24	|
		-------------------------
		64 Bit Key
		*/
		// Priority:

		// 1 Shader
		// 2 Texture
		// 3 Depth

		
		F32 procent = item.distance / frustum.m_Far;
		if (procent > 1.0f)
		{
			procent = 1.0f;
		}

		U64 depth = static_cast<U64>(procent * static_cast<F32>(Bit(24) - 1));
		U64 material = 1;

		key |= (depth << 0);
		key |= (material << 24);

		m_RenderQueue.pushItem(item);
		m_sort.push_back({ key, m_RenderQueue.getLastItem() });
		
	}

	//------------------------------------------------------------------------------
	void Renderer::sortRenderQueue()
	{
		std::sort(m_sort.begin(), m_sort.end(),	
			[](const SortKey& a, const SortKey& b) 
		{
			return a.key > b.key;
		});
	}

	//------------------------------------------------------------------------------
	void Renderer::loadRenderQueue()
	{
		PoolAllocator<Renderable3D>* pool = 
			Engine::getComponentManager()->getContainer<Renderable3D>();
		
		for (PoolIterator<Renderable3D> it = pool->begin(); it != pool->end(); ++it)
		{
			if (!it.m_item->allocated) continue;
			Vec3 &position = (*it).transform->position;
			EPlacement placement = m_Camera->sphereInFrustum(position, 1.0f);
			if (placement == EPlacement::INSIDE || placement == EPlacement::INTERSECT)
			{
				submit(*it);
			}
			
		}

		/*if (m_Camera->sphereInFrustum(Vec3(0, 0, 0), 1.0f) == EPlacement::INSIDE)
		{
			renderGUIText("Sphere 0,0,0 rad 1.0 inside", 25,25, 0.4f, Color::Red);
		}
		else
		{
			renderGUIText("sphere not inside", 25, 25, 0.4f, Color::Red);
		}*/


		if (m_Camera->pointInFrustum(Vec3(0, 0, 0)) == EPlacement::INSIDE )
		{
			renderGUIText("Point 0,0,0 inside", 25, 50, 0.4f, Color::Green);
		}
		else
		{
			renderGUIText("point not inside", 25, 50, 0.4f, Color::Red);
		}

		std::string camera_pos = "Camera Pos X " + std::to_string(m_Camera->getPosition().x) +
			" Y " + std::to_string(m_Camera->getPosition().y) +
			" Z " + std::to_string(m_Camera->getPosition().z);
		renderGUIText(camera_pos.c_str(), 25, 75, 0.4f, Color::Red);
	}

	F32 counter = 0;
	//------------------------------------------------------------------------------
	void Renderer::prepare()
	{
		counter += 1.0f;
		F32 x = 10.0f*cos(counter*PI / 180.0f);
		F32 z = 10.0f*sin(counter*PI / 180.0f);

		VS_Uniforms vs_uniforms;
		vs_uniforms.camera = m_Camera->getProjectionMatrix() * m_Camera->getViewMatrix();
		vs_uniforms.lightPosition = Vec3(x, 0, z);

		VS_uniformBuffer->setData(&vs_uniforms, sizeof(VS_Uniforms), 0);
		
		FS_Uniforms fs_uniforms;
		fs_uniforms.viewPos = m_Camera->getPosition();
		FS_uniformBuffer->setData(&fs_uniforms.viewPos, sizeof(Vec3), 0);
	}

	//------------------------------------------------------------------------------
	void Renderer::render()
	{
		loadRenderQueue();
		sortRenderQueue();
		prepare();
		const RenderItem* renderItem;

		for(auto it = m_sort.begin(); it != m_sort.end() ;++it)
		{
			const Renderable3D& renderable = *it->renderItem->renderable;
			vs_uniforms.model = mat4::TransformToMat4(*renderable.transform);
			VS_uniformBuffer->setData(&vs_uniforms.model, sizeof(mat4), sizeof(mat4) * 1);

			// Cached rendercall
			if (m_cache.vertexArray != renderable.model->vertices)
			{
				renderable.model->vertices->bind();
				m_cache.vertexArray = renderable.model->vertices;
			}
			if (m_cache.shader != renderable.material->shader)
			{
				renderable.material->shader->enable();
				m_cache.shader = renderable.material->shader;
			}
			if (m_cache.texture != renderable.material->texture)
			{
				renderable.material->texture->bind();
				m_cache.texture = renderable.material->texture;
			}

			m_cache.vertexArray->draw(renderable.model->numVertices);
		}


		renderGUI();


		clearCache();
		clearRenderQueue();
	}

	//------------------------------------------------------------------------------
	void Renderer::renderGUI()
	{
		U32 x = 1100, y = 700;
		renderGUIText("RenderQueue", x, y, 0.4f, Color::Green);
		U32 renderItemCounter = 0;
		for (auto it = m_sort.begin(); it != m_sort.end(); ++it)
		{
			y -= 20;
			renderItemCounter++;
			renderGUIText(std::to_string(it->key).c_str(), x, y, 0.4f, Color::Green);
		}

		//U32 entities = Engine::getEntityManager()->getEntityCount();
		std::string text = "Entities: " +std::to_string( renderItemCounter );
		renderGUIText(text.c_str(), x, y-20, 0.4f, Color::Red);
	}

	//------------------------------------------------------------------------------
	void Renderer::renderGUIText(const char* text, const F32& x, const F32& y, const F32& size, const Vec3& color)
	{
		font.renderText(*m_fontShader, *m_Camera, text, x, y, size, color);
	}

	//------------------------------------------------------------------------------
	void Renderer::renderTerrain(entity::Terrain& terrain)
	{
		vs_uniforms.model = mat4::TransformToMat4(terrain.transform);
		VS_uniformBuffer->setData(&vs_uniforms.model, sizeof(mat4), sizeof(mat4) * 1);
		terrain.draw();
	}

	//------------------------------------------------------------------------------
	void Renderer::clearCache()
	{
		memset(&m_cache, 0, sizeof(m_cache));
	}

	//------------------------------------------------------------------------------
	void Renderer::clearRenderQueue()
	{
		m_RenderQueue.reset();
		m_sort.clear();
	}

}}