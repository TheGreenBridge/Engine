#pragma once

#include <graphics\BufferManager.h>
#include <EngineCore.h>

namespace engine {
	namespace graphics {

		BufferManager::BufferManager(U32 vaos, U32 vbos, U32 layouts) :
			m_PoolVAO(&Engine::gMemoryManager, vaos),
			m_PoolVBO(&Engine::gMemoryManager, vbos),
			m_PoolLayout(&Engine::gMemoryManager, layouts),
			m_PoolUniform(&Engine::gMemoryManager, NUM_UNIFORM)
		{

		}		

		BufferManager::~BufferManager()
		{

		}

		VertexArray* BufferManager::createVertexArray()
		{
			return m_PoolVAO.allocate();
		}

		VertexBuffer* BufferManager::createVertexBuffer(U32 size, BufferUsage usage)
		{
			return m_PoolVBO.allocate(size, usage);
		}

		BufferLayout* BufferManager::createBufferLayout()
		{
			return m_PoolLayout.allocate();
		}

		UniformBuffer* BufferManager::createUniformBuffer(U32 size)
		{
			return m_PoolUniform.allocate(size);
		}

		void BufferManager::destroy(VertexArray* vao)
		{
			m_PoolVAO.deallocate(vao);
		}

		void BufferManager::destroy(VertexBuffer* vbo)
		{
			m_PoolVBO.deallocate(vbo);
		}

		void BufferManager::destroy(BufferLayout* layout)
		{
			m_PoolLayout.deallocate(layout);
		}

		void BufferManager::destroy(UniformBuffer* uniform)
		{
			m_PoolUniform.deallocate(uniform);
		}

	}
}