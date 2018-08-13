//------------------------------------------------------------------------------
// VertexBufferArray.h
//
// Represents a vertex buffer array (VAO)
// It is basically an array of vertex buffer objects (VBO)
//
// Author: Sommerauer Christian
// Created: 18.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>

#include <graphics\api\VertexBuffer.h>
#include <graphics\api\BufferLayout.h>


#include <vector>

namespace engine {	namespace graphics {
	class VertexArray
	{
	private:
		std::vector<VertexBuffer*> m_Buffers;
		U32 m_Handle;
		U32 m_Index;
	public:
		// Ctr
		VertexArray();

		// Deleted Ctr
		VertexArray(const VertexArray&) = delete;
		VertexArray(VertexArray&&) = delete;
		VertexArray& operator=(const VertexArray&) = delete;
		VertexArray& operator=(VertexArray&&) = delete;

		~VertexArray();

		VertexBuffer* getBuffer(U32 index = 0);
		VertexBuffer* createAndAddBuffer(U32 size, const BufferLayout& layout, 
			BufferUsage usage = BufferUsage::STATIC);

		void VertexArray::addBuffer(VertexBuffer* buffer,
			const BufferLayout& layout);

		void draw(const U32 count) const;

		void bind() const;
		void unbind() const;
	};
}}