#pragma once

#include <memory\allocator\PoolAllocator.h>
#include <graphics\api\Shader.h>
#include <common\types.h>

namespace engine {
	namespace graphics {

		using namespace engine::memory;

		class ShaderManager {
		private:
			PoolAllocator<Shader> m_Pool;
			
		public:

			ShaderManager(U32 shaders);
			// Deleted Ctr
			ShaderManager() = delete;
			ShaderManager(const ShaderManager&) = delete;
			ShaderManager(ShaderManager&&) = delete;
			// Deleted Assignment
			ShaderManager& operator=(const ShaderManager&) = delete;
			ShaderManager& operator=(const ShaderManager&&) = delete;

			~ShaderManager();

			template <typename... arguments>
			Shader* createShader(arguments&&... args)
			{
				return m_Pool.allocate(std::forward<arguments>(args)...);
			}

			void destroy(Shader* vao);

		};

	}
}