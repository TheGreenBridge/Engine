//------------------------------------------------------------------------------
// VertexBufferArray.h
//
// OPEN GL Implementation of the vertex array object (vao)
//
// Author: Sumi
// Created: 18.07.18
// Changed: 21.07.18
//------------------------------------------------------------------------------
//

#include <graphics\api\VertexArray.h>
#include <renderapi\opengl\GLCommon.h>
#include <memory\Memory.h>


namespace engine { namespace graphics {

	//--------------------------------------------------------------------------
	static U32 getSizeOfType(U32 type)
	{
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_BYTE:
			return 1;
		default: return 0;
		}
	}

	//--------------------------------------------------------------------------
	VertexArray::VertexArray()
	{
		GLCall(glGenVertexArrays(1, &m_Handle));
	}

	//--------------------------------------------------------------------------
	VertexArray::~VertexArray()
	{
		GLCall(glDeleteVertexArrays(1, &m_Handle));
	}

	//--------------------------------------------------------------------------
	VertexBuffer* VertexArray::getBuffer(U32 index)
	{
		if (index >= 0 && index < m_Buffers.size())
		{
			return m_Buffers[index];
		}
		else
		{
			LOG_ERROR("index not in range");
			return nullptr;
		}
	}

	//--------------------------------------------------------------------------
	VertexBuffer* VertexArray::createAndAddBuffer(U32 size, 
		 const BufferLayout& layout, BufferUsage usage)
	{
		VertexBuffer* buffer = NEW_MEM VertexBuffer(size, usage);
		m_Buffers.emplace_back(buffer);
		addBuffer(buffer, layout);
		return buffer;
	}

	//--------------------------------------------------------------------------
	void VertexArray::addBuffer(VertexBuffer* buffer, 
		const BufferLayout& layout)
	{
		bind();
		buffer->bind();
		U32 offset = 0;
		const std::vector<LayoutElement>& elements = layout.getLayout();

		for (U32 i = 0; i < elements.size(); ++i)
		{
			const auto& element = elements[i];
			GLCall(glEnableVertexAttribArray(m_Index));
			GLCall(glVertexAttribPointer(m_Index, element.count, element.type,
				element.normalized, layout.getStride(), (void*)offset));

			m_Index++;
			offset += element.count * getSizeOfType(element.type);
		}
		
		buffer->unbind();
		unbind();
	}

	//--------------------------------------------------------------------------
	void VertexArray::draw(const U32 count) const
	{
		GLCall(glDrawArrays(GL_TRIANGLES, 0, count));
	}

	//--------------------------------------------------------------------------
	void VertexArray::bind() const
	{
		GLCall(glBindVertexArray(m_Handle));
	}

	//--------------------------------------------------------------------------
	void VertexArray::unbind() const
	{
		GLCall(glBindVertexArray(0));
	}

}}