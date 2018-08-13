//------------------------------------------------------------------------------
// GLUniformBuffer.cpp
//
// OPEN GL implementation of a uniform buffer object (vbo)
// Available since OPEN GL 3.1
//
// Author: Sommerauer Christian
// Created: 30.07.18
// Changed: 01.08.18
//------------------------------------------------------------------------------
//

#include <graphics\api\UniformBuffer.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine { namespace graphics {

	//--------------------------------------------------------------------------
	UniformBuffer::UniformBuffer(U32 size, void* pData)
	{
		GLCall(glGenBuffers(1, &m_Handle));
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Handle));

		// TODO: Option to choose between dynamic and static draw
		GLCall(glBufferData(GL_UNIFORM_BUFFER, size, 0, GL_DYNAMIC_DRAW));
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));		
	}

	//--------------------------------------------------------------------------
	UniformBuffer::~UniformBuffer()
	{
		GLCall(glDeleteBuffers(1, &m_Handle));
	}

	//--------------------------------------------------------------------------
	void UniformBuffer::setData(const void * pData, 
		const U32 size, const U32 offset) const
	{
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Handle));
		// Pointer to the gpu
		//GLvoid* p = GLCall(glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY));
		//memcpy(p, pData, size);
		//GLCall(glUnmapBuffer(GL_UNIFORM_BUFFER));
		GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, pData));
	}

	//--------------------------------------------------------------------------
	void UniformBuffer::setBindingPoint(const U8 slot)
	{
		m_BindingPoint = slot;
		GLCall(glBindBufferBase(GL_UNIFORM_BUFFER, slot, m_Handle));
	}

	//--------------------------------------------------------------------------
	U32 UniformBuffer::getHandle() const
	{
		return m_Handle;
	}		

	//--------------------------------------------------------------------------
	U8 UniformBuffer::getBindindPoint() const
	{
		return m_BindingPoint;
	}

	//--------------------------------------------------------------------------
	void UniformBuffer::bind() const
	{
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Handle));
	}

	//--------------------------------------------------------------------------
	void UniformBuffer::unbind() const
	{
		GLCall(glBindBuffer(GL_UNIFORM_BUFFER, 0));
	}

}}