#pragma once

#include <graphics\Model.h>
#include <graphics\Mesh.h>
#include <common\types.h>

class Loader {
private:
public:
	// To prevent any object construction -> delete all standard constructors
	//Loader() = delete;
	//Loader(const Loader&) = delete;
	//Loader(Loader&&) = delete;

	static Model loadModel(engine::graphics::Mesh &mesh);
	static U32 loadBuffer(engine::graphics::Mesh &mesh, const U32 dimensions, const U32 attribute);
	static U32 loadBufferf(const float * const mesh, const U32 size, const U32 dimensions, const U32 attribute);
	static void testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals,
		const float *uvs, const int *joints, const float *weights, const unsigned int vertSize);
	static U32 loadIndexedBufferf(const float * const mesh, const U32 size, const U32 *indices, const U32 indicesSize);
	static U32 loadVAO(U32 &vbo, const float *mesh, const U32 size, const U32 dimensions, const U32 attribute);
};