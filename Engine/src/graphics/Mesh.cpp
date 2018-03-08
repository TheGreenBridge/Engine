#include "Mesh.h"

#include "../math/Vec3.h"
#include <graphics/api/Texture.h>

typedef std::vector<Vec3> vect3;
typedef std::vector<vec2> vect2;

namespace engine {	namespace graphics {

	Mesh::Mesh(vect3 &vertices, vect3 &normals, vect2 &uvs)
		: m_Vertices(vertices), m_Normals(normals), m_UVs(uvs)
	{}

	Mesh::Mesh(){}

	Mesh::~Mesh() {

	}

	std::vector<Vec3> & Mesh::getVertices() {
		return m_Vertices;
	}

	vect2 & Mesh::getUVs() {
		return m_UVs;
	}

	vect3 & Mesh::getNormals() {
		return m_Normals;
	}

}}