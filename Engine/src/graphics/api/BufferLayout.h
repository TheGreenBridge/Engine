//------------------------------------------------------------------------------
// VertexBufferArray.h
//
// Represents a layout in a vertex buffer 
//
// Author: Sommerauer Christian
// Created: 18.07.18
// Changed: 30.07.18
//------------------------------------------------------------------------------
//

#pragma once

#include <common\types.h>
#include <vector>

namespace engine { namespace graphics{

	struct LayoutElement
	{
		U32 type;
		U32 count;
		U32 normalized;
	};

	class BufferLayout
	{
	private:

		std::vector<LayoutElement> m_Elements;
		U32 m_Stride;

	public:
		BufferLayout();

		// Deleted Ctr
		BufferLayout(const BufferLayout&) = delete;

		~BufferLayout();

		void pushFloat(U32 count);

		void pushByte(U32 count);

		void pushUnsignedInteger(U32 count);

		U32 getStride() const;

		const std::vector<LayoutElement>& getLayout() const;
	};


}
}
