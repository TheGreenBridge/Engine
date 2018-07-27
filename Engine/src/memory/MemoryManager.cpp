#include "MemoryManager.h"

namespace engine {
	namespace memory {

		MemoryManager::MemoryManager()
			: LinearAllocator(GLOBAL_MEMORY)
		{}
		MemoryManager::~MemoryManager()
		{
		}

		blk MemoryManager::newMemory(size_t size)
		{
			return allocate(size);
		}
		void MemoryManager::hardReset()
		{
		}
	}
}


