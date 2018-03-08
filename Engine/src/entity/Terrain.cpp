#include "Terrain.h"
#include <utils/Log.h>
#include <assert.h>
#include <cmath>
#include <graphics/api/Loader.h>
#include <math/Quaternion.h>

namespace engine{	namespace entity {

		Terrain::Terrain() : numIndices(0) {
			
			F32 vertices[VERTICES_COUNT * 3];
			//F32 normals[VERTICES_COUNT * 3];
			
			F32 angle = 0;
			U32 indices[6 * (VERTICES_PER_SIDE - 1)*(VERTICES_PER_SIDE - 1)];
			U32 vertexPointer = 0;
			for (int i = 0; i < VERTICES_PER_SIDE; i++) {
				
				for (int j = 0; j < VERTICES_PER_SIDE; j++) {
					// XYZ
					angle += 1.0f;
					vertices[vertexPointer * 3] = (float)j / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;
					vertices[vertexPointer * 3 + 2] = sinf((float)(angle*PI/180.0f));
					vertices[vertexPointer * 3 + 1] = (float)i / (float)(VERTICES_PER_SIDE - 1) * TILE_SIZE;

					vertexPointer++;
				}
			}
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
			
		}

		void Terrain::loadTerrain() {
			
		}

		Terrain::~Terrain() {

		}
		Model &Terrain::getModel() {
			return m_Model;
		}

		U32 Terrain::getNumIndices() {
			return numIndices;
		}

	}
}