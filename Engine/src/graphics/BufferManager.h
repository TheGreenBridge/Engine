#pragma once

#include <memory\allocator\PoolAllocator.h>
#include <graphics\api\VertexArray.h>
#include <graphics\api\UniformBuffer.h>
#include <common\types.h>

#define NUM_VAO		10
#define NUM_VBO		10
#define NUM_LAYOUT	10
#define NUM_UNIFORM	10

namespace engine {
	namespace graphics {

		using namespace engine::memory;

		class BufferManager {
		private:
			PoolAllocator<VertexArray> m_PoolVAO;
			PoolAllocator<VertexBuffer> m_PoolVBO;
			PoolAllocator<BufferLayout> m_PoolLayout;
			PoolAllocator<UniformBuffer> m_PoolUniform;
		public:

			BufferManager(U32 vaos, U32 vbos, U32 layouts);
			// Deleted Ctr
			BufferManager() = delete;
			BufferManager(const BufferManager&) = delete;
			BufferManager(BufferManager&&) = delete;
			// Deleted Assignment
			BufferManager& operator=(const BufferManager&) = delete;
			BufferManager& operator=(const BufferManager&&) = delete;

			~BufferManager();

			VertexArray* createVertexArray();
			VertexBuffer* createVertexBuffer(U32 size, BufferUsage usage);
			BufferLayout* createBufferLayout();
			UniformBuffer* createUniformBuffer(U32 size);

			void destroy(VertexArray* vao);
			void destroy(VertexBuffer* vbo);
			void destroy(BufferLayout* layout);
			void destroy(UniformBuffer* uniform);
		};

	}
}