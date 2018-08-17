#include <graphics\api\Loader.h>
#include <renderapi\opengl\GLCommon.h>

#define VBO_SLOTS	5

#define VBO_VERTEX	0
#define VBO_NORMAL	1
#define VBO_UV		2
#define VBO_JOINT	3
#define VBO_WEIGHT	4

#define ATT_VERTEX	0
#define ATT_NORMAL	1
#define ATT_UV		2
#define ATT_JOINT	3
#define ATT_WEIGHT	4

#define LAYOUT_ATTR_POSITION	0
#define LAYOUT_ATTR_NORMAL		1
#define LAYOUT_ATTR_UV			2



//engine::graphics::Model Loader::loadModel(engine::graphics::Mesh &mesh) {
//	Model model;
//
//	//GLCall(glGenVertexArrays(1, &model.vao));
//	//GLCall(glBindVertexArray(model.vao));
//	//// Vertices
//	//GLCall(glGenBuffers(3, &model.vbo_vertices));
//	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.vbo_vertices));
//	//GLCall(glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(Vec3), &mesh.getVertices()[0], GL_STATIC_DRAW));
//	//GLCall(glVertexAttribPointer(LAYOUT_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0));
//	//GLCall(glEnableVertexAttribArray(LAYOUT_ATTR_POSITION));
//	//// Normals
//	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.vbo_normals));
//	//GLCall(glBufferData(GL_ARRAY_BUFFER, mesh.getNormals().size() * sizeof(Vec3), &mesh.getNormals()[0], GL_STATIC_DRAW));
//	//GLCall(glVertexAttribPointer(LAYOUT_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0));
//	//GLCall(glEnableVertexAttribArray(LAYOUT_ATTR_NORMAL));
//	////UV Coordinates
//	//GLCall(glBindBuffer(GL_ARRAY_BUFFER, model.vbo_uvs));
//	//GLCall(glBufferData(GL_ARRAY_BUFFER, mesh.getUVs().size() * sizeof(Vec2), &mesh.getUVs()[0], GL_STATIC_DRAW));
//	//GLCall(glVertexAttribPointer(LAYOUT_ATTR_UV, 2, GL_FLOAT, GL_FALSE, 0, 0));
//	//GLCall(glEnableVertexAttribArray(LAYOUT_ATTR_UV));
//
//	//GLCall(glBindVertexArray(0));
//	return model;
//}

void Loader::testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals, const float *uvs, const int *joints, const float *weights,
	const unsigned int vertSize) {

	GLCall(glGenVertexArrays(1, vao));
	GLCall(glBindVertexArray(*vao));
	GLCall(glGenBuffers(5, vbo));
	//VERTICES
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_VERTEX]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 3, vertices, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(ATT_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(ATT_VERTEX));
	//NORMALS
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_NORMAL]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 3, normals, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(ATT_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(ATT_NORMAL));
	//UVS
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_UV]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 2, uvs, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(ATT_UV, 2, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(ATT_UV));
	//BONES
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_JOINT]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(int) * 4, joints, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(ATT_JOINT, 4, GL_INT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(ATT_JOINT));
	//BONE WEIGTHS
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_WEIGHT]));
	GLCall(glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 4, weights, GL_STATIC_DRAW));
	GLCall(glVertexAttribPointer(ATT_WEIGHT, 4, GL_FLOAT, GL_FALSE, 0, 0));
	GLCall(glEnableVertexAttribArray(ATT_WEIGHT));

	GLCall(glBindVertexArray(0));
}