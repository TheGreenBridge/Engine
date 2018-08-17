//------------------------------------------------------------------------------
// BufferManager.cpp
//
// Implementation of the buffer manager
//
// Author: Sommerauer Christian
// Created: xx.xx.18
// Changed: 13.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <graphics\BufferManager.h>

namespace engine {	namespace graphics {

	//--------------------------------------------------------------------------
	BufferManager::BufferManager(IAllocator* allocator) :
		m_PoolVAO(allocator, NUM_VAO),
		m_PoolVBO(allocator, NUM_VBO),
		m_PoolUniform(allocator, NUM_UNIFORM),
		m_PoolIndices(allocator, NUM_INDICES),
		m_memory(allocator)
	{

	}		

	//--------------------------------------------------------------------------
	BufferManager::~BufferManager()
	{

	}

	//--------------------------------------------------------------------------
	VertexArray* BufferManager::createVertexArray()
	{
		return m_PoolVAO.allocate();
	}

	//--------------------------------------------------------------------------
	VertexBuffer* BufferManager::createVertexBuffer(U32 size, BufferUsage usage)
	{
		return m_PoolVBO.allocate(size, usage);
	}

	//--------------------------------------------------------------------------
	UniformBuffer* BufferManager::createUniformBuffer(U32 size)
	{
		return m_PoolUniform.allocate(size);
	}

	IndexBuffer * BufferManager::createIndexBuffer(const U32* data, U32 count)
	{
		return m_PoolIndices.allocate(data, count);
	}

	//--------------------------------------------------------------------------
	void BufferManager::destroy(VertexArray* vao)
	{
		m_PoolVAO.deallocate(vao);
	}

	//--------------------------------------------------------------------------
	void BufferManager::destroy(VertexBuffer* vbo)
	{
		m_PoolVBO.deallocate(vbo);
	}

	//--------------------------------------------------------------------------
	void BufferManager::destroy(UniformBuffer* uniform)
	{
		m_PoolUniform.deallocate(uniform);
	}

	//--------------------------------------------------------------------------
	void BufferManager::destroy(IndexBuffer* indices)
	{
		m_PoolIndices.deallocate(indices);
	}

}}