

#pragma once

#include <graphics\Model.h>
#include <graphics\Mesh.h>
#include <common\types.h>

using namespace engine::graphics;

class Loader {
private:
public:
	// To prevent any object construction -> delete all standard constructors
	//Loader() = delete;
	//Loader(const Loader&) = delete;
	//Loader(Loader&&) = delete;

	static Model loadModel(Mesh &mesh);
	static void testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals,
		const float *uvs, const int *joints, const float *weights, const unsigned int vertSize);
};