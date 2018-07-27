//------------------------------------------------------------------------------
// VertexBufferArray.h
//
// Represents a vertex buffer array (VAO)
// It is basically an array of vertex buffer objects (VBO)
//
// Author: Sumi
// Created: 18.07.18
// Changed: 21.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

#include <graphics\api\VertexBuffer.h>
#include <graphics\api\VertexBufferLayout.h>


#include <vector>

namespace engine {	namespace graphics {
	class VertexArray
	{
	private:
		std::vector<VertexBuffer*> m_Buffers;
		U32 m_Handle;
		U32 m_Index;
	public:
		VertexArray();
		~VertexArray();

		VertexBuffer* getBuffer(U32 index = 0);
		VertexBuffer* createAndAddBuffer(U32 size, const VertexBufferLayout& layout, 
			BufferUsage usage = BufferUsage::STATIC);

		void VertexArray::addBuffer(const VertexBuffer& buffer, 
			const VertexBufferLayout& layout);

		void draw(const U32 count) const;

		void bind() const;
		void unbind() const;
	};
}}