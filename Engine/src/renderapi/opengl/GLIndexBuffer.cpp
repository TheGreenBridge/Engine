//------------------------------------------------------------------------------
// IndexBuffer.cpp
//
// OPEN GL implementation of a vertex buffer object (vbo)
//
// Author: Sommerauer Christian
// Created: 30.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\IndexBuffer.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine {
	namespace graphics {

		//--------------------------------------------------------------------------
		IndexBuffer::IndexBuffer(const U32* data, U32 count) :
			m_Count(count)
		{
			GLCall(glGenBuffers(1, &m_Handle));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(U32) * count, 
				data, GL_STATIC_DRAW));
		}

		//--------------------------------------------------------------------------
		IndexBuffer::~IndexBuffer()
		{
			GLCall(glDeleteBuffers(1, &m_Handle));
			LOG("Deleted IndexBuffer");
		}

		//--------------------------------------------------------------------------
		void IndexBuffer::bind() const
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
		}

		//--------------------------------------------------------------------------
		void IndexBuffer::unbind() const
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		//--------------------------------------------------------------------------
		void IndexBuffer::draw() const
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Handle));
			GLCall(glDrawElements(GL_LINES, m_Count, GL_UNSIGNED_INT, 0));
		}

		//--------------------------------------------------------------------------
		inline U32 IndexBuffer::getCount() const
		{
			return m_Count;
		}
	}
}