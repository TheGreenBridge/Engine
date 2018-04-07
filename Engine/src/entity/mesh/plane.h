#pragma once

#include "../../graphics/Mesh.h"

int tiles = 20;
void createPlaneMesh(engine::graphics::Mesh &planeMesh) {
	for (int z = -tiles; z <= tiles; z++) {
		//counter += 10;
		planeMesh.getVertices().push_back(Vec3((float)tiles*2, 0.0f, (float)z));
		planeMesh.getVertices().push_back(Vec3((float)-tiles*2, 0.0f, (float)z));

		//std::cout << "inGENPLANE: X(" << 5 << ") Z(" << z << ")" << std::endl;
		//std::cout << "inGENPLANE: X(" << -5 << ") Z(" << z << ")" << std::endl;
	}
	for (float x = (float)-tiles; x <= (float)tiles; x++) {
		planeMesh.getVertices().push_back(Vec3(x*2, 0, (float)tiles));
		planeMesh.getVertices().push_back(Vec3(x*2, 0, (float)-tiles));
		//std::cout << "inGENPLANE: X(" << x << ") Z(" << 5 << ")" << std::endl;
		//std::cout << "inGENPLANE: X(" << x << ") Z(" << -5 << ")" << std::endl;
	}
}