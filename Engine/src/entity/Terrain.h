#pragma once

#include <common\types.h>
#include <math/Vec3.h>

#include <graphics/Model.h>
#include <entity\component\Transform.h>

namespace engine {
	namespace graphics {
		class IndexBuffer;
		class Shader;
	}
}


#define TILE_SIZE 50
#define VERTICES_PER_SIDE 128
#define VERTICES_COUNT VERTICES_PER_SIDE*VERTICES_PER_SIDE

namespace engine {namespace entity {
	
	using namespace engine::graphics;
	class Terrain {
		
	private:

		Model m_Model;
		IndexBuffer* index;
		Shader* shader;
		U32 numIndices;

		F32* vertices;
		F32* normals;
		U32* indices;

	public:
		explicit Terrain();
		Transform transform;
		~Terrain();
		void loadTerrain();
		U32 getNumIndices();

		void init();
		void update();
		void draw() const;
		Model &getModel();
	};
}}