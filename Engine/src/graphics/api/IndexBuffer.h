//------------------------------------------------------------------------------
// IndexBuffer.cpp
//
// Represents graphics data
//
// Author: Sumi
// Created: 19.07.18
// Changed: 19.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include<common\types.h>

namespace engine {
	namespace graphics {
		class VertexBuffer {
		public:
			enum BufferUsage {
				STATIC, DYNAMIC
			};
		private:
			U32 m_Handle;
			U32 m_Size;
			BufferUsage m_Usage;

		public:
			VertexBuffer(BufferUsage usage);
			VertexBuffer(U32 size, BufferUsage usage);
			~VertexBuffer();

			void setData(U32 size, const void* data);
			void resize(U32 size);

			void bind() const;
			void unbind() const;
		};

	}
}