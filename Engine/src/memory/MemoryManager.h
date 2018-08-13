#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__
#pragma once

#include <memory\allocator\LinearAllocator.h>
#include <common\types.h>

#define GLOBAL_MEMORY 102400

namespace engine {
	namespace memory {

		class MemoryManager : public IAllocator{

		public:
			MemoryManager();
			~MemoryManager();

			blk allocate(U32 size);
			void deallocate(blk allocation);

			void hardReset();
		private:
			LinearAllocator m_allocator;
		};

	}
}

#endif
