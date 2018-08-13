#pragma once

namespace engine {

	class Entity;

	class AssetLoader {
	private:

	public:
		static Entity* loadEntity(const char *path);
	};
}