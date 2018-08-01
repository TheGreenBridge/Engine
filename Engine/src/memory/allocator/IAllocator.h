#pragma once

#include <common\types.h>

namespace engine {namespace memory {

	struct blk {
		void* ptr;
		unsigned int size;
	};

	class IAllocator {
	public:
		virtual blk allocate(U32 size) = 0;
		virtual void deallocate(blk allocation) = 0;
	};
} }

