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

	class VertexBufferLayout
	{
	private:

		std::vector<LayoutElement> m_Elements;
		U32 m_Stride;

	public:

		void pushFloat(U32 count);

		void pushByte(U32 count);

		void pushUnsignedInteger(U32 count);

		U32 getStride() const;

		const std::vector<LayoutElement>& getLayout() const;
	};


}
}
