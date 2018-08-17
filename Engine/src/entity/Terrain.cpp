//------------------------------------------------------------------------------
// File Name: Terrain.cpp
// Description: Implementation of the terrain
//
// Author: Sommerauer Christian
// Created: xx.xx.xxxx
// Changed: 17.08.2018
//------------------------------------------------------------------------------
//

#include "Terrain.h"
#include <utils/Log.h>
#include <assert.h>
#include <graphics/api/Loader.h>
#include <math/Quaternion.h>

#include <graphics\api\IndexBuffer.h>
#include <graphics\api\Shader.h>

#include <utils\Random.h>
#include <cmath>

#include <EngineCore.h>

// std
#include <cmath>

namespace engine{	namespace entity {

		Terrain::Terrain() : numIndices(0), transform(Vec3(-TILE_SIZE/2, -1, -TILE_SIZE/2), Quaternion(0,0,0,1), 1.0f)
		{
			vertices = new F32[VERTICES_COUNT * 3];
			normals = new F32[VERTICES_COUNT * 3];
			indices = new U32[6 * (VERTICES_PER_SIDE - 1)*(VERTICES_PER_SIDE - 1)];
		}

		void Terrain::loadTerrain() {
			
		}

		Terrain::~Terrain() {
			delete[] vertices;
			delete[] normals;
			delete[] indices;
		}

		void Terrain::init()
		{
			shader = Engine::gShaderManager.createShader("res/shader/terrain/terrainshader.glsl");
			shader->setUniformBlockIndex("vs_uniforms", 0);

			U32 vertexPointer = 0;
			
			// Fill in vertices
			for (int i = 0; i < VERTICES_PER_SIDE; i++) {

				for (int j = 0; j < VERTICES_PER_SIDE; j++) {
					// XYZ
					//angle += 1.0f;
					vertices[vertexPointer * 3] = (float)j / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;
					vertices[vertexPointer * 3 + 1] = 0.0f;
					vertices[vertexPointer * 3 + 2] = (float)i / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;//sinf((float)(angle*PI / 180.0f));

					vertexPointer++;
				}
			}

			// Fill indices
			for (int gz = 0; gz<VERTICES_PER_SIDE - 1; gz++) {
				for (int gx = 0; gx<VERTICES_PER_SIDE - 1; gx++) {
					int topLeft = (gz*VERTICES_PER_SIDE) + gx;
					int topRight = topLeft + 1;
					int bottomLeft = ((gz + 1)*VERTICES_PER_SIDE) + gx;
					int bottomRight = bottomLeft + 1;
					indices[numIndices++] = topLeft;
					indices[numIndices++] = bottomLeft;
					indices[numIndices++] = topRight;
					indices[numIndices++] = topRight;
					indices[numIndices++] = bottomLeft;
					indices[numIndices++] = bottomRight;
				}
			}

			//m_Model.vertices = Loader::loadIndexedBufferf(vertices, VERTICES_COUNT * 3, indices, numIndices);

			m_Model.vertices = Engine::gBufferManager.createVertexArray();
			VertexBuffer* buffer = Engine::gBufferManager.createVertexBuffer(VERTICES_COUNT * 3 * 4, BufferUsage::DYNAMIC);
			VertexBuffer* normalbuffer = Engine::gBufferManager.createVertexBuffer(VERTICES_COUNT * 3 * 4, BufferUsage::DYNAMIC);


			buffer->setData(VERTICES_COUNT * 3 * 4, vertices);
			normalbuffer->setData(VERTICES_COUNT * 3 * 4, normals);

			BufferLayout layout;
			layout.pushFloat(3);
			m_Model.vertices->addBuffer(buffer, layout);
			m_Model.vertices->addBuffer(normalbuffer, layout);

			index = Engine::gBufferManager.createIndexBuffer(indices, numIndices);
			update();
		}

		F32 phase = 0.0f;
		const F32 frequency = 5.0f;

		void Terrain::update()
		{
			phase += 0.1f;
			F32 anglex = 0.0f;
			F32 angley = 0.0f;

			U32 vertexPointer = 0;
			Random rand;
			// Fill in vertices
			for (int i = 0; i < VERTICES_PER_SIDE; i++) {

				anglex += frequency;
				angley = 0.0f;
				for (int j = 0; j < VERTICES_PER_SIDE; j++) {
					// XYZ
					angley += frequency;
					vertices[vertexPointer * 3] = (float)j / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;
					vertices[vertexPointer * 3 + 1] = rand.generateF32(1.0f)* sin((anglex+angley)*(F32)PI/180.0f + phase); // rand.generateF32(2.0f);
					vertices[vertexPointer * 3 + 2] = (float)i / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;//sinf((float)(angle*PI / 180.0f));

					vertexPointer++;
				}
			}
			m_Model.vertices->getBuffer(0)->setData(VERTICES_COUNT * 3 * 4, vertices);
			//m_Model.vertices->getBuffer(1)->setData(VERTICES_COUNT * 3 * 4, normals);
		}

		void Terrain::draw() const
		{
			shader->enable();
			m_Model.vertices->bind();
			index->draw();
		}

		Model &Terrain::getModel() {
			return m_Model;
		}

		U32 Terrain::getNumIndices() {
			return numIndices;
		}
	}
}