#pragma once

#include <vector>
#include "../math/Vec3.h"
#include "../math/vec2.h"
#include <common/types.h>

namespace engine {	namespace graphics {

	class Mesh {
		typedef std::vector<Vec3> vect3;
		typedef std::vector<Vec2> vect2;

	private:
		vect3 m_Vertices, m_Normals;
		vect2 m_UVs;
		

	public:
		U32 numVertices;
		Mesh(vect3 &vertices, vect3 &normals, vect2 &uvs);
		Mesh();

		~Mesh();

		std::vector<Vec3> & getVertices();
		vect3 & getNormals();
		vect2 & getUVs();
	};

}}