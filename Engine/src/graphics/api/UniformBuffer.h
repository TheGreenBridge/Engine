//------------------------------------------------------------------------------
// UniformBuffer.h
//
// Represents graphics data uniforms
//
// Author: Sommerauer Christian
// Created: 30.07.18
// Changed: 01.08.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>
#include <graphics\api\Shader.h>

namespace engine { namespace graphics {

	class UniformBuffer {
	private:

		U32 m_Handle;
		U8 m_BindingPoint;

	public:

		// Cstr
		UniformBuffer(U32 size, void* pData = nullptr);

		// Deleted cstr
		UniformBuffer() = delete;
		UniformBuffer(const UniformBuffer&) = delete;
		UniformBuffer(UniformBuffer&&) = delete;
		UniformBuffer& operator=(const UniformBuffer&) = delete;
		UniformBuffer& operator=(UniformBuffer&&) = delete;

		~UniformBuffer();

		// Binding
		void bind() const;
		void unbind() const;

		// Setter
		void setData(const void * pointer, const U32 size, const U32 offset = 0) const;
		void setBindingPoint(const U8 slot);

		// Getter
		U32 getHandle() const;		
		U8 getBindindPoint() const;
	};

}}