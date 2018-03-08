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


Model Loader::loadModel(engine::graphics::Mesh &mesh) {
	Model model;

	glGenVertexArrays(1, &model.vao);
	glBindVertexArray(model.vao);
	// Vertices
	glGenBuffers(3, &model.vertices);
	glBindBuffer(GL_ARRAY_BUFFER, model.vertices);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(Vec3), &mesh.getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	// Normals
	glBindBuffer(GL_ARRAY_BUFFER, model.normals);
	glBufferData(GL_ARRAY_BUFFER, mesh.getNormals().size() * sizeof(Vec3), &mesh.getNormals()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);
	//UV Coordinates
	glBindBuffer(GL_ARRAY_BUFFER, model.uvs);
	glBufferData(GL_ARRAY_BUFFER, mesh.getUVs().size() * sizeof(vec2), &mesh.getUVs()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	return model;
}

U32 Loader::loadBuffer(engine::graphics::Mesh &mesh, const U32 dimensions, const U32 attribute) {
	U32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, mesh.getVertices().size() * sizeof(Vec3), &mesh.getVertices()[0], GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute);
	return vbo;
}

U32 Loader::loadBufferf(const float * const mesh, const U32 size, const U32 dimensions, const U32 attribute) {
	U32 vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), mesh, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute);

	return vbo;
}

U32 Loader::loadIndexedBufferf(const float * const mesh, const U32 size, const U32 *indices, const U32 indicesSize) {
	// For indexed Buffer the enum must be GL_ELEMENT_ARRAY_BUFFER
	U32 vao, vbo[2];
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glGenBuffers(2, vbo);


	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), mesh, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);


	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize * sizeof(int), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);
	return vao;
}

U32 Loader::loadVAO(U32 &vbo, const float *mesh, const U32 size, const U32 dimensions, const U32 attribute) {
	U32 vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size, mesh, GL_STATIC_DRAW);
	glVertexAttribPointer(attribute, dimensions, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(attribute);
	glBindVertexArray(0);
	return vao;
}

void Loader::testloadSkinnedMesh(unsigned int *vao, unsigned int *vbo, const float *vertices, const float *normals, const float *uvs, const int *joints, const float *weights,
	const unsigned int vertSize) {

	glGenVertexArrays(1, vao);
	glBindVertexArray(*vao);
	glGenBuffers(5, vbo);
	//VERTICES
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 3, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(ATT_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATT_VERTEX);
	//NORMALS
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_NORMAL]);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 3, normals, GL_STATIC_DRAW);
	glVertexAttribPointer(ATT_NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATT_NORMAL);
	//UVS
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_UV]);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 2, uvs, GL_STATIC_DRAW);
	glVertexAttribPointer(ATT_UV, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATT_UV);
	//BONES
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_JOINT]);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(int) * 4, joints, GL_STATIC_DRAW);
	glVertexAttribPointer(ATT_JOINT, 4, GL_INT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATT_JOINT);
	//BONE WEIGTHS
	glBindBuffer(GL_ARRAY_BUFFER, vbo[VBO_WEIGHT]);
	glBufferData(GL_ARRAY_BUFFER, vertSize * sizeof(float) * 4, weights, GL_STATIC_DRAW);
	glVertexAttribPointer(ATT_WEIGHT, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(ATT_WEIGHT);

	glBindVertexArray(0);
}