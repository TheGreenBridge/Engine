//------------------------------------------------------
// File name:		FileUtils.cpp
// Author:			Christian Sommerauer
// Last Update:		09.04.2018
// Description:		Load file on the system
//------------------------------------------------------

#include <utils\FileUtils.h>
#include <utils\Log.h>
#include <math\vec3.h>
#include <math\vec2.h>

#include <vector>

namespace engine {
	std::string FileUtils::read_file(const char* filepath) {

		// flag "r" für nur lesen, "t" für Zeilenende in Textdateien 
		//FILE* file = fopen(filepath, "rt");
		FILE* file;

		errno_t err = fopen_s( &file,filepath, "r");
		
		// err is 0 if file failed to open
		if (err != 0)
		{
			LOG_ERROR("Could not read file in path!");
			return std::string("");
		}

		fseek(file, 0, SEEK_END);
		unsigned long length = ftell(file);
		char* data = new char[length + 1];

		memset(data, 0, length + 1);
		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);
		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}

	void FileUtils::load_obj(const char* filepath, Mesh & mesh) {

		unsigned int counter = 0;
		unsigned int faces = 0;
		unsigned int normals = 0;

		std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
		std::vector< Vec3 > temp_vertices;
		std::vector< Vec3 > temp_normals;
		std::vector< vec2 > temp_uvs;

		// FILE * file = fopen(path, "r");
		FILE* file;

		errno_t err = fopen_s(&file, filepath, "r");

		// err is 0 if file failed to open
		if (err != 0 || file == NULL) {
			LOG("Impossible to open the file !\n");
			return;
		}

		else LOG("Loading Mesh ...");

		while (1) {

			char lineHeader[128];
			// read the first word of the line
			int res = fscanf(file, "%s", lineHeader);

			if (res == EOF)
				break; // EOF = End Of File. Quit the loop.

					   // else : parse lineHeader
			if (strcmp(lineHeader, "v") == 0) {
				Vec3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				temp_vertices.push_back(vertex);
			}
			else if (strcmp(lineHeader, "vt") == 0) {
				vec2 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
				temp_uvs.push_back(uv);
			}
			else if (strcmp(lineHeader, "vn") == 0) {
				normals++;
				Vec3 normal;
				fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				temp_normals.push_back(normal);

			}
			else if (strcmp(lineHeader, "f") == 0) {
				faces++;

				//std::string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9) {
					LOG_ERROR("File can't be read by our simple parser : ( Try exporting with other options\n");
					return;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}

		LOG("Vertices: ", vertexIndices.size());
		LOG("Faces: ", faces);
		LOG("Normals: ", normals);

		bool test = false;

		// For each vertex of each triangle
		for (unsigned int i = 0; i < vertexIndices.size(); i++) {
			unsigned int vertexIndex = vertexIndices[i];
			unsigned int uvIndex = uvIndices[i];
			unsigned int normalIndex = normalIndices[i];

			Vec3 vertex;
			Vec3 normal;
			vec2 uv;

			if (vertexIndex > temp_vertices.size()) {
				test = true;
			}
			else vertex = temp_vertices[vertexIndex - 1];

			if (normalIndex > temp_normals.size()) {
				test = true;
			}
			else normal = temp_normals[normalIndex - 1];

			if (uvIndex > temp_uvs.size()) {
				test = true;
			}
			else uv = temp_uvs[uvIndex - 1];

			counter++;

			if (!test) {
				mesh.getVertices().push_back(vertex);
				mesh.getNormals().push_back(normal);
				mesh.getUVs().push_back(uv);
			}
			else LOG("Es gab ein Problem beim OBJ Loader!");

		}
		mesh.numVertices = vertexIndices.size();

		LOG("Vertex Count ", counter);
	}

	
}