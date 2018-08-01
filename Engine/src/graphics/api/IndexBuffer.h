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

		private:
			U32 m_Handle;
			U32 m_Count;
			IndexBuffer();

		public:
			// Ctr
			IndexBuffer(const U32* data, U32 count);
			// Deleted Ctr
			IndexBuffer(const IndexBuffer&) = delete;

			~IndexBuffer();

			// Binding
			void bind() const;
			void unbind() const;

			// Getter
			inline U32 getCount() const;
		};

	}
}