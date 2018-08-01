#include "MemoryManager.h"

namespace engine {
	namespace memory {

		MemoryManager::MemoryManager()
			: LinearAllocator(GLOBAL_MEMORY)
		{

		}

		MemoryManager::~MemoryManager()
		{

		}

		/*blk MemoryManager::allocate(U32 size)
		{
			return allocate(size);
		}

		void MemoryManager::deallocate(blk allocation)
		{

		}*/

		void MemoryManager::hardReset()
		{

		}
	}
}


