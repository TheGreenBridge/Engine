//------------------------------------------------------------------------------
// VertexBuffer.h
//
// Represents graphics data
//
// Author: Sumi
// Created: 18.07.18
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include<common\types.h>

namespace engine {	namespace graphics {

	enum BufferUsage {
		STATIC, DYNAMIC
	};

	class VertexBuffer {
	public:
		
	private:
		U32 m_Handle;
		U32 m_Size;
		BufferUsage m_Usage;

	public:
		// Ctr
		VertexBuffer(BufferUsage usage);
		VertexBuffer(U32 size, BufferUsage usage);

		// deleted Ctr
		VertexBuffer() = delete;
		VertexBuffer(const VertexBuffer&) = delete;

		~VertexBuffer();

		void setData(U32 size, const void* data);
		void resize(U32 size);

		void bind() const;
		void unbind() const;
	};

}}