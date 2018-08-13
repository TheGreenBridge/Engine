#include "MemoryManager.h"
#include <utils\Log.h>

namespace engine {
	namespace memory {

		MemoryManager::MemoryManager()
			: m_allocator(GLOBAL_MEMORY)
		{

		}

		MemoryManager::~MemoryManager()
		{

		}

		blk MemoryManager::allocate(U32 size)
		{
			LOG("Allocation: " + size);
			m_allocator.logStates();
			return m_allocator.allocate(size);
		}

		void MemoryManager::deallocate(blk allocation)
		{

		}

		void MemoryManager::hardReset()
		{

		}
	}
}


