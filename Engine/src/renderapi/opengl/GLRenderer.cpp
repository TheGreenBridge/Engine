//------------------------------------------------------------------------------
// GLRenderer.cpp
//
// OPEN GL implementation of the renderer
//
// Author: Sommerauer Christian
// Created: xx.xx.xx
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\Renderer.h>
#include <graphics\api\Texture.h> 

#include <renderapi/opengl/GLCommon.h>
#include <collision\AABB.h>
#include <entity\Camera.h>

#include <graphics\pbr\PBRMaterial.h>
#include <EngineCore.h>

using namespace engine::graphics;
using namespace engine;

namespace engine {	namespace graphics {

	
	//--------------------------------------------------------------------------
	Renderer::Renderer() : 
		m_RenderQueue(Engine::gMemoryManager.allocate(sizeof(RenderItem) * 50).ptr, 50)
	{
		VS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(VS_Uniforms));
		VS_uniformBuffer->setBindingPoint(0);
		FS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(FS_Uniforms));
		FS_uniformBuffer->setBindingPoint(1);
	}

	//------------------------------------------------------------------------------
	Renderer::Renderer(Camera *camera) : 
		m_RenderQueue(Engine::gMemoryManager.allocate(sizeof(RenderItem) * 50).ptr, 50)
	{
		setCamera(camera);
		VS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(VS_Uniforms));
		VS_uniformBuffer->setBindingPoint(0);
		FS_uniformBuffer = Engine::gBufferManager.createUniformBuffer(sizeof(FS_Uniforms));
		FS_uniformBuffer->setBindingPoint(1);
	}

	//------------------------------------------------------------------------------
	Renderer::~Renderer() 
	{

	}

	//------------------------------------------------------------------------------
	void Renderer::loadCollisionShapes() 
	{

		Vec3 verts[8];
		verts[0] = Vec3(0, 0, 0);
		verts[1] = Vec3(1, 0, 0);
		verts[2] = Vec3(1, 0, 1);
		verts[3] = Vec3(0, 0, 1);

		verts[4] = Vec3(0, 1, 0);
		verts[5] = Vec3(1, 1, 0);
		verts[6] = Vec3(1, 1, 1);
		verts[7] = Vec3(0, 1, 1);

		GLCall(glGenBuffers(1, &vbo_aabb));

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb));
		GLCall(glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verts, GL_STATIC_DRAW));
		GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0));
		GLCall(glEnableVertexAttribArray(0));
	}

	//------------------------------------------------------------------------------
	void Renderer::initialize() 
	{
		loadCollisionShapes();
	}

	/*
	void Renderer::render(const Scene &scene, const Shader &shader, const Light &light) const {

		for each (Entity *entity in scene.getContainer())
		{
			if (entity->model == nullptr) continue;
			if (entity->mesh == nullptr) continue;
			if (entity->material == nullptr) continue;
			if (entity->material->shader == nullptr) continue;
			Shader &rShader = *entity->material->shader;
			rShader.enable();
			GLCall(glBindVertexArray(entity->model->vao));
			//glBindTexture(GL_TEXTURE_2D, entity->material->texture->getID());
			GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox->getTextureID()));
			
			// Entity
			rShader.setUniformMat4("trans_matrix", entity->getTransformation());
			// Camera
			rShader.setUniformMat4("proj_matrix", m_Camera->getProjectionMatrix());
			rShader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
			rShader.setUniform3f("camera_position", m_Camera->getPosition());
		
			// Light
			//rShader.setUniform3f("lightPosition", light.getPosition());
			//shader.setUniform3f("light.color", light.getColor());

			GLCall(glDrawArrays(GL_TRIANGLES, 0, entity->mesh->getVertices().size() * sizeof(Vec3)));
			rShader.disable();
		}
		GLCall(glBindVertexArray(0));
	}
	
	void Renderer::renderLINES(Entity &entity, const Shader &shader) const {
	shader.enable();
	GLCall(glBindVertexArray(entity.model->vao));
	shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
	shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
	shader.setUniformMat4("transformation_matrix", entity.getTransformation());
	GLCall(glDrawArrays(GL_LINES, 0, entity.mesh->getVertices().size() * sizeof(Vec3)));
	GLCall(glBindVertexArray(0));
	shader.disable();

	}

	

	float counter = 0;

	void Renderer::renderRenderSkin(Entity &entity, const Shader &shader) const {
		shader.enable();
		if (entity.animatable == nullptr) LOG_ERROR("IN RENDERER: IST NULLPTR");
		if (entity.animatable->m_pSkin == nullptr) LOG_ERROR("IN RENDERER: SKIN IST NULLPTR");
		GLCall(glBindVertexArray(entity.animatable->m_pSkin->vao));

		counter += 0.01f;
		if (counter >= 2.0) counter = 0;
		Vec3 color(counter, 1.0, 0.0);

		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("trans_matrix", entity.getTransformation());
		shader.setUniformMat4Array("joint_transforms", entity.animatable->m_pBones->elements);
		shader.setUniform3f("color", color);

		GLCall(glDrawArrays(GL_TRIANGLES, 0, entity.animatable->m_pSkin->numVerts));
		GLCall(glBindVertexArray(0));
		shader.disable();
	}


	void Renderer::renderUI(Entity &entity, const Shader &shader) const {
		shader.enable();
		GLCall(glBindVertexArray(entity.model->vao));
		//shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4Array("transformation_matrix", entity.getTransformation().elements);
		GLCall(glDrawArrays(GL_LINES, 0, entity.mesh->getVertices().size() * sizeof(Vec3)));
		GLCall(glBindVertexArray(0));
	}

	void Renderer::render(const U32 vbo, const Shader &shader, const int dim, U32 size) const {
		shader.enable();
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
		GLCall(glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, 0));
		shader.setUniformMat4("view_matrix", m_Camera->getRotationMatrix());
		//shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		GLCall(glDrawArrays(GL_LINES, 0, size * sizeof(float)));
	}

	void Renderer::render(Entity & entity, const Texture &texture, const Shader &shader) const
	{
		shader.enable();

		GLCall(glBindVertexArray(entity.model->vao));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3)));

		shader.setUniform3f("lightPosition", m_Lights[0].getPosition());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("transformation_matrix", entity.getTransformation());
		shader.setUniform3f("viewPos", m_Camera->getPosition());

		shader.setUniformTexture("modelTexture", 0, texture.getID());
		
		shader.disable();
	}

	void Renderer::render(Entity & entity, const Shader & shader) const
	{
		shader.enable();
		GLCall(glBindVertexArray(entity.model->vao));
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("proj_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("model_matrix", entity.getTransformation());

		GLCall(glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3)));
		shader.disable();
	}



	void Renderer::renderTerrain(const U32 vao, const Shader &shader, const int dim, U32 indicesSize) const {
		shader.enable();
		GLCall(glBindVertexArray(vao));
		//glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, 0);
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		
			
		GLCall(glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0));
		//glDrawArrays(GL_TRIANGLES, 0, size * sizeof(float));
		GLCall(glBindVertexArray(0));
	}

	void Renderer::renderReflection(Entity & entity) const
	{
		entity.material->shader->enable();
		GLCall(glBindVertexArray(entity.model->vao));
		

		entity.material->shader->setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		entity.material->shader->setUniformMat4("proj_matrix", m_Camera->getProjectionMatrix());
		entity.material->shader->setUniformMat4("trans_matrix", entity.getTransformation());
		
		entity.material->shader->setUniform3f("camera_position", m_Camera->getPosition());
		
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox->getTextureID()));
		GLCall(glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3)));
		GLCall(glBindVertexArray(0));
		entity.material->shader->disable();
		
	}
	
	void Renderer::renderAABB(const collision::AABB3D &aabb, const Shader &shader) const {
		//if (change) {
		//	change = false;
		//	Vec3 verts[8];
		//	verts[0] = aabb.min;		
		//	verts[1] = Vec3(aabb.max.x, aabb.min.y, aabb.min.z);
		//	verts[2] = Vec3(aabb.max.x, aabb.min.y, aabb.max.z);
		//	verts[3] = Vec3(aabb.min.x, aabb.min.y, aabb.max.z);
		//
		//	verts[4] = Vec3(aabb.min.x, aabb.max.y, aabb.min.z);
		//	verts[5] = Vec3(aabb.max.x, aabb.max.y, aabb.min.z);
		//	verts[6] = aabb.max;
		//	verts[7] = Vec3(aabb.min.x, aabb.max.y, aabb.max.z);
		//
		//	glGenBuffers(1, &vbo_aabb);
		//		
		//	glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb);
		//	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verts, GL_STATIC_DRAW);
		//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		//	glEnableVertexAttribArray(0);
		//}
			

		U16 indices[24] = {
			0, 1, 1, 2, 2, 3, 3, 0, 
			4, 5, 5, 6, 6, 7, 7, 4,
			4, 0, 5, 1, 6, 2, 7, 3
		};

		mat4 result(1.0f);
		Vec3 scale = aabb.max - aabb.min;
		result.elements[0] = scale.x;
		result.elements[5] = scale.y;
		result.elements[10] = scale.z;
		result.elements[12] = aabb.min.x;
		result.elements[13] = aabb.min.y;
		result.elements[14] = aabb.min.z;

		shader.enable();

		//glVertexPointer(3, GL_FLOAT, 0, verts);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb));
		GLCall(glVertexAttribPointer(3, GL_UNSIGNED_SHORT, false, 0, 0, 0));
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("transformation_matrix", result);

		GLCall(glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, indices));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		shader.disable();
	}

	void Renderer::renderAABBs(const collision::AABB3D *colliders, const U32 size, const Shader &shader) const {
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb));
		GLCall(glVertexAttribPointer(3, GL_UNSIGNED_SHORT, false, 0, 0, 0));
		shader.enable();
		for (U32 i = 0; i < size; i++) {
				
			mat4 result(1.0f);
			Vec3 scale = colliders[i].max - colliders[i].min;
			result.elements[0] = scale.x;
			result.elements[5] = scale.y;
			result.elements[10] = scale.z;
			result.elements[12] = colliders[i].min.x;
			result.elements[13] = colliders[i].min.y;
			result.elements[14] = colliders[i].min.z;

			unsigned short indices[24] = {
				0, 1, 1, 2, 2, 3, 3, 0,
				4, 5, 5, 6, 6, 7, 7, 4,
				4, 0, 5, 1, 6, 2, 7, 3
			};
				
			shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
			shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
			shader.setUniformMat4("transformation_matrix", result);

			GLCall(glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, indices));
		}
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		shader.disable();
	}
	
	
	
	

	*/

	//void Renderer::renderPBR(Entity &entity) const
	//{
	//	const PBRMaterial &material = *entity.pbrmaterial;
	//	const Shader &shader = material.getShader();

	//	shader.enable();

	//	GLCall(glBindVertexArray(entity.model->vao));

	//	shader.setUniformMat4("projection", m_Camera->getProjectionMatrix());
	//	shader.setUniformMat4("view", m_Camera->getViewMatrix());
	//	shader.setUniformMat4("model", entity.getTransformation());

	//	//shader.setUniform1f("roughness", material.roughness);
	//	//shader.setUniform1f("metallic", material.metallic);
	//	//shader.setUniform3f("albedo", material.albedo);

	//	shader.setUniform1f("ao", 1.0f);
	//	shader.setUniform3f("light", m_Lights[0].getPosition());

	//	shader.setUniformTexture("albedoMap", 0, material.getAlbedo());
	//	shader.setUniformTexture("metallicMap", 1, material.getMetallic());
	//	shader.setUniformTexture("roughnessMap", 2, material.getRoughness());

	//	shader.setUniform3f("camPos", m_Camera->getPosition());

	//	GLCall(glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3)));
	//	
	//	GLCall(glBindVertexArray(0));
	//	shader.disable();
	//}

	//

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
		const Vec3& modelPosition = renderable.transform->position;
		const Vec3& cameraPosition = m_Camera->getPosition();

		item.distance = Vec3::distance(cameraPosition, modelPosition);
		item.renderable = &renderable;

		m_RenderQueue.pushItem(item);
	}

	//------------------------------------------------------------------------------
	void Renderer::sortRenderQueue()
	{
		// Priority:

		// 1 Shader
		// 2 Texture
		// 3 Depth
	}

	//------------------------------------------------------------------------------
	void Renderer::render()
	{
		//VS_Uniforms vs_uniforms;
		//FS_Uniforms fs_uniforms;

		//fs_uniforms.viewPos = m_Camera->getPosition();

		//vs_uniforms.projection = m_Camera->getProjectionMatrix();
		//vs_uniforms.view = m_Camera->getViewMatrix();

		//VS_uniformBuffer->setData(&vs_uniforms, sizeof(mat4) * 2, 0);
		//FS_uniformBuffer->setData(&fs_uniforms.viewPos, sizeof(Vec3), 0);
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		const RenderItem* renderItem;
		while (renderItem = m_RenderQueue.next())
		{
			const Renderable3D& renderable = *renderItem->renderable;

			//vs_uniforms.model = mat4::TransformToMat4(*renderable.transform);
			//VS_uniformBuffer->setData(&vs_uniforms.model, sizeof(mat4), sizeof(mat4) * 2);
			
			renderable.model->vertices->bind();
			renderable.material->shader->enable();

			renderable.material->shader->setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
			renderable.material->shader->setUniformMat4("view_matrix", m_Camera->getViewMatrix());

			renderable.material->shader->setUniformMat4("transformation_matrix", mat4::TransformToMat4(*renderable.transform));
			renderable.material->shader->setUniform3f("viewPos", m_Camera->getPosition());

			//fs_uniforms.texture = renderable.material->texture->getID();
			//FS_uniformBuffer->setData(&fs_uniforms.texture, sizeof(U32), 0);
			//renderable.material->shader->setUniformTexture("modelTexture", 0, renderable.material->texture->getID());

			//renderable.material->texture->bind();

			//renderable->material->uniforms->bind();

			renderable.model->vertices->draw(renderable.model->numVertices);
		}
		GLCall(glUseProgram(0));
		GLCall(glBindVertexArray(0));
	}
}}