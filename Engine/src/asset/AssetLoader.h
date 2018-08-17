#pragma once

namespace engine {
	namespace graphics {
	class Renderer;
	}
}

namespace engine {
		

	class Entity;

	class AssetLoader {
	private:

	public:
		static Entity* loadEntity(graphics::Renderer& renderer, const char *path);
		static void loadScene(graphics::Renderer& renderer, const char* path);
	};
}