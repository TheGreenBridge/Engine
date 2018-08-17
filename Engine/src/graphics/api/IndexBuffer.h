//------------------------------------------------------------------------------
// IndexBuffer.cpp
//
// Represents a buffer of indices on the gpu
//
// Author: Sumi
// Created: 19.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include<common\types.h>

namespace engine {	namespace graphics {

		class IndexBuffer {
		public:
			// Ctr
			IndexBuffer(const U32* data, U32 count);

			~IndexBuffer();

			// Binding
			void bind() const;
			void unbind() const;
			void draw() const;

			// Getter
			inline U32 getCount() const;

			// Deleted Ctr
			IndexBuffer() = delete;
			IndexBuffer(const IndexBuffer&) = delete;
			IndexBuffer(IndexBuffer&&) = delete;
			IndexBuffer& operator=(const IndexBuffer&) = delete;
			IndexBuffer& operator=(IndexBuffer&&) = delete;

		private:
			U32 m_Handle;
			U32 m_Count;
		};

	}
}