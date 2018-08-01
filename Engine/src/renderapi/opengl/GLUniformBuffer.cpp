//------------------------------------------------------------------------------
// GLUniformBuffer.cpp
//
// OPEN GL implementation of a uniform buffer object (vbo)
// Available since OPEN GL 3.1
//
// Author: Sumi
// Created: 30.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\UniformBuffer.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine {
	namespace graphics {

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
		void UniformBuffer::setData(U32 offset, void * pData, U32 size) const
		{
			GLCall(glBindBuffer(GL_UNIFORM_BUFFER, m_Handle));
			// Pointer to the gpu
			/*GLvoid* p = GLCall(glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY));
			memcpy(p, pointer, size);
			GLCall(glUnmapBuffer(GL_UNIFORM_BUFFER));*/
			GLCall(glBufferSubData(GL_UNIFORM_BUFFER, offset, size, pData));
		}

		//--------------------------------------------------------------------------
		U32 UniformBuffer::getHandle() const
		{
			return m_Handle;
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

	}
}