#pragma once


#include "../../entity/Entity.h"
#include <entity\Scene.h>
#include <graphics\api\Shader.h>
#include <graphics\api\Cubemap.h>

#include <entity\Light.h>


#include <common/types.h>

namespace engine {
	// forward declaration
	struct collision::AABB3D;
	
	namespace graphics {
		// forward declaration
		class Camera;

		class Renderer {
		private:
			Camera *m_Camera;
			Cubemap *m_Skybox;
			U32 vbo_aabb;


			void loadCollisionShapes();
		public:
			Renderer(Camera *camera);
			~Renderer();

			void initialize();
			void render(const Scene &scene, const Shader &shader, const Light &light) const;
			void render(const Cubemap &cubemap, const U32 vao, const Shader &shader) const;
			void render(const U32 vbo, const Shader &shader, const int dim, U32 size) const;
			void renderLINES(Entity &entity, const Shader &shader) const;
			void renderUI(Entity &entity, const Shader &shader) const;
			
			void renderRenderSkin(Entity &entity, const Shader &shader) const;
			void renderAABB(const collision::AABB3D &aabb, const Shader &shader) const;
			void renderAABBs(const collision::AABB3D *aabb, const U32 size, const Shader &shader) const;
			void renderTerrain(const U32 vbo, const Shader &shader, const int dim, U32 size) const;
			void renderReflection(Entity &entity) const;

			void setCamera(Camera *camera);
			void setSkybox(Cubemap *skybox) { m_Skybox = skybox; }
		};
	}
}