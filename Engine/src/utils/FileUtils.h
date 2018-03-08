#pragma once

#include <string>
#include "../graphics/Mesh.h"

namespace engine {
	
	using namespace engine::graphics;

	class FileUtils {
	public:
		static std::string read_file(const char* filepath);
		static void FileUtils::load_obj(const char* path, Mesh & mesh);
	
	};
}
