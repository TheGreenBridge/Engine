//------------------------------------------------------------------------------
// GLBufferLayout.cpp
//
// OPEN GL implementation of vertex buffer layout
//
// Author: Sommerauer Christian
// Created: 21.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\BufferLayout.h>
#include <renderapi\opengl\GLCommon.h>

namespace engine {	namespace graphics {
	
	//--------------------------------------------------------------------------
	BufferLayout::BufferLayout()
	{

	}

	//--------------------------------------------------------------------------
	BufferLayout::~BufferLayout()
	{

	}

	//--------------------------------------------------------------------------
	void BufferLayout::pushFloat(U32 count)
	{
		m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * sizeof(GLfloat);
	}

	//--------------------------------------------------------------------------
	void BufferLayout::pushByte(U32 count)
	{
		m_Elements.push_back({ GL_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	//--------------------------------------------------------------------------
	void BufferLayout::pushUnsignedInteger(U32 count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	//--------------------------------------------------------------------------
	U32 BufferLayout::getStride() const
	{
		return 0;
	}

	//--------------------------------------------------------------------------
	const std::vector<LayoutElement>& BufferLayout::getLayout() const
	{
		return m_Elements;
	}
}}