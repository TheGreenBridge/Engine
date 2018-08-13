#pragma once

#include <memory\allocator\PoolAllocator.h>
#include <common\types.h>
#include <graphics\api\VertexArray.h>
#include <graphics\api\UniformBuffer.h>

#define NUM_VAO		100
#define NUM_VBO		100
#define NUM_UNIFORM	10

namespace engine {
	namespace graphics {

		using namespace engine::memory;

		class BufferManager {
		public:

			// Ctor & Dtor
			BufferManager(IAllocator* allocator);
			~BufferManager();

			VertexArray* createVertexArray();
			VertexBuffer* createVertexBuffer(U32 size, BufferUsage usage = BufferUsage::STATIC);
			UniformBuffer* createUniformBuffer(U32 size);

			void destroy(VertexArray* vao);
			void destroy(VertexBuffer* vbo);
			void destroy(UniformBuffer* uniform);

			// Deleted Ctr
			BufferManager() = delete;
			BufferManager(const BufferManager&) = delete;
			BufferManager(BufferManager&&) = delete;
			// Deleted Assignment
			BufferManager& operator=(const BufferManager&) = delete;
			BufferManager& operator=(const BufferManager&&) = delete;

		private:

			PoolAllocator<VertexArray> m_PoolVAO;
			PoolAllocator<VertexBuffer> m_PoolVBO;
			PoolAllocator<UniformBuffer> m_PoolUniform;
			IAllocator* m_memory;
		};

	}
}