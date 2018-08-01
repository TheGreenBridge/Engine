//------------------------------------------------------------------------------
// VertexBufferArray.h
//
// OPEN GL implementation of a vertex buffer object (vbo)
//
// Author: Sumi
// Created: 18.07.18
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\VertexBuffer.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine { namespace graphics {

	//--------------------------------------------------------------------------
	static U32 BufferUsageToGL(BufferUsage usage)
	{
		switch (usage)
		{
		case BufferUsage::STATIC: return GL_STATIC_DRAW;
		case BufferUsage::DYNAMIC: return GL_DYNAMIC_DRAW;
		}
		return 0;
	}

	//--------------------------------------------------------------------------
	VertexBuffer::VertexBuffer(BufferUsage usage) : m_Usage(usage)
	{
		GLCall(glGenBuffers(1, &m_Handle));
	}

	//--------------------------------------------------------------------------
	VertexBuffer::VertexBuffer(U32 size, BufferUsage usage) : 
		m_Size(size), m_Usage(usage)
	{
		GLCall(glGenBuffers(1, &m_Handle));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, BufferUsageToGL(m_Usage)));
	}

	//--------------------------------------------------------------------------
	VertexBuffer::~VertexBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_Handle));
		LOG("Deleted VertexBuffer");
	}

	//--------------------------------------------------------------------------
	void VertexBuffer::setData(U32 size, const void* data)
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, (const GLvoid *) data));
	}

	//--------------------------------------------------------------------------
	void VertexBuffer::resize(U32 size)
	{
		m_Size = size;

		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
		// size is in bytes
		GLCall(glBufferData(GL_ARRAY_BUFFER, size, nullptr, BufferUsageToGL(m_Usage)));

	}

	//--------------------------------------------------------------------------
	void VertexBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Handle));
	}
	
	//--------------------------------------------------------------------------
	void VertexBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	}
} }