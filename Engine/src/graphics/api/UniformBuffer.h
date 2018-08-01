//------------------------------------------------------------------------------
// UniformBuffer.h
//
// Represents graphics data
//
// Author: Sommerauer Christian
// Created: 30.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include<common\types.h>
#include <graphics\api\Shader.h>

namespace engine {
	namespace graphics {

		class UniformBuffer {
		private:
			U32 m_Handle;

		public:

			UniformBuffer(U32 size, void* pData = nullptr);

			// deleted cstr
			UniformBuffer(const UniformBuffer&) = delete;
			UniformBuffer() = delete;

			~UniformBuffer();

			void setData(U32 offset, void * pointer, U32 size) const;

			U32 getHandle() const;

			void bind() const;
			void unbind() const;
		};

	}
}