#include <graphics\api\Renderer.h>
#include <graphics\api\Texture.h> 

#include <renderapi/opengl/GLCommon.h>
#include <collision\AABB.h>
#include <entity\Camera.h>


using namespace engine::graphics;
using namespace engine;

namespace engine {	namespace graphics {

	Renderer::Renderer(Camera *camera) {
		setCamera(camera);
	}

	Renderer::~Renderer() {

	}

	void Renderer::loadCollisionShapes() {

		Vec3 verts[8];
		verts[0] = Vec3(0, 0, 0);
		verts[1] = Vec3(1, 0, 0);
		verts[2] = Vec3(1, 0, 1);
		verts[3] = Vec3(0, 0, 1);

		verts[4] = Vec3(0, 1, 0);
		verts[5] = Vec3(1, 1, 0);
		verts[6] = Vec3(1, 1, 1);
		verts[7] = Vec3(0, 1, 1);

		glGenBuffers(1, &vbo_aabb);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb);
		glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verts, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}

	void Renderer::initialize() {
		loadCollisionShapes();
	}

	void Renderer::render(const Scene &scene, const Shader &shader, const Light &light) const {
		
		
		
			
		for each (Entity *entity in scene.getContainer())
		{
			if (entity->model == nullptr) continue;
			if (entity->mesh == nullptr) continue;
			if (entity->material == nullptr) continue;
			if (entity->material->shader == nullptr) continue;
			Shader &rShader = *entity->material->shader;
			rShader.enable();
			glBindVertexArray(entity->model->vao);
			/*glBindTexture(GL_TEXTURE_2D, entity->material->texture->getID());*/
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox->getTextureID());
			
			// Entity
			rShader.setUniformMat4("trans_matrix", entity->getTransformation());
			// Camera
			rShader.setUniformMat4("proj_matrix", m_Camera->getProjectionMatrix());
			rShader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
			rShader.setUniform3f("camera_position", m_Camera->getPosition());
		
			// Light
			//rShader.setUniform3f("lightPosition", light.getPosition());
			//shader.setUniform3f("light.color", light.getColor());

			glDrawArrays(GL_TRIANGLES, 0, entity->mesh->getVertices().size() * sizeof(Vec3));
			rShader.disable();
		}
		glBindVertexArray(0);
	}

	void Renderer::render(const Cubemap &cubemap, const U32 vao, const Shader &shader) const {
		glDepthMask(GL_FALSE);
		shader.enable();
		glBindVertexArray(vao);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.getTextureID());
		shader.setUniformMat4("projection", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view", m_Camera->getRotationMatrix());
	
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthMask(GL_TRUE);
	}

	void Renderer::renderLINES(Entity &entity, const Shader &shader) const {
		shader.enable();
		glBindVertexArray(entity.model->vao);
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("transformation_matrix", entity.getTransformation());
		glDrawArrays(GL_LINES, 0, entity.mesh->getVertices().size() * sizeof(Vec3));
		glBindVertexArray(0);
	}

	void Renderer::renderRenderSkin(Entity &entity, const Shader &shader) const {
		shader.enable();
		if (entity.animatable == nullptr) LOG("IN RENDERER: IST NULLPTR");
		if (entity.animatable->m_pSkin == nullptr) LOG("IN RENDERER: SKIN IST NULLPTR");
		glBindVertexArray(entity.animatable->m_pSkin->vao);
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("trans_matrix", entity.getTransformation());
		shader.setUniformMat4Array("joint_transforms", entity.animatable->m_pBones->elements);

		glDrawArrays(GL_TRIANGLES, 0, entity.animatable->m_pSkin->numVerts);
		glBindVertexArray(0);
	}

	void Renderer::renderUI(Entity &entity, const Shader &shader) const {
		shader.enable();
		glBindVertexArray(entity.model->vao);
		//shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("transformation_matrix", entity.getTransformation());
		glDrawArrays(GL_LINES, 0, entity.mesh->getVertices().size() * sizeof(Vec3));
		glBindVertexArray(0);
	}

	void Renderer::render(const U32 vbo, const Shader &shader, const int dim, U32 size) const {
		shader.enable();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, 0);
		shader.setUniformMat4("view_matrix", m_Camera->getRotationMatrix());
		//shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		glDrawArrays(GL_LINES, 0, size * sizeof(float));
	}

	void Renderer::renderTerrain(const U32 vao, const Shader &shader, const int dim, U32 indicesSize) const {
		shader.enable();
		glBindVertexArray(vao);
		//glVertexAttribPointer(0, dim, GL_FLOAT, GL_FALSE, 0, 0);
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
			
		glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
		//glDrawArrays(GL_TRIANGLES, 0, size * sizeof(float));
		glBindVertexArray(0);
	}

	void Renderer::renderReflection(Entity & entity) const
	{
		entity.material->shader->enable();
		glBindVertexArray(entity.model->vao);
		

		entity.material->shader->setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		entity.material->shader->setUniformMat4("proj_matrix", m_Camera->getProjectionMatrix());
		entity.material->shader->setUniformMat4("trans_matrix", entity.getTransformation());
		
		entity.material->shader->setUniform3f("camera_position", m_Camera->getPosition());
		
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox->getTextureID());
		glDrawArrays(GL_TRIANGLES, 0, entity.mesh->numVertices * sizeof(Vec3));
		glBindVertexArray(0);
		entity.material->shader->disable();
	}

	//bool change = true;
		
		
		
		
	void Renderer::renderAABB(const collision::AABB3D &aabb, const Shader &shader) const {
		/*if (change) {
			change = false;
			Vec3 verts[8];
			verts[0] = aabb.min;		
			verts[1] = Vec3(aabb.max.x, aabb.min.y, aabb.min.z);
			verts[2] = Vec3(aabb.max.x, aabb.min.y, aabb.max.z);
			verts[3] = Vec3(aabb.min.x, aabb.min.y, aabb.max.z);

			verts[4] = Vec3(aabb.min.x, aabb.max.y, aabb.min.z);
			verts[5] = Vec3(aabb.max.x, aabb.max.y, aabb.min.z);
			verts[6] = aabb.max;
			verts[7] = Vec3(aabb.min.x, aabb.max.y, aabb.max.z);

			glGenBuffers(1, &vbo_aabb);
				
			glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb);
			glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), verts, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		}*/
			

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
		glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb);
		glVertexAttribPointer(3, GL_UNSIGNED_SHORT, false, 0, 0, 0);
		shader.setUniformMat4("view_matrix", m_Camera->getViewMatrix());
		shader.setUniformMat4("pr_matrix", m_Camera->getProjectionMatrix());
		shader.setUniformMat4("transformation_matrix", result);

		glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, indices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shader.disable();
	}

	void Renderer::renderAABBs(const collision::AABB3D *colliders, const U32 size, const Shader &shader) const {
		glBindBuffer(GL_ARRAY_BUFFER, vbo_aabb);
		glVertexAttribPointer(3, GL_UNSIGNED_SHORT, false, 0, 0, 0);
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

			glDrawElements(GL_LINES, 24, GL_UNSIGNED_SHORT, indices);			
		}
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		shader.disable();
	}

	void Renderer::setCamera(Camera *camera) {
		m_Camera = camera;
	}

}}