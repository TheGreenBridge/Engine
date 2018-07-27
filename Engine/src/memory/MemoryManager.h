#ifndef __MEMORY_MANAGER_H__
#define __MEMORY_MANAGER_H__
#pragma once

#include <memory\allocator\LinearAllocator.h>

#define GLOBAL_MEMORY 1024

namespace engine {
	namespace memory {

		class MemoryManager : private LinearAllocator{
		private:
		public:
			MemoryManager();
			~MemoryManager();

			blk newMemory(size_t size);
			void hardReset();
		};

	}
}

#endif
