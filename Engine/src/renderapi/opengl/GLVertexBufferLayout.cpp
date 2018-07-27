//------------------------------------------------------------------------------
// GLVertexBufferLayout.cpp
//
// OPEN GL implementation of vertex buffer layout
//
// Author: Sommerauer Christian
// Created: 21.07.18
// Changed: 22.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\VertexBufferLayout.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine {
	namespace graphics {

		void VertexBufferLayout::pushFloat(U32 count)
		{
			m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
			m_Stride += count * sizeof(GLfloat);
		}

		void VertexBufferLayout::pushByte(U32 count)
		{
			m_Elements.push_back({ GL_BYTE, count, GL_TRUE });
			m_Stride += count * sizeof(GLbyte);
		}

		void VertexBufferLayout::pushUnsignedInteger(U32 count)
		{
			m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
			m_Stride += count * sizeof(GLuint);
		}

		U32 VertexBufferLayout::getStride() const
		{
			return m_Stride;
		}

		const std::vector<LayoutElement>& VertexBufferLayout::getLayout() const
		{
			return m_Elements;
		}
	}
}